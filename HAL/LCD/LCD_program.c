/*
 * LCD_program.c
 *
 *  	Created on: 24/08/2022
 *      Author: Mohamed Hussein
 *      Layer: HAL
 */
#include "util/delay.h"
#include "../../Library/Conversion_Function.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "LCD_configuration.h"
#include "LCD_private.h"
#include "LCD_interface.h"

void vLCD_Init(void)
{
	/* 1. LCD Pin Directions */
	/* Data Pins Directions */
	u8DIO_PortDir(LCD_DATA_PORT, DIO_OUTPUT);

	/* Control Pins Directions */
	/* Rs Pin */
	u8DIO_PinDir(LCD_CTRL_PORT, LCD_RS_PIN, DIO_OUTPUT);
	/* R/W Pin */
	u8DIO_PinDir(LCD_CTRL_PORT, LCD_RW_PIN, DIO_OUTPUT);
	/* Enable Pin */
	u8DIO_PinDir(LCD_CTRL_PORT, LCD_EN_PIN, DIO_OUTPUT);
#if LCD_InitMode == EightBit_Init
	/*Wait for more than 30ms*/
	_delay_ms(40);
	/*Function Set: 1 or 2 Lines & 5x8 or 5x11 Dots*/
#if LCD_NumbersOfLines == One_Line
#if LCD_Font_Size == FiveEight_Size
	vLCD_SendCommand(OneLine_5x8_8Bit);
#elif LCD_Font_Size == FiveEleven_Size
	vLCD_SendCommand(OneLine_5x11_8Bit);
#endif
#elif LCD_NumbersOfLines == Two_Lines
#if LCD_Font_Size == FiveEight_Size
	vLCD_SendCommand(TwoLine_5x8_8Bit);
#elif LCD_Font_Size == FiveEleven_Size
	vLCD_SendCommand(TwoLine_5x11_8Bit);
#endif
#endif
	/*Wait for more than 39us*/
	_delay_us(40);
	/*Display On/Off control*/
#if LCD_Display == Display_ON
#if LCD_Cursor == Cursor_ON
#if LCD_Blinking == Blinking_ON
	vLCD_SendCommand(DisplayOn_CursorOn_BlinkingOn);
#elif LCD_Blinking == Blinking_OFF
	vLCD_SendCommand(DisplayOn_CursorOn_BlinkingOff);
#endif /*Blinking*/
#elif LCD_Cursor == Cursor_OFF
#if LCD_Blinking == Blinking_ON
	vLCD_SendCommand(DisplayOn_CursorOff_BlinkingOn);
#elif LCD_Blinking == Blinking_OFF
	vLCD_SendCommand(DisplayOn_CursorOff_BlinkingOff);
#endif  /*Blinking*/
#endif  /*cursor*/
#elif LCD_Display == Display_OFF
#if LCD_Cursor == Cursor_ON
#if LCD_Blinking == Blinking_ON
	vLCD_SendCommand(DisplayOff_CursorOn_BlinkingOn);
#elif LCD_Blinking == Blinking_OFF
	vLCD_SendCommand(DisplayOff_CursorOn_BlinkingOff);
#endif   /*Blinking*/
#elif LCD_Cursor == Cursor_OFF
#if LCD_Blinking == Blinking_ON
	vLCD_SendCommand(DisplayOff_CursorOff_BlinkingOn);
#elif LCD_Blinking == Blinking_OFF
	vLCD_SendCommand(DisplayOff_CursorOff_BlinkingOff);
#endif  /*Blinking*/
#endif  /*cursor*/
#endif  /*Display*/

	/*Wait for more than 39us*/
	_delay_us(40);
	/*Display Clear*/
	vLCD_SendCommand(CLEAR_DISPLAY);
	/*Wait for more than 1.53ms*/
	_delay_us(1600);
	/*Entry Mode Set*/
	vLCD_SendCommand(ENTRY_MODE_SET);
#endif   /*Eight Bit mode*/

}

