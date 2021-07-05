/*
 * device.c
 *
 *  Created on: 13-Jun-2021
 *      Author: elvez
 */


#include "device.h"

//Device typedefs
extern MultimeterTypedef multimeter_;
extern PowerSourceTypedef powerSource_;
extern WaveGeneratorTypedef waveGenerator_;
extern OscilloscopeTypedef oscilloscopeCh1_;
extern OscilloscopeTypedef oscilloscopeCh2_;

//Multimeter voltmeter value
uint16_t multimeterVoltVal_ = 0;

//Multimeter ammeter value
uint16_t multimeterCurrVal_ = 0;

//Oscilloscope plot
uint16_t oscVal_[1000];


void processCMD(char* command_) {
	//Command buffer's first character.
	char header_ = command_[0];

	//Number of digits after decimal
	int decimals = 0;

	//Is there decimal in the command
	bool decimalFlag = false;

	//General use iterator
	int iter = 0;

	switch(header_) {
	//Multimeter command
	case MULTIMETER:
		//Store source
		multimeter_.source_ = parseInt(command_[1]);

		//Store state
		if(command_[2] == STATE_HIGH) {
		  multimeter_.state_ = STATE_ON;
		} else if(command_[2] == STATE_LOW) {
		  multimeter_.state_ = STATE_OFF;
		} else {
		  debug("Bad command\n\r");
		}

		break;

	//Wave generator command
	case WAVE_GENERATOR:
		//Store source
		waveGenerator_.source_ = parseInt(command_[1]);

		//Store state
		if(command_[2] == STATE_HIGH) {
			waveGenerator_.state = STATE_ON;

			//Store wave type
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

			//Parse and store wave phase as integer
			for(iter = 4; command_[iter] != 'A'; iter++) {
				if(command_[iter] != '.') {
					if(decimalFlag) decimals++;
					waveGenerator_.period_ = (waveGenerator_.period_* 10) + parseFloat(command_[iter]);
				} else {
					decimalFlag = true;
				}
			}

			//Convert integer to float
			while(decimals > 0) {
				waveGenerator_.period_ = waveGenerator_.period_ / 10;
				decimals--;
			}

			//Reset vars
			decimals = 0;
			decimalFlag = false;
			iter++;

			//Parse and store wave amplitude as integer
			while(command_[iter] != '-') {
				if(command_[iter] != '.') {
					if(decimalFlag) decimals++;
					waveGenerator_.amplitude_ = (waveGenerator_.amplitude_ * 10) + parseFloat(command_[iter]);
				} else {
					decimalFlag = true;
				}
				iter++;
			}

			//Convert integer to float
			while(decimals > 0) {
				waveGenerator_.amplitude_ = waveGenerator_.amplitude_ / 10;
				decimals--;
			}
		} else if(command_[2] == STATE_LOW) {
			//Store state
			waveGenerator_.state = STATE_OFF;
			resetParams(WAVE_GENERATOR);
		} else {
			debug("Bad command\n\r");
		}

		//Reset vars
		decimals = 0;
		decimalFlag = false;
		iter = 0;

		break;

	//Power source command
	case POWER_SOURCE:
		//Store source
		powerSource_.source_ = parseInt(command_[1]);

		//Store state
		if(command_[2] == STATE_HIGH) {
			powerSource_.state_ = STATE_ON;

			//Store amplitude as integer
			for(iter = 3; command_[iter] != '-'; iter++) {
				if(command_[iter] != '.') {
					if(decimalFlag) decimals++;
					powerSource_.value_ = (powerSource_.value_ * 10) + parseFloat(command_[iter]);
				} else {
					decimalFlag = true;
				}
			}

			//Convert integer to float
			while(decimals > 0) {
				powerSource_.value_ = powerSource_.value_ / 10;
				decimals--;
			}
		} else if(command_[2] == STATE_LOW) {
			//Store state and reset params
			powerSource_.state_ = STATE_OFF;
			resetParams(POWER_SOURCE);
		} else {
			debug("Bad command\n\r");
		}

		//Reset vars
		decimals = 0;
		decimalFlag = false;
		iter = 0;

		break;

	//Oscilloscope command
	case OSCILLOSCOPE:
		//Store channel
		if(command_[1] == '1') {
			if(command_[2] == STATE_HIGH) {
				//Store state
				oscilloscopeCh1_.state_ = STATE_ON;

				//Store period as integer
				for(int iter = 3; command_[iter] != 'U'; iter++) {
					if(command_[iter] != '.') {
						if(decimalFlag) decimals++;
						oscilloscopeCh1_.period_ = (oscilloscopeCh1_.period_ * 10) + parseFloat(command_[iter]);
					} else {
						decimalFlag = true;
					}
				}

				//Convert to float
				while(decimals > 0) {
					oscilloscopeCh1_.period_ = oscilloscopeCh1_.period_ / 10;
					decimals--;
				}

				//Store period unit
				switch(command_[iter]) {
				case '1':
					oscilloscopeCh1_.unit_ = MICRO;
					break;
				case '2':
					oscilloscopeCh1_.unit_ = MILLI;
					break;
				case '3':
					oscilloscopeCh1_.unit_ = SECOND;
					break;
				default:
					break;
				}
			} else if(command_[2] == STATE_LOW) {
				//Store state
				oscilloscopeCh1_.state_ = STATE_OFF;

				//Reset params
				oscilloscopeCh1_.period_ = 0;
				oscilloscopeCh1_.unit_ = MICRO;
			}

			//Reset vars
			iter++;
			decimals = 0;
			decimalFlag = false;

		} else if(command_[1] == '2') {
			if(command_[2] == STATE_HIGH) {
				//Store state
				oscilloscopeCh2_.state_ = STATE_ON;

				//Store period as integer
				for(int iter = 3; command_[iter] != 'U'; iter++) {
					if(command_[iter] != '.') {
						if(decimalFlag) decimals++;
						oscilloscopeCh2_.period_ = (oscilloscopeCh2_.period_ * 10) + parseFloat(command_[iter]);
					} else {
						decimalFlag = true;
					}
				}

				//Convert to float
				while(decimals > 0) {
					oscilloscopeCh2_.period_ = oscilloscopeCh2_.period_ / 10;
					decimals--;
				}

				//Store period unit
				switch(command_[iter]) {
				case '1':
					oscilloscopeCh2_.unit_ = MICRO;
					break;
				case '2':
					oscilloscopeCh2_.unit_ = MILLI;
					break;
				case '3':
					oscilloscopeCh2_.unit_ = SECOND;
					break;
				default:
					break;
				}
			} else if(command_[2] == STATE_LOW) {
				//Store state
				oscilloscopeCh2_.state_ = STATE_OFF;

				//Reset params
				oscilloscopeCh2_.period_ = 0;
				oscilloscopeCh2_.unit_ = MICRO;
			}

			//Reset vars
			iter++;
			decimals = 0;
			decimalFlag = false;
		}

		break;

	//Bad command received
	default:
		break;
	}
}


