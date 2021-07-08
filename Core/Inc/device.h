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

//ADC typedef extern
extern ADC_HandleTypeDef hadc1;

/*
 * Process command buffer.
 *
 * Processes command buffer and stores data into the correct device_def
 *
 * @params : Command buffer(char*)
 * @return : none
 */
void processCMD(char* command_);

/*
 * Main loop
 *
 * Runs indefinitely in main.c
 *
 * @params : All device_defs
 * @return : none
 */
void runDevice(MultimeterTypedef mul_, WaveGeneratorTypedef wg_, PowerSourceTypedef ps_,
		OscilloscopeTypedef osc1_, OscilloscopeTypedef osc2_, PWMTypedef* pwm_);

/*
 * Millisecond delay
 *
 * Gives a millisecond delay
 *
 * @params : Delay(uint32_t)
 * @return : none
 */
void delayMS(uint32_t time);

/*
 * Get ADC value
 *
 * Returns ADC sampled value
 *
 * @params : none
 * @return : 16-bit int
 */
uint16_t getADCvalue(void);

/*
 * Parser
 *
 * Makes float from character
 *
 * @params : Character(char)
 * @return : float
 */
float parseFloat(char c);

/*
 * Parser
 *
 * Makes int from character
 *
 * @params : Character(char)
 * @return : int
 */
int parseInt(char c);

/*
 * Reset device_def
 *
 * Sets all device parameters to default
 *
 * @params : Device type(char)
 * @return : none
 */
void resetParams(char device);

/*
 * Kills oscilloscope task
 *
 * Stops sending packets if sending
 *
 * @params : none
 * @return : none
 */
void killOscilloscope(void);

/*
 * Kills multimeter task
 *
 * Stops sending packets if sending
 *
 * @params : none
 * @return : none
 */
void killMultimeter(void);

#endif /* INC_DEVICE_H_ */
