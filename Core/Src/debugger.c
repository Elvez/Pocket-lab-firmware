/*
 * debugger.c
 *
 *  Created on: May 25, 2021
 *      Author: elvez
 */


#include "debugger.h"

void debug(char* format, ...) {
	//Message to send
	char message[100];

	//Arguments
	va_list args;

	//Get arguments from format
	va_start(args, format);

	//Copy arguments to the message
	vsprintf(message, format, args);

	//Send message
	HAL_UART_Transmit(&huart2, (uint8_t *)message, strlen(message), HAL_MAX_DELAY);
	va_end(args);
}

void debugSend(uint8_t data) {
	//Send byte
	HAL_UART_Transmit(&huart2, &data, 1, HAL_MAX_DELAY);
}

void blink(uint8_t turns, uint32_t delay) {
	for(uint8_t iter = 0; iter < 2*turns; iter++)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_Delay(delay);
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, LOW);
}

