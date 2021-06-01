/*
 * bluetooth.c
 *
 *  Created on: May 24, 2021
 *      Author: elvez
 */

#include "bluetooth.h"

void sendPacket(uint8_t* packet, uint16_t len) {
	HAL_UART_Transmit(&huart1, packet, len, HAL_MAX_DELAY);
}

void receivePacket(uint8_t* packet, uint16_t len) {
	HAL_UART_Receive(&huart1, packet, len, HAL_MAX_DELAY);
}
