/*
 * com.c
 *
 *  Created on: May 25, 2021
 *      Author: elvez
 */

#include "com.h"
#include <stdbool.h>

extern DeviceState state_;
extern uint8_t commandBuffer[];

uint8_t multimeterCommand = 'm';
uint8_t wavegeneratorCommand = 'w';
uint8_t powersourceCommand = 'p';
uint8_t oscilloscopeCommand = 'o';

void sendPacket(uint8_t* packet, uint16_t len) {
	HAL_UART_Transmit(&huart1, packet, len, HAL_MAX_DELAY);
}

void receivePacket(uint8_t* packet, uint16_t len) {
	HAL_UART_Receive(&huart1, packet, len, HAL_MAX_DELAY);
}

void receiveCommand(uint8_t* packet, uint16_t len) {
	HAL_UART_Receive_IT(&huart1, packet, len);
}

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
	//uint16_t recieveLen = 0;
	//memset(commandBuffer, 0, sizeof(commandBuffer));

	//receivePacket(commandBuffer, 1);
	//recieveLen = commandBuffer[0];
	//receivePacket(&commandBuffer[1], recieveLen);
}

void cmdMultimeter(uint8_t* buffer) {
	while(state_ == MULTIMETER) {
		blink(2, 50);
	}
}

void cmdWave(uint8_t* buffer) {
	while(state_ == WAVEGENERATOR) {
		blink(2, 50);
	}
}

void cmdSource(uint8_t* buffer) {
	while(state_ == POWERSOURCE) {
		blink(2, 50);
	}
}

void cmdOsc(uint8_t* buffer) {
	while(state_ == MULTIMETER) {
		blink(2, 50);
	}
}

void freeCommand(void) {
	//commandState = '0';
}

bool isCommandWaiting(void) {
//	if(commandState == '1') {
//		return true;
//	} else {
//		return false;
//	}
	return true;
}