void runDevice(MultimeterTypedef mul_, WaveGeneratorTypedef wg_, PowerSourceTypedef ps_,
		OscilloscopeTypedef osc1_, OscilloscopeTypedef osc2_) {
	//Multimeter turned on
	if(mul_.state_ == STATE_ON) {
		//Stop any running service
		killOscilloscope();

		//Start multimeter
		if(mul_.source_ == 1) {
			//Get ADC value
			multimeterVoltVal_ = getADCvalue();
		} else {

		}

		//Send value at approximately 5Hz
		sendFormat("%d!", multimeterVoltVal_);
		delayMS(150);

	} else if(osc1_.state_ == STATE_ON) {
		//Stop any running services
		killMultimeter();
	} else if(osc2_.state_ == STATE_ON) {
		//Stop any running services
		killMultimeter();
	} else if(waveGenerator_.isWaiting_) {
		//TODO: Turn on WG

		//Free device
		waveGenerator_.isWaiting_ = false;
	} else if(powerSource_.isWaiting_) {
		//TODO: Turn on PS

		//Free device
		powerSource_.isWaiting_ = false;
	} else {

	}
}

void delayMS(uint32_t time) {
	HAL_Delay(time);
}

uint16_t getADCvalue(void) {
	//ADC value
	uint16_t value_ = 0;

	//Start conversion
	HAL_ADC_Start(&hadc1);

	//Wait for conversion
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

	//Get value and return
	value_ = HAL_ADC_GetValue(&hadc1);
	return value_;
}

float parseFloat(char c) {
	return c - '0';
}

int parseInt(char c) {
	return c - '0';
}

void resetParams(char device) {
	//Set all params to default
	switch(device) {
	case OSCILLOSCOPE:
		oscilloscopeCh1_.period_ = 0;
		oscilloscopeCh1_.unit_ = MICRO;
		oscilloscopeCh2_.period_ = 0;
		oscilloscopeCh2_.unit_ = MICRO;
		break;
	case MULTIMETER:
		multimeter_.source_ = 1;
		multimeter_.state_ = STATE_OFF;
		break;
	case WAVE_GENERATOR:
		waveGenerator_.amplitude_ = 0;
		waveGenerator_.period_ = 0;
		break;
	case POWER_SOURCE:
		powerSource_.value_ = 0;
		break;
	default :
		break;
	}
}

void killOscilloscope(void) {
	oscilloscopeCh1_.state_ = STATE_OFF;
	oscilloscopeCh2_.state_ = STATE_OFF;
}

void killMultimeter(void) {
	multimeter_.state_ = STATE_OFF;
}


