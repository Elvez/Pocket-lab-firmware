/*
 * device.c
 *
 *  Created on: 13-Jun-2021
 *      Author: elvez
 */
#include "device.h"

//Device typedefs
extern MultimeterTypedef multimeter_;
extern WaveGeneratorTypedef waveGenerator_;
extern OscilloscopeTypedef oscilloscopeCh1_;
extern OscilloscopeTypedef oscilloscopeCh2_;
extern PWMTypedef pwmGenerator_[];

//Multimeter voltmeter value
uint16_t adcRaw_ = 0;

//PWM command status
bool isWaitingPWM = false;


void processCMD(char* command_) {
	//Command buffer's first character.
	char header_ = command_[0];

	//Number of digits after decimal
	int decimals = 0;

	//Is there decimal in the command
	bool decimalFlag = false;

	//General use iterator
	int iter = 0;

	//PWM pointer
	int pwmSource = 0;

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

	//Oscilloscope command
	case OSCILLOSCOPE:
		//Store channel
		switch(command_[1]) {
		case '1':
			if(command_[2] == STATE_HIGH) {
				//Store state
				oscilloscopeCh1_.state_ = STATE_ON;
			} else {
				//Store state
				oscilloscopeCh1_.state_ = STATE_OFF;
			}

			break;
		case '2':
			if(command_[2] == STATE_HIGH) {
				//Store state
				oscilloscopeCh2_.state_ = STATE_ON;

			} else {
				//Store state
				oscilloscopeCh2_.state_ = STATE_OFF;
			}

			break;
		default:
			break;
		}

		break;

	//PWM generator command
	case PWM_GENERATOR:
		//Set source
		pwmSource = parseInt(command_[1]) - 1;

		//Set state
		if(command_[2] == STATE_HIGH) {
			pwmGenerator_[pwmSource].state_ = STATE_ON;

			//Reset duty cycle
			pwmGenerator_[pwmSource].dutyCycle_ = 0;

			//Parse duty cycle
			for(int iter = 3; command_[iter] != '-'; iter++) {
				pwmGenerator_[pwmSource].dutyCycle_ = (pwmGenerator_[pwmSource].dutyCycle_ * 10)
														+ parseInt(command_[iter]);
			}

			//Set pwm state
			isWaitingPWM = true;
		} else if(command_[2] == STATE_LOW) {
			pwmGenerator_[pwmSource].state_ = STATE_OFF;

			pwmGenerator_[pwmSource].dutyCycle_ = 0;

			//Set pwm state
			isWaitingPWM = true;
		} else {
			debug("Bad command\n\r");
		}

		break;

	//Bad command received
	default:
		break;
	}
}

