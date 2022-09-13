/*
 * Name: Mohamed Hussein
 * Layer: HAL
 * Version: V1.0 - 15/10/2021
 *
 */

#ifndef _DCMOTOR_INTERFACE_H
#define _DCMOTOR_INTERFACE_H


/* Fucntions Prototype */
void vDCMotor_Init(void);

void vDCMotor_RotateCW (void);
void vDCMotor_RotateCCW (void);

void vDCMotor_Stop(void);

uint8_t u8DCMotor_Init(EN_PORT_t PortId0, EN_PORT_t PortId1, EN_PIN_t PinId0, EN_PIN_t PinId1);

uint8_t u8DCMotor_RotateCW (EN_PORT_t PortId0, EN_PORT_t PortId1, EN_PIN_t PinId0, EN_PIN_t PinId1);
uint8_t u8DCMotor_RotateCCW (EN_PORT_t PortId0, EN_PORT_t PortId1, EN_PIN_t PinId0, EN_PIN_t PinId1);

uint8_t u8DCMotor_Stop(EN_PORT_t PortId0, EN_PORT_t PortId1, EN_PIN_t PinId0, EN_PIN_t PinId1);

#endif
