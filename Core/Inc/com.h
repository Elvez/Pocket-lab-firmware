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
#include "stdarg.h"
#include <stdlib.h>



#define		FIRMWARE_VERSION	1.00
#define		DEVICE_ID			0xDD
#define		ACK					0xAA
#define		NACK				0xFF
#define		WAITING				1
#define		FREE				0

#define		MULTIMETER			'M'
#define 	WAVE_GENERATOR		'W'
#define 	POWER_SOURCE		'P'
#define		OSCILLOSCOPE		'O'
#define		STATE_HIGH			'H'
#define		STATE_LOW			'L'

extern CRC_HandleTypeDef hcrc;
extern UART_HandleTypeDef huart1;

typedef enum {
	STATE_OFF = 0,
	STATE_ON = 1
} StateTypedef;

typedef enum {
	SINE = 1,
	SQUARE = 2,
	TRIANG = 3
} WaveTypedef;

typedef enum {
	MICRO = 1,
	MILLI = 2,
	SECOND = 3
} UnitTypedef;

typedef struct {
	StateTypedef state_;
	uint8_t source_;
} MultimeterTypedef;

typedef struct {
	uint8_t source_;
	StateTypedef state_;
	float value_;
} PowerSourceTypedef;

typedef struct {
	uint8_t source_;
	StateTypedef state;
	WaveTypedef wave_;
	float amplitude_;
	float period_;
} WaveGeneratorTypedef;

typedef struct {
	uint8_t channel_;
	StateTypedef state_;
	uint16_t period_;
	UnitTypedef unit_;
} OscilloscopeTypedef;





void sendPacket(uint8_t* packet, uint16_t len);

void receivePacket(uint8_t* packet, uint16_t len);

void sendACK(uint8_t ltf);

void sendNACK(void);

void sendFormat(char* format, ...);





#endif /* INC_COM_H_ */
