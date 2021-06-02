/*
 * com.h
 *
 *  Created on: May 25, 2021
 *      Author: elvez
 */

#ifndef INC_COM_H_
#define INC_COM_H_

#include "debugger.h"
#include "stdbool.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "string.h"


#define		FIRMWARE_VERSION	1.00
#define		DEVICE_ID			0xDD
#define		ACK					0xAA
#define		NACK				0xFF
#define		CRC_SUCCESS			0x01
#define		CRC_FAIL			0x00

#define		MULTIMETER_START	0xA1
#define		MULTIMETER_STOP		0xB1
#define		VOLTMETER			0x11
#define		AMMETER				0x12

#define 	WAVE_START			0xA2
#define		WAVE_STOP			0xB2
#define		WAVE_SOURCE_ONE		0x21
#define		WAVE_SOURCE_TWO		0x22
#define		WAVE_SIN			0xC1
#define		WAVE_SQUARE			0xC2
#define		WAVE_TRIANG			0xC3

#define 	SOURCE_START		0xA3
#define 	SOURCE_STOP			0xB3
#define		POWER_SOURCE_ONE	0x31
#define		POWER_SOURCE_TWO	0x32
#define		POWER_SOURCE_THREE	0x33
#define		POWER_SOURCE_FOUR	0x34

#define		OSC_START			0xA4
#define		OSC_STOP			0xB4
#define		OSC_CHANNEL_ONE		0xD1
#define		OSC_CHANNEL_TWO		0xD2
#define		OSC_CHANNEL_BOTH	0xD3

extern CRC_HandleTypeDef hcrc;
extern UART_HandleTypeDef huart1;

void sendPacket(uint8_t* packet, uint16_t len);

void receivePacket(uint8_t* packet, uint16_t len);

void sendACK(uint8_t ltf);

void sendNACK(void);

void getCommand(void);

uint8_t verifyCRC(uint8_t* commandData, uint32_t len, uint32_t crcHost);



#endif /* INC_COM_H_ */
