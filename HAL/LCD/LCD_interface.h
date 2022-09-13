/*
 * LCD_interface.h
 *
 *  	Created on: 24/08/2022
 *      Author: Mohamed Hussein
 *      Layer: HAL
 */

#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H

/*ROWs*/
#define LCD_ROW0            0
#define LCD_ROW1            1

/*Columns*/
#define LCD_COL0            0
#define LCD_COL1            1
#define LCD_COL2            2
#define LCD_COL3            3
#define LCD_COL4            4
#define LCD_COL5            5
#define LCD_COL6            6
#define LCD_COL7            7
#define LCD_COL8            8
#define LCD_COL9            9
#define LCD_COL10           10
#define LCD_COL11           11
#define LCD_COL12           12
#define LCD_COL13           13
#define LCD_COL14           14
#define LCD_COL15           15

void vLCD_Init(void);

void vLCD_SendCommand(unsigned char u8Copy_Command);
void vLCD_ClearDisplay(void);

void vLCD_SendCharacter(unsigned char u8Copy_Character);
void vLCD_SendString(const char* pchCopy_String);
void vLCD_CreateCustomunCharacter(const char *u8Copy_Pattern, unsigned char u8Copy_Location, unsigned char u8Copy_Row, unsigned char u8Copy_Col);

void vLCD_GoToRowCol (unsigned char u8Copy_Row, unsigned char u8Copy_Col);

void vLCD_SendNumber(signed long int s32Copy_Number);

#endif /* ECUAL_LCD_LCD_INTERFACE_H_ */
