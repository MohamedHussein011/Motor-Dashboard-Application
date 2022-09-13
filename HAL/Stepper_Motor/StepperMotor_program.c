/*
 * Name: Mohamed Hussein
 * Layer: HAL
 * Version: V1.0 - 15/10/2021
 *
 */

/* Files Inclusion */

/* 1. User Defined Libraries */
#include "../../Library/BIT_MATH.h"

#include "util/delay.h"

/* 3. MCAL Files */
#include "../../MCAL/DIO/DIO_interface.h"
#include "StepperMotor_configuration.h"

/* 4. ECUAL Files */
#include "StepperMotor_interface.h"

/* Functions Definitions */
/*using Darlington Pair*/
void vSepperMotor_Init(void)
{
	u8DIO_PinDir (StepperMotor_PORT, StepperMotor_Blue, DIO_OUTPUT);
	u8DIO_PinDir (StepperMotor_PORT, StepperMotor_Pink, DIO_OUTPUT);
	u8DIO_PinDir (StepperMotor_PORT, StepperMotor_Yellow, DIO_OUTPUT);
	u8DIO_PinDir (StepperMotor_PORT, StepperMotor_Orange, DIO_OUTPUT);
}

void vSepperMotor_RotateCW (void)
{
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_LOW);
	_delay_ms(5);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_LOW);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_HIGH);
	_delay_ms(5);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_LOW);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_HIGH);
	_delay_ms(5);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_LOW);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_HIGH);
	_delay_ms(5);

}
void vSepperMotor_RotateCCW (void)
{

	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_LOW);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_HIGH);
	_delay_ms(5);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_LOW);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_HIGH);
	_delay_ms(5);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_LOW);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_HIGH);
	_delay_ms(5);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_HIGH);
	u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_LOW);
	_delay_ms(5);

}
void vSepperMotor_RotateCWatAngle (short u16Copy_Angle)
{
	short u16Local_Iterator = 0;
	short u16Local_AngleIteration = (uint16_t)((((uint32_t)u16Copy_Angle * 100000UL)/17578UL) / 4UL);

	for(u16Local_Iterator = 0; u16Local_Iterator < u16Local_AngleIteration; u16Local_Iterator++)
	{
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_LOW);
		_delay_ms(5);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_LOW);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_HIGH);
		_delay_ms(5);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_LOW);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_HIGH);
		_delay_ms(5);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_LOW);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_HIGH);
		_delay_ms(5);
	}

}

void vSepperMotor_RotateCCWatAngle (short u16Copy_Angle)
{
	short u16Local_Iterator = 0;
	short u16Local_AngleIteration =  (uint16_t)((((uint32_t)u16Copy_Angle * 100000UL)/17578UL) / 4UL);

	for(u16Local_Iterator = 0; u16Local_Iterator < u16Local_AngleIteration; u16Local_Iterator++)
	{
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_LOW);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_HIGH);
		_delay_ms(5);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_LOW);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_HIGH);
		_delay_ms(5);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_LOW);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_HIGH);
		_delay_ms(5);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Blue,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Pink,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Yellow,DIO_HIGH);
		u8DIO_PinVal(StepperMotor_PORT,StepperMotor_Orange,DIO_LOW);
		_delay_ms(5);
	}
}

void vSepperMotor_Stop(void)
{
	u8DIO_PinDir (StepperMotor_PORT, StepperMotor_Blue, DIO_HIGH);
	u8DIO_PinDir (StepperMotor_PORT, StepperMotor_Pink, DIO_HIGH);
	u8DIO_PinDir (StepperMotor_PORT, StepperMotor_Yellow, DIO_HIGH);
	u8DIO_PinDir (StepperMotor_PORT, StepperMotor_Orange, DIO_HIGH);
}
