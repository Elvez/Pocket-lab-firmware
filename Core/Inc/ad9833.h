/*
 * ad9833.h
 *
 *  Created on: 22-Jul-2021
 *      Author: elvez
 */

#ifndef INC_AD9833_H_
#define INC_AD9833_H_
#include <math.h>
#include "stm32f4xx_hal.h"
#include "com.h"

//Master clock on AD9833
#define FMCLK 25000000

//No-operation instruction from assembly
#define ASM_NOP() asm("NOP")

void setWave(WaveTypedef wave, int source);

void setWaveData(float frequency, float phase, int source);

void initWG(WaveTypedef wave, float frequency, float phase, int source);

void resetWG(int source);

#endif /* INC_AD9833_H_ */
