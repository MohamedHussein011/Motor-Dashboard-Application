/*
 * LCD_configuration.h
 *
 *  	Created on: 24/08/2022
 *      Author: Mohamed Hussein
 *      Layer: HAL
 */

#ifndef _LCD_CONFIGURATION_H
#define _LCD_CONFIGURATION_H

/* Modes of Initialization
   Options:
		1: EightBit_Init
		2: FourBit_Init
 */
#define LCD_InitMode         EightBit_Init

/* Number of Lines
   Options:
		1: One_Line
		2: Two_Lines
 */
#define LCD_NumbersOfLines         Two_Lines

/* Font Size
   Options:
		1: FiveEight_Size
		2: FiveEleven_Size
 */
#define LCD_Font_Size        FiveEight_Size

/* Display On/Off
   Options:
		1: Display_ON
		2: Display_OFF
 */
#define LCD_Display        Display_ON

/* Cursor On/Off
   Options:
		1: Cursor_ON
		2: Cursor_OFF
 */
#define LCD_Cursor       Cursor_OFF

/* Blinking On/Off
   Options:
		1: Blinking_ON
		2: Blinking_OFF
 */
#define LCD_Blinking       Blinking_OFF

/*Control Port*/
#define LCD_CTRL_PORT       DIO_PORTA
/*Control Pins*/
#define LCD_RS_PIN          DIO_PIN5
#define LCD_RW_PIN          DIO_PIN6
#define LCD_EN_PIN          DIO_PIN7
/*Data Port*/
#define LCD_DATA_PORT       DIO_PORTB




#endif /* ECUAL_LCD_LCD_CONFIGURATION_H_ */
