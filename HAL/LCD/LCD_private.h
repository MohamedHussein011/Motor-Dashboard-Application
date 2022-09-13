/*
 * LCD_private.h
 *
 *  	Created on: 24/08/2022
 *      Author: Mohamed Hussein
 *      Layer: HAL
 */

#ifndef _LCD_PRIVATE_H
#define _LCD_PRIVATE_H

/* Modes of Initialization
   Options:
		1: EightBit_Init
		2: FourBit_Init
 */
#define EightBit_Init         0
#define FourBit_Init          1

/* Number of Lines
   Options:
		1: One_Line
		2: Two_Lines
 */
#define One_Line         0
#define Two_Lines        1

/* Font Size
   Options:
		1: FiveEight_Size
		2: FiveEleven_Size
 */
#define FiveEight_Size        0
#define FiveEleven_Size       1

/* Display On/Off
   Options:
		1: Display_ON
		2: Display_OFF
 */
#define Display_ON        0
#define Display_OFF       1

/* Cursor On/Off
   Options:
		1: Cursor_ON
		2: Cursor_OFF
 */
#define Cursor_ON       0
#define Cursor_OFF      1

/* Blinking On/Off
   Options:
		1: Blinking_ON
		2: Blinking_OFF
 */
#define Blinking_ON       0
#define Blinking_OFF      1

/*Control Instruction*/
#define CLEAR_DISPLAY       0x01
#define RETURN_HOME         0x02
#define ENTRY_MODE_SET      0x06
#define RESET               0x30
#define CURSOR_OFFEST       0x80
#define OneLine_5x8_8Bit    0x30
#define OneLine_5x11_8Bit   0x34
#define TwoLine_5x8_8Bit    0x38
#define TwoLine_5x11_8Bit   0x3c
#define DisplayOn_CursorOn_BlinkingOn        0x0F
#define DisplayOn_CursorOn_BlinkingOff       0x0E
#define DisplayOn_CursorOff_BlinkingOn       0x0D
#define DisplayOn_CursorOff_BlinkingOff      0x0C
#define DisplayOff_CursorOn_BlinkingOn       0x0B
#define DisplayOff_CursorOn_BlinkingOff      0x0A
#define DisplayOff_CursorOff_BlinkingOn      0x09
#define DisplayOff_CursorOff_BlinkingOff     0x08



#endif /* ECUAL_LCD_LCD_PRIVATE_H_ */
