/*
 * ad9833.c
 *
 *  Created on: 22-Jul-2021
 *      Author: elvez
 */
#include "ad9833.h"

//MSB of Frequency tuning word
uint16_t frequencyMSB = 0;

//LSB of Frequency tuning word
uint16_t frequencyLSB = 0;

//Phase tuning value
uint32_t  phaseVal = 0;

//Flag variable
WaveTypedef currentWave = SINE;

void setWave(WaveTypedef wave, int source) {
  switch(wave){
  case SINE:
	//0x2000 is value for sinusoidal wave
    if(source == 1) writeSPI1(0x2000);
    else if(source == 2) writeSPI2(0x2000);

    //Save wave
    currentWave = SINE;

    break;
  case SQUARE:
    //0x2028 is value for square wave
	if(source == 1) writeSPI1(0x2028);
	else if(source == 2) writeSPI2(0x2028);

    //Save wave
    currentWave = SQUARE;

    break;
  case TRIANG:
    //0x2002 is the value for triangle wave
	if(source == 1) writeSPI1(0x2002);
	else if(source == 2) writeSPI2(0x2002);

    //Save wave
    currentWave = TRIANG;

    break;
  default:
    break;
  }
}

void setWaveData(float frequency, float phase, int source) {
	//Little delay
	ASM_NOP();

	//Phase must be a value between 0 - 360 degrees.
	if(phase < 0) phase = 0;
	if(phase > 360) phase = 360;

	//4096/360 = 11.37 change per degree for register and using 0xC000 which is phase 0 register address
	phaseVal  = ((int)(phase * (4096 / 360))) | 0xC000;

	//Wave-frequency
	long freq=0;

	//Tuning word
	freq = (int)(((frequency * pow(2,28)) / FMCLK) + 1);

	//Frequency MSB and LSB
	frequencyLSB = (int)((freq & 0xFFFC000) >> 14);
	frequencyMSB = (int)(freq & 0x3FFF);
	frequencyMSB |= 0x4000;
	frequencyLSB |= 0x4000;

	//Little delay
	ASM_NOP();

	//----Write data----

	//Enable 16-bit word and set reset bit
	if(source == 1) writeSPI1(0x2100);
	else if(source == 2) writeSPI2(0x2100);

	//Write frequency MSB and LSB
	if(source == 1) {
		writeSPI1(frequencyMSB);
		writeSPI1(frequencyLSB);
	}
	else if(source == 2) {
		writeSPI2(frequencyMSB);
		writeSPI2(frequencyLSB);
	}

	//Write phase
    if(source == 1) writeSPI1(phaseVal);
    else if(source == 2) writeSPI2(phaseVal);

    //Clear reset bit
    if(source == 1) writeSPI1(0x2000);
    else if(source == 2) writeSPI2(0x2000);

	//-------------------

	//Little delay
	ASM_NOP();

	//Set current wave again.
	setWave(currentWave, source);

	//Little delay
	ASM_NOP();
}

void initWG(WaveTypedef wave, float frequency, float phase, int source) {
	setWave(wave, source);
	setWaveData(frequency, phase, source);
}

void resetWG(int source) {
	//Write reset command : 0x0100
	if(source == 1) writeSPI1(0x0100);
	else if(source == 2) writeSPI2(0x0100);
}








