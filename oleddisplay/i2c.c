/*
 * i2c.c
 *
 *  Created on: 24.07.2014
 *      Author: Felix
 */

#include "global.h"

void i2c_start(void) {
	SDA_PORT &= ~(1 << SDA);
	SCL_PORT &= ~(1 << SCL);

	I2C_DATA_HIGH;
	I2C_CLOCK_HIGH;
	I2C_DATA_LOW;
	I2C_CLOCK_LOW;
}

void i2c_stop(void) {
	I2C_CLOCK_LOW;
	I2C_DATA_LOW;
	I2C_CLOCK_HIGH;
	I2C_DATA_HIGH;
}

uint8_t i2c_transmit(uint8_t byte) {
	uint8_t ack;

	for (uint8_t i = 8; i; i--) {
		I2C_CLOCK_LOW;

		if (byte & 0x80) {
			I2C_DATA_HIGH;
		}

		else {
			I2C_DATA_LOW;
		}

		I2C_CLOCK_HIGH;
		byte <<= 1;
	}
	I2C_CLOCK_LOW;
	I2C_DATA_RELEASE;

	I2C_CLOCK_HIGH;
	ack = !((SDA_PIN & (1 << SDA)));
	I2C_CLOCK_LOW;

	return ack; // 1 if ACK received, 0 if not
}

uint8_t i2c_receive(uint8_t ack) {
	uint8_t byte = 0;

	I2C_DATA_RELEASE;

	for (uint8_t i = 8; i; i--) {
		I2C_CLOCK_LOW;
		I2C_CLOCK_HIGH;
		byte <<= 1;
		if (SDA_PIN & (1 << SDA)) byte |= 1;
	}
	I2C_CLOCK_LOW;

	if (ack) I2C_DATA_LOW;


	I2C_CLOCK_HIGH;
	I2C_CLOCK_LOW;

	I2C_DATA_RELEASE;

	return byte;
}
