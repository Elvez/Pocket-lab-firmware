/*
 * device.h
 *
 *  Created on: 13-Jun-2021
 *      Author: elvez
 */

#ifndef INC_DEVICE_H_
#define INC_DEVICE_H_

#include "com.h"
#include "debugger.h"

void processCMD(uint8_t* command_);

void runDevice(MultimeterTypedef mul_,
		WaveGeneratorTypedef wg_, PowerSourceTypedef ps_, OscilloscopeTypedef osc_);

#endif /* INC_DEVICE_H_ */
