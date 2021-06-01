/*
 * bluetooth.h
 *
 *  Created on: May 24, 2021
 *      Author: elvez
 */

#ifndef INC_BLUETOOTH_H_
#define INC_BLUETOOTH_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "string.h"
#include "debugger.h"


extern UART_HandleTypeDef huart1;

void sendPacket(uint8_t* packet, uint16_t len);

void receivePacket(uint8_t* packet, uint16_t len);






#endif /* INC_BLUETOOTH_H_ */
