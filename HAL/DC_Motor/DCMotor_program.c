/*
 * Name: Mohamed Hussein
 * Layer: HAL
 * Version: V1.0 - 15/10/2021
 *
 */

/* Files Inclusion */

/* 1. User Defined Libraries */
#include "../../Library/STD_TYPE.h"
#include "../../Library/BIT_MATH.h"

/* 3. MCAL Files */
#include "../../MCAL/DIO/DIO_interface.h"

/* 4. ECUAL Files */
#include "DCMotor_configuration.h"
#include "DCMotor_interface.h"

/* Functions Definitions */
void vDCMotor_Init(void)
{
	u8DIO_PinDir (DCMotor_PORT, DCMotor_PIN0, DIO_OUTPUT);
	u8DIO_PinDir (DCMotor_PORT, DCMotor_PIN1, DIO_OUTPUT);
}

void vDCMotor_RotateCW (void)
{
	u8DIO_PinVal(DCMotor_PORT, DCMotor_PIN1, DIO_LOW);
	u8DIO_PinVal(DCMotor_PORT, DCMotor_PIN0, DIO_HIGH);
}
void vDCMotor_RotateCCW (void)
{
	u8DIO_PinVal(DCMotor_PORT, DCMotor_PIN0, DIO_LOW);
	u8DIO_PinVal(DCMotor_PORT, DCMotor_PIN1, DIO_HIGH);
}

void vDCMotor_Stop(void)
{
	u8DIO_PinVal (DCMotor_PORT, DCMotor_PIN0, DIO_LOW);
	u8DIO_PinVal (DCMotor_PORT, DCMotor_PIN1, DIO_LOW);
}

uint8_t u8DCMotor_Init(EN_PORT_t PortId0, EN_PORT_t PortId1, EN_PIN_t PinId0, EN_PIN_t PinId1)
{
	uint8_t u8Local_Error = OK;

	if(PortId0 <= DIO_PORTD && PortId1 <= DIO_PORTD && PinId0 <= DIO_PIN7 && PinId1 <= DIO_PIN7)
	{
		u8DIO_PinDir (PortId0, PinId0, DIO_OUTPUT);
		u8DIO_PinDir (PortId1, PinId1, DIO_OUTPUT);
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}
uint8_t u8DCMotor_RotateCW (EN_PORT_t PortId0, EN_PORT_t PortId1, EN_PIN_t PinId0, EN_PIN_t PinId1)
{
	uint8_t u8Local_Error = OK;

	if(PortId0 <= DIO_PORTD && PortId1 <= DIO_PORTD && PinId0 <= DIO_PIN7 && PinId1 <= DIO_PIN7)
	{
		u8DIO_PinVal(PortId1, PinId1, DIO_LOW);
		u8DIO_PinVal(PortId0, PinId0, DIO_HIGH);
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

uint8_t u8DCMotor_RotateCCW (EN_PORT_t PortId0, EN_PORT_t PortId1, EN_PIN_t PinId0, EN_PIN_t PinId1)
{
	uint8_t u8Local_Error = OK;

	if(PortId0 <= DIO_PORTD && PortId1 <= DIO_PORTD && PinId0 <= DIO_PIN7 && PinId1 <= DIO_PIN7)
	{
		u8DIO_PinVal(PortId0, PinId0, DIO_LOW);
		u8DIO_PinVal(PortId1, PinId1, DIO_HIGH);
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

uint8_t u8DCMotor_Stop(EN_PORT_t PortId0, EN_PORT_t PortId1, EN_PIN_t PinId0, EN_PIN_t PinId1)
{
	uint8_t u8Local_Error = OK;

	if(PortId0 <= DIO_PORTD && PortId1 <= DIO_PORTD && PinId0 <= DIO_PIN7 && PinId1 <= DIO_PIN7)
	{
		u8DIO_PinVal (PortId0, PinId0, DIO_LOW);
		u8DIO_PinVal (PortId1, PinId1, DIO_LOW);
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}