void runDevice(MultimeterTypedef mul_, WaveGeneratorTypedef wg_, OscilloscopeTypedef osc1_,
				OscilloscopeTypedef osc2_, PWMTypedef* pwm_) {
	//Multimeter turned on
	if(mul_.state_ == STATE_ON) {
		//Stop any running service
		killOscilloscope();

		//Start multimeter
		if(mul_.source_ == 1) {
			//Set channel
			selectChannel(MUL_CH1);

			//Sample a value and send
			sampleAndSend(MUL_CH1);

			//Delay in milliseconds
			delayMS(150);
		} else if(mul_.source_ == 2){
			//Set channel
			selectChannel(MUL_CH2);

			//Sample a value and send
			sampleAndSend(MUL_CH2);

			//Delay in milliseconds
			delayMS(150);
		}

	} else if(osc1_.state_ == STATE_ON || osc2_.state_ == STATE_ON) {
		//Stop any running services
		killMultimeter();

		//Send OSC1 values
		if(osc1_.state_ == STATE_ON) {
			//Set channel
			selectChannel(OSC_CH1);

			//Sample and send
			sampleAndSend(OSC_CH1);

			//Sampling delay
			delayMS(1);
		}

		//Send OSC2 values
		if(osc2_.state_ == STATE_ON) {
			//Set channel
			selectChannel(OSC_CH2);

			//Sample and send
			sampleAndSend(OSC_CH2);

			//Sampling delay
			delayMS(1);
		}


	} else if(waveGenerator_.isWaiting_) {
		//TODO: Turn on WG

		//Free device
		waveGenerator_.isWaiting_ = false;
	} else if(isWaitingPWM){
		//Turn on PWM
		for(int iter = 0; iter < 5; iter ++) {
			if(pwm_[iter].state_ == STATE_ON) {
				startPWM(iter, pwm_[iter].dutyCycle_);
			} else {
				stopPWM(iter);
			}
		}
		//Free device
		isWaitingPWM = false;
	}
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

	//Stop ADC
	HAL_ADC_Stop(&hadc1);

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
		oscilloscopeCh1_.state_ = STATE_OFF;
		oscilloscopeCh2_.state_ = STATE_OFF;
		break;
	case MULTIMETER:
		multimeter_.source_ = 1;
		multimeter_.state_ = STATE_OFF;
		break;
	case WAVE_GENERATOR:
		waveGenerator_.amplitude_ = 0;
		waveGenerator_.period_ = 0;
		break;
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

void sampleAndSend(ChannelTypedef channel) {
	//Sample one value
	adcRaw_ = getADCvalue();

	//Send formatted packet
	switch(channel) {
	case MUL_CH1:
		//Send value
		sendFormat("%dM", adcRaw_);

		break;
	case MUL_CH2:
		//Send value
		sendFormat("%dM", adcRaw_);

		break;
	case OSC_CH1:
		//Send value, 'A' for oscilloscope channel 1
		sendFormat("%dA", adcRaw_);

		break;
	case OSC_CH2:
		//Send value, 'B' for oscilloscope channel 2
		sendFormat("%dB", adcRaw_);

		break;
	default:
		break;
	}
}

void selectChannel(ChannelTypedef channel) {
	//ADC config
	ADC_ChannelConfTypeDef sConfig = {0};

	//Set chanel
	switch(channel) {
	case MUL_CH1:
		//Set ADC channel to multimeter channel 1
		sConfig.Channel = ADC_CHANNEL_0;
		sConfig.Rank = 1;
		sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

		if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
		{
			Error_Handler();
		}

		break;
	case MUL_CH2:
		//Set ADC channel to multimeter channel 2
		sConfig.Channel = ADC_CHANNEL_1;
		sConfig.Rank = 1;
		sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

		if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
		{
			Error_Handler();
		}

		break;
	case OSC_CH1:
		//Set ADC channel to oscilloscope channel 1
		sConfig.Channel = ADC_CHANNEL_5;
		sConfig.Rank = 1;
		sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

		if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
		{
			Error_Handler();
		}

		break;
	case OSC_CH2:
		//Set ADC channel to oscilloscope channel 2
		sConfig.Channel = ADC_CHANNEL_7;
		sConfig.Rank = 1;
		sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

		if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
		{
			Error_Handler();
		}

		break;
	default:
		break;
	}
}

void startPWM(PWMChannelTypedef channel, int dutyCycle) {
	//Duty cycle is in range 0-100
	if(dutyCycle < 0) dutyCycle = 0;
	if(dutyCycle > 100) dutyCycle = 100;

	switch(channel) {
	case PWM1:
		//Set duty cycle
		htim1.Instance->CCR1 = dutyCycle;

		//Start PWM
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		break;
	case PWM2:
		//Set duty cycle
		htim2.Instance->CCR1 = dutyCycle;

		//Start PWM
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		break;
	case PWM3:
		//Set duty cycle
		htim3.Instance->CCR1 = dutyCycle;

		//Start PWM
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
		break;
	case PWM4:
		//Set duty cycle
		htim4.Instance->CCR1 = dutyCycle;

		//Start PWM
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
		break;
	case PWM5:
		//Set duty cycle
		htim10.Instance->CCR1 = dutyCycle;

		//Start PWM
		HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
		break;
	case PWM6:
		//Set duty cycle
		htim11.Instance->CCR1 = dutyCycle;

		//Start PWM
		HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1);
		break;
	default:
		break;
	}
}

void stopPWM(PWMChannelTypedef channel) {
	switch(channel) {
	case PWM1:
		//Stop PWM
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);

		//Set PWM value 0
		htim1.Instance->CCR1 = 0;
		break;
	case PWM2:
		//Stop PWM
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);

		//Set PWM value 0
		htim2.Instance->CCR1 = 0;
		break;
	case PWM3:
		//Stop PWM
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);

		//Set PWM value 0
		htim3.Instance->CCR1 = 0;
		break;
	case PWM4:
		//Stop PWM
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);

		//Set PWM value 0
		htim4.Instance->CCR1 = 0;
		break;
	case PWM5:
		//Stop PWM
		HAL_TIM_PWM_Stop(&htim10, TIM_CHANNEL_1);

		//Set PWM value 0
		htim10.Instance->CCR1 = 0;
		break;
	case PWM6:
		//Stop PWM
		HAL_TIM_PWM_Stop(&htim11, TIM_CHANNEL_1);

		//Set PWM value 0
		htim11.Instance->CCR1 = 0;
		break;
	default:
		break;
	}
}

void delayMS(uint32_t delay) {
	//Give delay
	HAL_Delay(delay);
}

