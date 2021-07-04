/*
 * debugger.h
 *
 *  Created on: May 25, 2021
 *      Author: elvez
 */

#ifndef INC_DEBUGGER_H_
#define INC_DEBUGGER_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#define HIGH	GPIO_PIN_RESET
#define LOW		GPIO_PIN_SET

extern UART_HandleTypeDef huart2;


void debug(char* format, ...);

void blink(uint8_t turns, uint32_t delay);

void debugSend(uint8_t data);






#endif /* INC_DEBUGGER_H_ */
