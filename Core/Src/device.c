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

uint8_t multimeterVal_ = 0;

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

void runDevice(MultimeterTypedef mul_,
		WaveGeneratorTypedef wg_, PowerSourceTypedef ps_, OscilloscopeTypedef osc_) {

	if(mul_.state_ == STATE_ON) {

	} else if(osc_.state_ == STATE_ON) {

	} else {

	}
}

