/*
 * Keypad_configuration.h
 *
 *  	Created on: 24/08/2022
 *      Author: Mohamed Hussein
 *      Layer: HAL
 */

#ifndef _KEYPAD_CONFIGURATION_H
#define _KEYPAD_CONFIGURATION_H

#define Keypad_PORT           DIO_PORTC

#define Keypad_COL0           DIO_PIN0
#define Keypad_COL1           DIO_PIN1
#define Keypad_COL2           DIO_PIN2
#define Keypad_COL3           DIO_PIN3

#define Keypad_ROW0           DIO_PIN4
#define Keypad_ROW1           DIO_PIN5
#define Keypad_ROW2           DIO_PIN6
#define Keypad_ROW3           DIO_PIN7

#define Keypad_NoPressedKey         0x00

#define Keypad_Array  {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A','0','=','+'}}

#endif /* ECUAL_KEYPAD_KEYPAD_CONFIGURATION_H_ */
