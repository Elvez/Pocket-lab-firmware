/*
 * com.c
 *
 *  Created on: May 25, 2021
 *      Author: elvez
 */

#include "com.h"
#include <stdbool.h>


void sendPacket(uint8_t* packet, uint16_t len) {
	HAL_UART_Transmit(&huart1, packet, len, HAL_MAX_DELAY);
}

void receivePacket(uint8_t* packet, uint16_t len) {
	HAL_UART_Receive(&huart1, packet, len, HAL_MAX_DELAY);
}

void sendACK(uint8_t ltf) {
	uint8_t ackBuffer[2];

	ackBuffer[0] = ACK;
	ackBuffer[1] = ltf;
	sendPacket(ackBuffer, 2);
}

void sendNACK(void) {
	uint8_t nack = NACK;

	sendPacket(&nack, 1);
}

void sendFormat(char* format, ...) {
	char message[20];
	va_list args;
	va_start(args, format);
	vsprintf(message, format, args);

	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), HAL_MAX_DELAY);
	va_end(args);
}

