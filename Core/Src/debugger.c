/*
 * debugger.c
 *
 *  Created on: May 25, 2021
 *      Author: elvez
 */


#include "debugger.h"

void debug(char* format, ...) {
	char message[100];
	va_list args;
	va_start(args, format);
	vsprintf(message, format, args);

	HAL_UART_Transmit(&huart2, (uint8_t *)message, strlen(message), HAL_MAX_DELAY);
	va_end(args);
}

void blink(uint8_t turns, uint32_t delay) {
	for(uint8_t iter = 0; iter < 2*turns; iter++)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_Delay(delay);
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, LOW);
}