void vLCD_SendCommand(uint8_t u8Copy_Command)
{
	/*Set Rs to 0 to choose IR register to send command -----> 0 (Instruction Register), 1(Data Register)*/
	u8DIO_PinVal(LCD_CTRL_PORT, LCD_RS_PIN, DIO_LOW);

	/*Set R/W to 0 so i can write data ----> 0 (write), 1(read)*/
	u8DIO_PinVal(LCD_CTRL_PORT, LCD_RW_PIN, DIO_LOW);

	/*Send Command*/
	u8DIO_PortVal(LCD_DATA_PORT, u8Copy_Command);

	/*Set enable pin from high to low with wide as 230ns*/
	u8DIO_PinVal(LCD_CTRL_PORT, LCD_EN_PIN, DIO_HIGH);
	_delay_ms(2);
	u8DIO_PinVal(LCD_CTRL_PORT, LCD_EN_PIN, DIO_LOW);

	/* Delay to let the LCD Display the character */
	_delay_ms(10);

}

void vLCD_ClearDisplay(void)
{
	vLCD_SendCommand(CLEAR_DISPLAY);
	vLCD_SendCommand(CURSOR_OFFEST);
}

void vLCD_SendCharacter(uint8_t u8Copy_Character)
{
	/*Set Rs to 1 to choose DR register to send command -----> 0 (Instruction Register), 1(Data Register)*/
	u8DIO_PinVal(LCD_CTRL_PORT, LCD_RS_PIN, DIO_HIGH);

	/*Set R/W to 0 so i can write data ----> 0 (write), 1(read)*/
	u8DIO_PinVal(LCD_CTRL_PORT, LCD_RW_PIN, DIO_LOW);

	/*Send Character*/
	u8DIO_PortVal(LCD_DATA_PORT, u8Copy_Character);

	/*Set enable pin from high to low with wide as 230ns*/
	u8DIO_PinVal(LCD_CTRL_PORT, LCD_EN_PIN, DIO_HIGH);
	_delay_ms(2);
	u8DIO_PinVal(LCD_CTRL_PORT, LCD_EN_PIN, DIO_LOW);

	/* Delay to let the LCD Display the character */
	_delay_ms(10);
}

void vLCD_SendString(const char* pchCopy_String)
{
	uint8_t u8Local_Iterator = 0;
	while(pchCopy_String[u8Local_Iterator] != '\0')
	{
		vLCD_SendCharacter(pchCopy_String[u8Local_Iterator]);
		u8Local_Iterator++;
	}
}

void vLCD_CreateCustomCharacter(const char *u8Copy_Pattern, uint8_t u8Copy_Location, uint8_t u8Copy_Row, uint8_t u8Copy_Col)
{
	uint8_t u8Local_Iterator=0;

	/*CGRAM addresses ranges from 0x40 to 0x7f
	 * it allows you to create 8 different custom characters at 8 different locations at CGRAM
	 * every new character is 8 bit, so every location is 8bit
	 * u8Copy_Pattern is an array of bits for all 5x7 or 5x10 dots, 5 columns 7 rows or 10 rows
	 * so every element represents a row which is 5 bit long ---> every row contains 5 pixels
	 */

	/*send location of CGRAM i want to write*/
	vLCD_SendCommand(0x40 + (u8Copy_Location*8));

	for(u8Local_Iterator = 0; u8Local_Iterator<8; u8Local_Iterator++)
	{
		vLCD_SendCharacter(u8Copy_Pattern[u8Local_Iterator]);
	}

	/*Go to ROW & COL i want to display on screen*/
	vLCD_GoToRowCol(u8Copy_Row, u8Copy_Col);

	/*send location to DDRAM to output the character on the screen*/
	vLCD_SendCharacter(u8Copy_Location);
}

void vLCD_GoToRowCol (uint8_t u8Copy_Row, uint8_t u8Copy_Col)
{
	uint8_t u8Local_Location = 0;

	if(u8Copy_Row == 0)  /*Location is at first line*/
	{
		u8Local_Location = 0x00 + u8Copy_Col;
	}
	else if(u8Copy_Row == 1)   /*Location is at second line*/
	{
		u8Local_Location = 0x40 + u8Copy_Col;
	}

	/*send address of the ROW & COL*/
	vLCD_SendCommand(CURSOR_OFFEST | u8Local_Location);

}

void vLCD_SendNumber(int32_t s32Copy_Number)
{
	char pcCopy_String[10];
	ConvertToString(pcCopy_String, s32Copy_Number);
	vLCD_SendString(pcCopy_String);
}
