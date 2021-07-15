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
#include "main.h"
#include "debugger.h"
#include "DWT_Delay.h"

//ADC typedef extern
extern ADC_HandleTypeDef hadc1;

//Timer typedef extern
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;

//Channel enum
typedef enum {
	MUL_CH1,
	MUL_CH2,
	OSC_CH1,
	OSC_CH2
} ChannelTypedef;

//PWM channel enum
typedef enum {
	PWM1,
	PWM2,
	PWM3,
	PWM4,
	PWM5,
	PWM6
} PWMChannelTypedef;

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

/*
 * Sample one value and send
 *
 * Samples one value from ADC and sends with the given delay
 *
 * @params : DelayMilliseconds(uint32_t)
 * @return : none
 */
void sampleAndSend(ChannelTypedef channel);

/*
 * Change ADC channel
 *
 * Change ADC channel to another channel for sampling
 *
 * @params : Channel(Channel typedef)
 * @return : none
 */
void selectChannel(ChannelTypedef channel);

/*
 * Start PWM
 *
 * Start the pwm output on given channel with given duty cycle
 *
 * @params : Channel(PWMChannelTypedef), Duty cyclt(int)
 * @return : none
 */
void startPWM(PWMChannelTypedef channel, int dutyCycle);

/*
 * Stop PWM
 *
 * Stop PWM output on given channel
 *
 * @params : Channel(PWMChannelTypedef)
 * @return : none
 */
void stopPWM(PWMChannelTypedef channel);
#endif /* INC_DEVICE_H_ */
