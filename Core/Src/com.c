/*
 * com.c
 *
 *  Created on: May 25, 2021
 *      Author: elvez
 */

#include "com.h"

uint8_t commandBuffer[200];

void sendACK(uint8_t ltf) {
	uint8_t ackBuffer[2];

	ackBuffer[0] = ACK;
	ackBuffer[1] = ltf;
	sendPacket(ackBuffer, 2);
}

void sendNACK(void) {
	uint8_t nack = NACK;

	sendPacket(&nack, 1);
}

void getCommand(void) {
	uint8_t recieveLen = 0;

	receivePacket(commandBuffer, 1);
	recieveLen = commandBuffer[0];
	receivePacket(&commandBuffer[1], recieveLen);
}

uint8_t verifyCRC(uint8_t* commandData, uint32_t len, uint32_t crcHost) {
	uint32_t CRCvalue = 0xff;

		for(uint32_t iter = 0; iter < len; iter++) {
			uint32_t iterData = commandData[iter];
			CRCvalue = HAL_CRC_Accumulate(&hcrc, &iterData, 1);
		}

	if(CRCvalue == crcHost) {
		return CRC_SUCCESS;
	}

	else {
		return CRC_FAIL;
	}
}

