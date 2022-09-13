/*
 * main.c
 *
 *  	Created on: 24/08/2022
 *      Author: Mohamed Hussein
 *      Layer: Application
 *      Motor Dashboard App
 */
#include "util/delay.h"
#include "../Library/Mapping_interface.h"
#include "../Library/Conversion_Function.h"

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/Timer/Timer_interface.h"

#include "../HAL/DC_Motor/DCMotor_interface.h"
#include "../HAL/Stepper_Motor/StepperMotor_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/KeyPad/Keypad_interface.h"
#include "../HAL/TempSensor/TempSensor_interface.h"
#include "../HAL/ServoMotor/ServoMotor_interface.h"

#define NOT_PRESSED      0x00

void main(void)
{
	uint8_t u8Local_PressedKey = NOT_PRESSED;
	uint8_t u8Local_StepperAngle[3] = {NOT_PRESSED,NOT_PRESSED,NOT_PRESSED};
	uint8_t u8Local_ServoAngleArray[3] = {NOT_PRESSED,NOT_PRESSED,NOT_PRESSED};
	uint8_t u8Local_Iterator = 0;
	uint16_t u16Local_StepperAngle = 0;
	uint16_t u16Local_ADCresult = 0;
	uint16_t u16Local_DCmapCW = 0;
	uint8_t u8Local_DCmapCCW = 0;
	uint8_t u8Local_Temperature = 0;
	uint8_t u8Local_ServoAngle = 0;
	vLCD_Init();
	vKeypad_Init();
	vDCMotor_Init();
	vSepperMotor_Init();
	vADC_Init();
	vTempSensor_Init();

	u8DIO_PinDir(DIO_PORTA,DIO_PIN0,DIO_INPUT);
	u8DIO_PinVal(DIO_PORTA,DIO_PIN0,DIO_HIGH);

	u8DIO_PinDir(DIO_PORTD,DIO_PIN4,DIO_OUTPUT);

	vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
	vLCD_SendString("Welcome to Motor");
	vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
	vLCD_SendString("Dashboard App");
	_delay_ms(1000);
	vLCD_ClearDisplay();


	while(1)
	{
		vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
		vLCD_SendString("1.Stepper 2.DC M");
		vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
		vLCD_SendString("3.Servo Motor");

		do{
			u8Local_PressedKey = u8Keypad_GetPressedKey();
		}while(u8Local_PressedKey == NOT_PRESSED);

		switch(u8Local_PressedKey)
		{
		/*Stepper Motor Case*/
		case '1': u8Local_PressedKey = NOT_PRESSED;
		vLCD_ClearDisplay();
		vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
		vLCD_SendString("1.Rotate CW     ");
		vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
		vLCD_SendString("2.Rotate CCW    ");

		do{
			u8Local_PressedKey = u8Keypad_GetPressedKey();
		}while(u8Local_PressedKey == NOT_PRESSED);

		if(u8Local_PressedKey == '1') /*Stepper rotate clockwise*/
		{
			u8Local_PressedKey = NOT_PRESSED;
			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
			vLCD_SendString("Set Angle: ");
			vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
			while(1)
			{

				do{
					u8Local_StepperAngle[u8Local_Iterator] = u8Keypad_GetPressedKey();
					if((u8Local_StepperAngle[u8Local_Iterator] - '0' < 0) || (u8Local_StepperAngle[u8Local_Iterator] - '0' > 9))
					{
						if(u8Local_StepperAngle[u8Local_Iterator] == 'A')
						{
							u8Local_PressedKey = 'A';
							break;
						}else
							u8Local_StepperAngle[u8Local_Iterator] = NOT_PRESSED;
					}
				}while(u8Local_StepperAngle[u8Local_Iterator] == NOT_PRESSED);

				if(u8Local_PressedKey == 'A')
					break;
				else
				{
					vLCD_SendCharacter(u8Local_StepperAngle[u8Local_Iterator]);
					u8Local_Iterator++;
					if(u8Local_Iterator >= 3)
						break;
				}
			}
			u8Local_PressedKey = NOT_PRESSED;

			u16Local_StepperAngle = (uint16_t)ConvertToint((char*)u8Local_StepperAngle);

			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
			vLCD_SendString("To Stop Press");
			vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
			vLCD_SendString("any key");

			vSepperMotor_RotateCWatAngle(u16Local_StepperAngle);
			u8Local_StepperAngle[0] = NOT_PRESSED;
			u8Local_StepperAngle[1] = NOT_PRESSED;
			u8Local_StepperAngle[2] = NOT_PRESSED;

			do{
				u8Local_PressedKey = u8Keypad_GetPressedKey();
			}while(u8Local_PressedKey == NOT_PRESSED);

			vSepperMotor_Stop();
			u8Local_PressedKey = NOT_PRESSED;
			u8Local_Iterator = 0;

		}else if(u8Local_PressedKey == '2')  /*Stepper rotate counter clockwise*/
		{
			u8Local_PressedKey = NOT_PRESSED;
			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
			vLCD_SendString("Set Angle: ");
			vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);

			while(1)
			{

				do{
					u8Local_StepperAngle[u8Local_Iterator] = u8Keypad_GetPressedKey();
					if((u8Local_StepperAngle[u8Local_Iterator] - '0' < 0) || (u8Local_StepperAngle[u8Local_Iterator] - '0' > 9))
					{
						if(u8Local_StepperAngle[u8Local_Iterator] == 'A')
						{
							u8Local_PressedKey = 'A';
							break;
						}else
							u8Local_StepperAngle[u8Local_Iterator] = NOT_PRESSED;
					}
				}while(u8Local_StepperAngle[u8Local_Iterator] == NOT_PRESSED);

				if(u8Local_PressedKey == 'A')
					break;
				else
				{
					vLCD_SendCharacter(u8Local_StepperAngle[u8Local_Iterator]);
					u8Local_Iterator++;
					if(u8Local_Iterator >= 3)
						break;
				}
			}
			u8Local_PressedKey = NOT_PRESSED;

			u16Local_StepperAngle = (uint16_t)ConvertToint((char*)u8Local_StepperAngle);

			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
			vLCD_SendString("To Stop Press");
			vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
			vLCD_SendString("any key");

			vSepperMotor_RotateCCWatAngle(u16Local_StepperAngle);
			u8Local_StepperAngle[0] = NOT_PRESSED;
			u8Local_StepperAngle[1] = NOT_PRESSED;
			u8Local_StepperAngle[2] = NOT_PRESSED;

			do{
				u8Local_PressedKey = u8Keypad_GetPressedKey();
			}while(u8Local_PressedKey == NOT_PRESSED);

			vSepperMotor_Stop();
			u8Local_PressedKey = NOT_PRESSED;
			u8Local_Iterator = 0;
		}
		break;
		/*DC Motor Case*/
		case '2': u8Local_PressedKey = NOT_PRESSED;
		vLCD_ClearDisplay();
		vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
		vLCD_SendString("1.Rotate CW     ");
		vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
		vLCD_SendString("2.Rotate CCW    ");
		do{
			u8Local_PressedKey = u8Keypad_GetPressedKey();
			if(u8Local_PressedKey - '0' <= 0  || u8Local_PressedKey - '0' > 2)
				u8Local_PressedKey = NOT_PRESSED;
		}while(u8Local_PressedKey == NOT_PRESSED);

		/*Rotate Clockwise*/
		if(u8Local_PressedKey == '1')
		{
			u8Local_PressedKey = NOT_PRESSED;
			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
			vLCD_SendString("SpeedControl 1.F");
			vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
			vLCD_SendString("2.Potent 3.LM35");

			do{
				u8Local_PressedKey = u8Keypad_GetPressedKey();
				if(u8Local_PressedKey - '0' <= 0  || u8Local_PressedKey - '0' > 3)
					u8Local_PressedKey = NOT_PRESSED;
			}while(u8Local_PressedKey == NOT_PRESSED);

			/*Full speed*/
			if(u8Local_PressedKey == '1')
			{
				vDCMotor_RotateCW();
				u8Local_PressedKey = NOT_PRESSED;
				vLCD_ClearDisplay();
				vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
				vLCD_SendString("To Stop Press");
				vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
				vLCD_SendString("any key");
				do{
					u8Local_PressedKey = u8Keypad_GetPressedKey();
				}while(u8Local_PressedKey == NOT_PRESSED);
				vDCMotor_Stop();
				u8Local_PressedKey = NOT_PRESSED;
			}
			else if(u8Local_PressedKey == '2')    /*Potentiometer speed control*/
			{
				vLCD_ClearDisplay();
				vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
				vLCD_SendString("To Stop Press");
				vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
				vLCD_SendString("any key");
				u8Timer1_SetCompareMatchMode(CHANNEL_A,SET_AT_TOP_CLEAR_AT_COMPARE);
				vTimer1_SetICRValue(65535);
				vTimer1_Initpostbuild(Fast_PWM_ICR1mode,Timer_prescaler8);
				u8Local_PressedKey = NOT_PRESSED;

				do{
					u8ADC_StartSingleConversionSynch(ADC_SingleEndedChannel0,&u16Local_ADCresult);
					u16Local_DCmapCW = (uint16_t) s32Map(0,1023,0,65535,u16Local_ADCresult);
					u8Timer1_SetCompValue(CHANNEL_A,u16Local_DCmapCW);
					u8Local_PressedKey = u8Keypad_GetPressedKey();
				}while(u8Local_PressedKey == NOT_PRESSED);

				u8Local_PressedKey = NOT_PRESSED;
				u8Timer1_SetCompareMatchMode(CHANNEL_A,NORMAL_OPERATION);
				vTimer1_Stop();
				vDCMotor_Stop();
				u16Local_ADCresult = 0;
				u16Local_DCmapCW = 0;
			}
			else if(u8Local_PressedKey == '3')    /*LM35 (Temperature) speed control*/
			{
				vLCD_ClearDisplay();
				vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
				vLCD_SendString("To Stop Press");
				vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
				vLCD_SendString("any key");
				u8Timer1_SetCompareMatchMode(CHANNEL_A,SET_AT_TOP_CLEAR_AT_COMPARE);
				vTimer1_SetICRValue(65535);
				vTimer1_Initpostbuild(Fast_PWM_ICR1mode,Timer_prescaler8);
				u8Local_PressedKey = NOT_PRESSED;

				do{
					u8ADC_StartSingleConversionSynch(ADC_SingleEndedChannel1,&u16Local_ADCresult);
					u8Local_Temperature = u8TempSensor_GetValue(u16Local_ADCresult);
					u16Local_DCmapCW = (uint16_t) s32Map(20,40,0,65535,u8Local_Temperature);
					u8Timer1_SetCompValue(CHANNEL_A,u16Local_DCmapCW);
					u8Local_PressedKey = u8Keypad_GetPressedKey();
				}while(u8Local_PressedKey == NOT_PRESSED);

				u8Local_PressedKey = NOT_PRESSED;
				u8Timer1_SetCompareMatchMode(CHANNEL_A,NORMAL_OPERATION);
				vTimer1_Stop();
				vDCMotor_Stop();
				u16Local_ADCresult = 0;
				u16Local_DCmapCW = 0;
				u8Local_Temperature = 0;
			}

			/*Rotate counter clockwise*/
		}else if(u8Local_PressedKey == '2')
		{
			u8Local_PressedKey = 0;
			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
			vLCD_SendString("SpeedControl 1.F");
			vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
			vLCD_SendString("2.Potent 3.LM35");

			do{
				u8Local_PressedKey = u8Keypad_GetPressedKey();
				if(u8Local_PressedKey - '0' <= 0  || u8Local_PressedKey - '0' > 3)
					u8Local_PressedKey = NOT_PRESSED;
			}while(u8Local_PressedKey == NOT_PRESSED);

			/*Full speed*/
			if(u8Local_PressedKey == '1')
			{
				vDCMotor_RotateCCW();
				u8Local_PressedKey = NOT_PRESSED;
				vLCD_ClearDisplay();
				vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
				vLCD_SendString("To Stop Press");
				vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
				vLCD_SendString("any key");
				do{
					u8Local_PressedKey = u8Keypad_GetPressedKey();
				}while(u8Local_PressedKey == NOT_PRESSED);
				vDCMotor_Stop();
				u8Local_PressedKey = NOT_PRESSED;
			}
			else if(u8Local_PressedKey == '2')    /*Potentiometer speed control*/
			{
				vLCD_ClearDisplay();
				vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
				vLCD_SendString("To Stop Press");
				vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
				vLCD_SendString("any key");
				u8Timer2_SetCompareMatchMode(SET_AT_TOP_CLEAR_AT_COMPARE);
				vTimer2_Initpostbuild(Fast_PWMmode,Timer2_prescaler8);
				u8Local_PressedKey = NOT_PRESSED;

				do{
					u8ADC_StartSingleConversionSynch(ADC_SingleEndedChannel0,&u16Local_ADCresult);
					u8Local_DCmapCCW = (uint8_t) s32Map(0,1023,0,255,u16Local_ADCresult);
					vTimer2_SetCompMatchValue(u8Local_DCmapCCW);
					u8Local_PressedKey = u8Keypad_GetPressedKey();
				}while(u8Local_PressedKey == NOT_PRESSED);

				u8Local_PressedKey = NOT_PRESSED;
				u8Timer2_SetCompareMatchMode(NORMAL_OPERATION);
				vTimer2_Stop();
				vDCMotor_Stop();
				u16Local_ADCresult = 0;
				u8Local_DCmapCCW = 0;
			}
			else if(u8Local_PressedKey == '3')    /*LM35 (Temperature) speed control*/
			{
				vLCD_ClearDisplay();
				vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
				vLCD_SendString("To Stop Press");
				vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
				vLCD_SendString("any key");
				u8Timer2_SetCompareMatchMode(SET_AT_TOP_CLEAR_AT_COMPARE);
				vTimer2_Initpostbuild(Fast_PWMmode,Timer2_prescaler8);
				u8Local_PressedKey = NOT_PRESSED;

				do{
					u8ADC_StartSingleConversionSynch(ADC_SingleEndedChannel1,&u16Local_ADCresult);
					u8Local_Temperature = u8TempSensor_GetValue(u16Local_ADCresult);
					u8Local_DCmapCCW = (uint8_t) s32Map(20,40,0,255,u8Local_Temperature);
					vTimer2_SetCompMatchValue(u8Local_DCmapCCW);
					u8Local_PressedKey = u8Keypad_GetPressedKey();
				}while(u8Local_PressedKey == NOT_PRESSED);

				u8Local_PressedKey = NOT_PRESSED;
				u8Timer2_SetCompareMatchMode(NORMAL_OPERATION);
				vTimer2_Stop();
				vDCMotor_Stop();
				u16Local_ADCresult = 0;
				u8Local_DCmapCCW = 0;
			}
		}
		break;
		/*Servo Motor Case*/
		case '3':
			u8Local_PressedKey = NOT_PRESSED;
			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
			vLCD_SendString("Set Angle: ");
			vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);

			while(1)
			{

				do{
					u8Local_ServoAngleArray[u8Local_Iterator] = u8Keypad_GetPressedKey();
					if((u8Local_ServoAngleArray[u8Local_Iterator] - '0' < 0) || (u8Local_ServoAngleArray[u8Local_Iterator] - '0' > 9))
					{
						if(u8Local_ServoAngleArray[u8Local_Iterator] == 'A')
						{
							u8Local_PressedKey = 'A';
							break;
						}else
							u8Local_ServoAngleArray[u8Local_Iterator] = NOT_PRESSED;
					}
				}while(u8Local_ServoAngleArray[u8Local_Iterator] == NOT_PRESSED);

				if(u8Local_PressedKey == 'A')
					break;
				else
				{
					vLCD_SendCharacter(u8Local_ServoAngleArray[u8Local_Iterator]);
					u8Local_Iterator++;
					if(u8Local_Iterator >= 3)
						break;
				}

			}
			u8Local_PressedKey = NOT_PRESSED;
			u8Local_ServoAngle = (uint16_t)ConvertToint((char*)u8Local_ServoAngleArray);

			u8ServoMotor_SetAngle(B_CHANNEL,u8Local_ServoAngle);
			u8Local_ServoAngleArray[0] = NOT_PRESSED;
			u8Local_ServoAngleArray[1] = NOT_PRESSED;
			u8Local_ServoAngleArray[2] = NOT_PRESSED;

			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
			vLCD_SendString("To Stop Press");
			vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
			vLCD_SendString("any key");
			do{
				u8Local_PressedKey = u8Keypad_GetPressedKey();
			}while(u8Local_PressedKey == NOT_PRESSED);

			vServoMotor_Stop();
			u8Local_PressedKey = NOT_PRESSED;
			u8Local_Iterator = 0;
			break;
		}
		if(u8Local_PressedKey == '4')
		{
			vPORT_Init();
			break;
		}
	}
}
