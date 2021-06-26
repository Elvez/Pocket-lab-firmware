/*
 * device.c
 *
 *  Created on: 13-Jun-2021
 *      Author: elvez
 */


#include "device.h"

extern MultimeterTypedef multimeter_;
extern PowerSourceTypedef powerSource_;
extern WaveGeneratorTypedef waveGenerator_;
extern OscilloscopeTypedef oscilloscope_;

uint16_t multimeterVoltVal_ = 0;
uint16_t multimeterCurrVal_ = 0;
uint16_t multimeterVal_ = 0;
uint16_t oscVal_[100];
int iter = 0;


void processCMD(uint8_t* command_) {
		uint8_t header_ = command_[0];

		if(header_ == MULTIMETER) {
		  if(command_[1] == '1') {
			  multimeter_.source_ = 1;
		  } else if(command_[1] == '2') {
			  multimeter_.source_ = 2;
		  } else {
			  debug("Bad command\n\r");
		  }
		  if(command_[2] == STATE_HIGH) {
			  multimeter_.state_ = STATE_ON;
		  } else if(command_[2] == STATE_LOW) {
			  multimeter_.state_ = STATE_OFF;
		  } else {
			  debug("Bad command\n\r");
		  }
		} else if(header_ == WAVE_GENERATOR) {

		} else if(header_ == POWER_SOURCE) {

		} else if(header_ == OSCILLOSCOPE) {

		}
}

void runDevice(MultimeterTypedef mul_, WaveGeneratorTypedef wg_, PowerSourceTypedef ps_, OscilloscopeTypedef osc_) {
	if(mul_.state_ == STATE_OFF) {
		if(mul_.source_ == 1) {
			for(uint8_t iter = 0; iter < 100; iter++) {
				oscVal_[iter] = getADCvalue();

			}
			//multimeterVoltVal_ = getADCvalue();
		} else {

		}
		//multimeterVal_ = multimeterVoltVal_;
		//sendFormat("%d!", multimeterVal_);
		//debug("%d!", multimeterVal_);
		for(uint8_t iter = 0; iter < 100; iter++) {
			debug("%d! ", oscVal_[iter]);
		}
		iter ++;
		debug("---------------------%d-----------------------\n\r", iter);
	} else if(osc_.state_ == STATE_ON) {

	} else {

	}
}

void halt(uint32_t time) {
	HAL_Delay(time);
}

uint16_t getADCvalue(void) {
	uint16_t value_ = 0;
	HAL_ADC_Start(&hadc1);

	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	value_ = HAL_ADC_GetValue(&hadc1);

	return value_;
}

