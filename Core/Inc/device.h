/*
 * device.h
 *
 *  Created on: 13-Jun-2021
 *      Author: elvez
 */

#ifndef INC_DEVICE_H_
#define INC_DEVICE_H_

#include "com.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "debugger.h"

extern ADC_HandleTypeDef hadc1;

void processCMD(char* command_);

void runDevice(MultimeterTypedef mul_,
		WaveGeneratorTypedef wg_, PowerSourceTypedef ps_, OscilloscopeTypedef osc_);

void halt(uint32_t time);

uint16_t getADCvalue(void);

int parseInt(char c);

#endif /* INC_DEVICE_H_ */
