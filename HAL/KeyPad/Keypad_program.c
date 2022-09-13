/*
 * KeyPad.c
 *
 * 	    Created on: 24/08/2022
 *      Author: Mohamed Hussein
 *      Layer: HAL
 */
#include "../../Library/STD_TYPE.h"
#include "../../MCAL/DIO/DIO_interface.h"

#include "Keypad_configuration.h"
#include "Keypad_private.h"
#include "Keypad_interface.h"

void vKeypad_Init(void)
{
	uint8_t u8Local_ColumnArray[4] = {Keypad_COL0,Keypad_COL1, Keypad_COL2, Keypad_COL3};
	uint8_t u8Local_ROWArray[4] = {Keypad_ROW0,Keypad_ROW1, Keypad_ROW2, Keypad_ROW3};

	for(uint8_t u8Local_ColIterator = 0; u8Local_ColIterator<COLUMN_NUM; u8Local_ColIterator++)
	{
		u8DIO_PinDir(Keypad_PORT, u8Local_ColumnArray[u8Local_ColIterator], DIO_OUTPUT);
		u8DIO_PinVal(Keypad_PORT,  u8Local_ColumnArray[u8Local_ColIterator], DIO_HIGH);
	}

	for(uint8_t u8Local_RowIterator = 0; u8Local_RowIterator<ROW_NUM; u8Local_RowIterator++)
	{
		u8DIO_PinDir(Keypad_PORT, u8Local_ROWArray[u8Local_RowIterator], DIO_INPUT);
		u8DIO_PinVal(Keypad_PORT, u8Local_ROWArray[u8Local_RowIterator], DIO_HIGH);
	}
}

char u8Keypad_GetPressedKey (void)
{
	uint8_t u8Local_PressedKey = Keypad_NoPressedKey, u8Local_PinState;
	uint8_t u8Local_ColIterator, u8Local_RowIterator;
	static uint8_t u8Local_Array[4][4] = Keypad_Array;
	/*static is used to save these arrays in .data/.bss rather than stack as its size is small
	 *as we call this function alot
	 */
	static uint8_t u8Local_ColumnArray[4] = {Keypad_COL0,Keypad_COL1, Keypad_COL2, Keypad_COL3};
	static uint8_t u8Local_ROWArray[4] = {Keypad_ROW0,Keypad_ROW1, Keypad_ROW2, Keypad_ROW3};

	for(u8Local_ColIterator = 0; u8Local_ColIterator<COLUMN_NUM; u8Local_ColIterator++)
	{
		/*Activate current Column*/
		u8DIO_PinVal(Keypad_PORT,  u8Local_ColumnArray[u8Local_ColIterator], DIO_LOW);

		for(u8Local_RowIterator = 0; u8Local_RowIterator<ROW_NUM; u8Local_RowIterator++)
		{
			/*Read current Row*/
			u8DIO_ReadPinVal(Keypad_PORT,  u8Local_ROWArray[u8Local_RowIterator], &u8Local_PinState);
			/*check if the switch is pressed*/
			if(u8Local_PinState == DIO_LOW)
			{
				/*get the value*/
				u8Local_PressedKey = u8Local_Array[u8Local_RowIterator][u8Local_ColIterator];

				/*Polling to make sure it is pressed one time (single pressed)*/
				while(u8Local_PinState == DIO_LOW)
				{
					u8DIO_ReadPinVal(Keypad_PORT,  u8Local_ROWArray[u8Local_RowIterator], &u8Local_PinState);
				}

				return u8Local_PressedKey;
			}
		}

		/*Deactivate current Column*/
		u8DIO_PinVal(Keypad_PORT,  u8Local_ColumnArray[u8Local_ColIterator], DIO_HIGH);
	}

	return u8Local_PressedKey;
}
