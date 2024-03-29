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
#define		OSCILLOSCOPE		'O'
#define		PWM_GENERATOR		'G'
#define		STATE_HIGH			'H'
#define		STATE_LOW			'L'

//CRC typedef
extern CRC_HandleTypeDef hcrc;

//UART typedef
extern UART_HandleTypeDef huart1;

//SPI for AD9833, wave-generator-1
SPI_HandleTypeDef hspi1;

//SPI for AD9833, wave-generator-2
SPI_HandleTypeDef hspi2;

//Device On/Off state
typedef enum {
	STATE_OFF = 0,
	STATE_ON = 1
} StateTypedef;

//Wave types
typedef enum {
	SINE = 1,
	SQUARE = 2,
	TRIANG = 3
} WaveTypedef;


//Time unit types
typedef enum {
	MICRO = 1,
	MILLI = 2,
	SECOND = 3
} UnitTypedef;

//Multimeter typedef
typedef struct {
	StateTypedef state_;
	uint8_t source_;
} MultimeterTypedef;

//Wave generator typedef
typedef struct {
	uint8_t source_;
	StateTypedef state;
	WaveTypedef wave_;
	float phase_;
	float period_;
	bool isWaiting_;
} WaveGeneratorTypedef;

//Oscilloscope typedef
typedef struct {
	StateTypedef state_;
} OscilloscopeTypedef;

//PWM typedef
typedef struct {
	StateTypedef state_;
	int dutyCycle_;
} PWMTypedef;

/*
 * Send Packet
 *
 * Sends packet to the main serial
 *
 * @params : Packet pointer(uint8_t*), length(uint8_t)
 * @return : none
 */
void sendPacket(uint8_t* packet, uint16_t len);

/*
 * Eeceive Packet
 *
 * Gets packet from the main serial
 *
 * @params : Packet pointer(uint8_t*), length(uint8_t)
 * @return : none
 */
void receivePacket(uint8_t* packet, uint16_t len);

/*
 * Send Acknowledge buffer
 *
 * Sends ACK buffer with Length to follow
 *
 * Stauts - UNUSED
 *
 * @params : Length to follow(uint8_t)
 * @return : none
 */
void sendACK(uint8_t ltf);

/*
 * Send Not Acknowledged buffer
 *
 * Sends NACK buffer with Length to follow
 *
 * Stauts - UNUSED
 *
 * @params : none
 * @return : none
 */
void sendNACK(void);

/*
 * Send Format buffer
 *
 * Sends format buffer to the main serial
 *
 *
 * @params : formats
 * @return : none
 */
void sendFormat(char* format, ...);

/*
 * Write 16-bit word to SPI1
 *
 * Writes given 16-bit word to SPI MOSI
 *
 * @params : Word(uint16_t)
 * @return : none
 */
void writeSPI1(uint16_t word);

/*
 * Write 16-bit word to SPI2
 *
 * Writes given 16-bit word to SPI MOSI
 *
 * @params : Word(uint16_t)
 * @return : none
 */
void writeSPI2(uint16_t word);

#endif /* INC_COM_H_ */
