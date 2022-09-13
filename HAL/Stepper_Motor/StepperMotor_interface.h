/*
 * Name: Mohamed Hussein
 * Layer: HAL
 * Version: V1.0 - 15/10/2021
 *
 */

#ifndef _STEPPERMOTOR_INTERFACE_H
#define _STEPPERMOTOR_INTERFACE_H


/* Fucntions Prototype */
void vSepperMotor_Init(void);

void vSepperMotor_RotateCW (void);
void vSepperMotor_RotateCCW (void);

void vSepperMotor_RotateCWatAngle (short u16Copy_Angle);
void vSepperMotor_RotateCCWatAngle (short u16Copy_Angle);

void vSepperMotor_Stop(void);

#endif
