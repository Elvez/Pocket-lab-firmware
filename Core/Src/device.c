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


void processCMD(char* command_) {
		char header_ = command_[0];
		int decimals = 0;
		bool decimalFlag = false;

		switch(header_) {
		case MULTIMETER:
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
			break;
		case WAVE_GENERATOR:
			if(command_[1] == '1') {
				waveGenerator_.source_ = 1;
			} else if(command_[1] == '2') {
				waveGenerator_.source_ = 2;
			} else {
				debug("Bad command\n\r");
			}

			if(command_[2] == STATE_HIGH) {
				waveGenerator_.state = STATE_ON;
				switch(command_[3]) {
					case '1':
						waveGenerator_.wave_ = SINE;
						break;
					case '2':
						waveGenerator_.wave_ = SQUARE;
						break;
					case '3':
						waveGenerator_.wave_ = TRIANG;
						break;
					default:
						break;
					}

				for(int iter = 4; command_[iter] != 'A'; iter++) {
					if(command_[iter] != '.') {
						if(decimalFlag) decimals++;
						waveGenerator_.period_ = (waveGenerator_.period_* 10) + parseInt(command_[iter]);
					} else {
						decimalFlag = true;
					}
				}

				while(decimals > 0) {
					waveGenerator_.period_ = waveGenerator_.period_ / 10;
					decimals--;
				}

				decimals = 0;
				decimalFlag = false;
			} else if(command_[2] == STATE_LOW) {
				waveGenerator_.state = STATE_OFF;
				waveGenerator_.amplitude_ = 0;
				waveGenerator_.period_ = 0;
				waveGenerator_.source_ = 1;
				waveGenerator_.wave_ = SINE;
			} else {
				debug("Bad command\n\r");
			}



			break;
		case POWER_SOURCE:
			break;
		case OSCILLOSCOPE:
			break;
		default:
			break;
		}
}

void runDevice(MultimeterTypedef mul_, WaveGeneratorTypedef wg_, PowerSourceTypedef ps_, OscilloscopeTypedef osc_) {
	if(mul_.state_ == STATE_ON) {
		if(mul_.source_ == 1) {
			multimeterVoltVal_ = getADCvalue();
		} else {

		}
		multimeterVal_ = multimeterVoltVal_;
		sendFormat("%d!", multimeterVal_);
		halt(150);
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

int parseInt(char c) {
	return c - '0';
}

