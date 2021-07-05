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

//HIGH and LOW typedef
#define HIGH	GPIO_PIN_RESET
#define LOW		GPIO_PIN_SET

//UART typedef
extern UART_HandleTypeDef huart2;

/*
 * Send Debug message
 *
 * Send formatted debug message to UART2 serial.
 *
 * @params : format
 * @return : none
 */
void debug(char* format, ...);

/*
 * Blink led
 *
 * Blinks led with given number of turns and delay between them
 *
 * @params : Turns(uint8_t), Delay(uint32_t)
 * @return : none
 */
void blink(uint8_t turns, uint32_t delay);

/*
 * Send debug message
 *
 * Send debug byte
 *
 * @params : Byte(uint8_t)
 * @return : none
 */
void debugSend(uint8_t data);

#endif /* INC_DEBUGGER_H_ */
