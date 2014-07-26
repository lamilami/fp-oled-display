/*
 * oled.c
 *
 *  Created on: 17.06.2014
 *      Author: Felix
 */

#include "global.h"

#ifdef OLEDBUFFERED_H_

static uint8_t buffer[1025] = { 0 };

const unsigned char oledchars[] PROGMEM = { 0x00, 0x00, 0x00, 0x00, 0x00, // ''
		0x3E, 0x5B, 0x4F, 0x5B, 0x3E, // ''
		0x3E, 0x6B, 0x4F, 0x6B, 0x3E, // ''
		0x1C, 0x3E, 0x7C, 0x3E, 0x1C, // ''
		0x18, 0x3C, 0x7E, 0x3C, 0x18, // ''
		0x1C, 0x57, 0x7D, 0x57, 0x1C, // ''
		0x1C, 0x5E, 0x7F, 0x5E, 0x1C, // ''
		0x00, 0x18, 0x3C, 0x18, 0x00, // ''
		0xFF, 0xE7, 0xC3, 0xE7, 0xFF, // ''
		0x00, 0x18, 0x24, 0x18, 0x00, // ''
		0xFF, 0xE7, 0xDB, 0xE7, 0xFF, // ''
		0x30, 0x48, 0x3A, 0x06, 0x0E, // ''
		0x26, 0x29, 0x79, 0x29, 0x26, // ''
		0x40, 0x7F, 0x05, 0x05, 0x07, // ''
		0x40, 0x7F, 0x05, 0x25, 0x3F, // ''
		0x5A, 0x3C, 0xE7, 0x3C, 0x5A, // ''
		0x7F, 0x3E, 0x1C, 0x1C, 0x08, // ''
		0x08, 0x1C, 0x1C, 0x3E, 0x7F, // ''
		0x14, 0x22, 0x7F, 0x22, 0x14, // ''
		0x5F, 0x5F, 0x00, 0x5F, 0x5F, // ''
		0x06, 0x09, 0x7F, 0x01, 0x7F, // ''
		0x00, 0x66, 0x89, 0x95, 0x6A, // ''
		0x60, 0x60, 0x60, 0x60, 0x60, // ''
		0x94, 0xA2, 0xFF, 0xA2, 0x94, // ''
		0x08, 0x04, 0x7E, 0x04, 0x08, // ''
		0x10, 0x20, 0x7E, 0x20, 0x10, // ''
		0x08, 0x08, 0x2A, 0x1C, 0x08, // ''
		0x08, 0x1C, 0x2A, 0x08, 0x08, // ''
		0x1E, 0x10, 0x10, 0x10, 0x10, // ''
		0x0C, 0x1E, 0x0C, 0x1E, 0x0C, // ''
		0x30, 0x38, 0x3E, 0x38, 0x30, // ''
		0x06, 0x0E, 0x3E, 0x0E, 0x06, // ''
		0x00, 0x00, 0x00, 0x00, 0x00, // ''
		0x00, 0x00, 0x5F, 0x00, 0x00, // ''
		0x00, 0x07, 0x00, 0x07, 0x00, // ''
		0x14, 0x7F, 0x14, 0x7F, 0x14, // ''
		0x24, 0x2A, 0x7F, 0x2A, 0x12, // ''
		0x23, 0x13, 0x08, 0x64, 0x62, // ''
		0x36, 0x49, 0x56, 0x20, 0x50, // ''
		0x00, 0x08, 0x07, 0x03, 0x00, // ''
		0x00, 0x1C, 0x22, 0x41, 0x00, // ''
		0x00, 0x41, 0x22, 0x1C, 0x00, // ''
		0x2A, 0x1C, 0x7F, 0x1C, 0x2A, // ''
		0x08, 0x08, 0x3E, 0x08, 0x08, // ''
		0x00, 0x80, 0x70, 0x30, 0x00, // ''
		0x08, 0x08, 0x08, 0x08, 0x08, // ''
		0x00, 0x00, 0x60, 0x60, 0x00, // '.'
		0x20, 0x10, 0x08, 0x04, 0x02, // '/'
		0x3E, 0x51, 0x49, 0x45, 0x3E, // '0' = 48 = 0x30
		0x00, 0x42, 0x7F, 0x40, 0x00, // '1' = 49 = 0x31
		0x72, 0x49, 0x49, 0x49, 0x46, // '2' = 50 = 0x32
		0x21, 0x41, 0x49, 0x4D, 0x33, // '3'
		0x18, 0x14, 0x12, 0x7F, 0x10, // '4'
		0x27, 0x45, 0x45, 0x45, 0x39, // '5'
		0x3C, 0x4A, 0x49, 0x49, 0x31, // '6'
		0x41, 0x21, 0x11, 0x09, 0x07, // '7'
		0x36, 0x49, 0x49, 0x49, 0x36, // '8'
		0x46, 0x49, 0x49, 0x29, 0x1E, // '9'
		0x00, 0x00, 0x14, 0x00, 0x00, // ':'
		0x00, 0x40, 0x34, 0x00, 0x00, // ';'
		0x00, 0x08, 0x14, 0x22, 0x41, // '<'
		0x14, 0x14, 0x14, 0x14, 0x14, // '='
		0x00, 0x41, 0x22, 0x14, 0x08, // '>'
		0x02, 0x01, 0x59, 0x09, 0x06, // '?'
		0x3E, 0x41, 0x5D, 0x59, 0x4E, // '@'
		0x7C, 0x12, 0x11, 0x12, 0x7C, // 'A'
		0x7F, 0x49, 0x49, 0x49, 0x36, // 'B'
		0x3E, 0x41, 0x41, 0x41, 0x22, // 'C'
		0x7F, 0x41, 0x41, 0x41, 0x3E, // 'D'
		0x7F, 0x49, 0x49, 0x49, 0x41, // 'E'
		0x7F, 0x09, 0x09, 0x09, 0x01, // 'F'
		0x3E, 0x41, 0x41, 0x51, 0x73, // 'G'
		0x7F, 0x08, 0x08, 0x08, 0x7F, // 'H'
		0x00, 0x41, 0x7F, 0x41, 0x00, // 'I'
		0x20, 0x40, 0x41, 0x3F, 0x01, // 'J'
		0x7F, 0x08, 0x14, 0x22, 0x41, // 'K'
		0x7F, 0x40, 0x40, 0x40, 0x40, // 'L'
		0x7F, 0x02, 0x1C, 0x02, 0x7F, // 'M'
		0x7F, 0x04, 0x08, 0x10, 0x7F, // 'N'
		0x3E, 0x41, 0x41, 0x41, 0x3E, // 'O'
		0x7F, 0x09, 0x09, 0x09, 0x06, // 'P'
		0x3E, 0x41, 0x51, 0x21, 0x5E, // 'Q'
		0x7F, 0x09, 0x19, 0x29, 0x46, // 'R'
		0x26, 0x49, 0x49, 0x49, 0x32, // 'S'
		0x03, 0x01, 0x7F, 0x01, 0x03, // 'T'
		0x3F, 0x40, 0x40, 0x40, 0x3F, // 'U'
		0x1F, 0x20, 0x40, 0x20, 0x1F, // 'V'
		0x3F, 0x40, 0x38, 0x40, 0x3F, // 'W'
		0x63, 0x14, 0x08, 0x14, 0x63, // 'X'
		0x03, 0x04, 0x78, 0x04, 0x03, // 'Y'
		0x61, 0x59, 0x49, 0x4D, 0x43, // 'Z'
		0x00, 0x7F, 0x41, 0x41, 0x41, // '['
		0x02, 0x04, 0x08, 0x10, 0x20, // '\'
		0x00, 0x41, 0x41, 0x41, 0x7F, // ']'
		0x04, 0x02, 0x01, 0x02, 0x04, // '^'
		0x40, 0x40, 0x40, 0x40, 0x40, // '_'
		0x00, 0x03, 0x07, 0x08, 0x00, // '`'
		0x20, 0x54, 0x54, 0x78, 0x40, // 'a'
		0x7F, 0x28, 0x44, 0x44, 0x38, // 'b'
		0x38, 0x44, 0x44, 0x44, 0x28, // 'c'
		0x38, 0x44, 0x44, 0x28, 0x7F, // 'd'
		0x38, 0x54, 0x54, 0x54, 0x18, // 'e'
		0x00, 0x08, 0x7E, 0x09, 0x02, // 'f'
		0x18, 0xA4, 0xA4, 0x9C, 0x78, // 'g'
		0x7F, 0x08, 0x04, 0x04, 0x78, // 'h'
		0x00, 0x44, 0x7D, 0x40, 0x00, // 'i'
		0x20, 0x40, 0x40, 0x3D, 0x00, // 'j'
		0x7F, 0x10, 0x28, 0x44, 0x00, // 'k'
		0x00, 0x41, 0x7F, 0x40, 0x00, // 'l'
		0x7C, 0x04, 0x78, 0x04, 0x78, // 'm'
		0x7C, 0x08, 0x04, 0x04, 0x78, // 'n'
		0x38, 0x44, 0x44, 0x44, 0x38, // 'o'
		0xFC, 0x18, 0x24, 0x24, 0x18, // 'p'
		0x18, 0x24, 0x24, 0x18, 0xFC, // 'q'
		0x7C, 0x08, 0x04, 0x04, 0x08, // 'r'
		0x48, 0x54, 0x54, 0x54, 0x24, // 's'
		0x04, 0x04, 0x3F, 0x44, 0x24, // 't'
		0x3C, 0x40, 0x40, 0x20, 0x7C, // 'u'
		0x1C, 0x20, 0x40, 0x20, 0x1C, // 'v'
		0x3C, 0x40, 0x30, 0x40, 0x3C, // 'w'
		0x44, 0x28, 0x10, 0x28, 0x44, // 'x'
		0x4C, 0x90, 0x90, 0x90, 0x7C, // 'y'
		0x44, 0x64, 0x54, 0x4C, 0x44, // 'z' = 122
		0x00, 0x08, 0x36, 0x41, 0x00, // '{'
		0x00, 0x00, 0x77, 0x00, 0x00, // '|'
		0x00, 0x41, 0x36, 0x08, 0x00, // '}'
		0x02, 0x01, 0x02, 0x04, 0x02, // ''
		0x3C, 0x26, 0x23, 0x26, 0x3C, // ''
		0x1E, 0xA1, 0xA1, 0x61, 0x12, // ''
		0x3A, 0x40, 0x40, 0x20, 0x7A, // ''
		0x38, 0x54, 0x54, 0x55, 0x59, // ''
		0x21, 0x55, 0x55, 0x79, 0x41, // ''
		0x21, 0x54, 0x54, 0x78, 0x41, // ''
		0x21, 0x55, 0x54, 0x78, 0x40, // ''
		0x20, 0x54, 0x55, 0x79, 0x40, // ''
		0x0C, 0x1E, 0x52, 0x72, 0x12, // ''
		0x39, 0x55, 0x55, 0x55, 0x59, // ''
		0x39, 0x54, 0x54, 0x54, 0x59, // ''
		0x39, 0x55, 0x54, 0x54, 0x58, // ''
		0x00, 0x00, 0x45, 0x7C, 0x41, // ''
		0x00, 0x02, 0x45, 0x7D, 0x42, // ''
		0x00, 0x01, 0x45, 0x7C, 0x40, // ''
		0xF0, 0x29, 0x24, 0x29, 0xF0, // ''
		0xF0, 0x28, 0x25, 0x28, 0xF0, // ''
		0x7C, 0x54, 0x55, 0x45, 0x00, // ''
		0x20, 0x54, 0x54, 0x7C, 0x54, // ''
		0x7C, 0x0A, 0x09, 0x7F, 0x49, // ''
		0x32, 0x49, 0x49, 0x49, 0x32, // ''
		0x32, 0x48, 0x48, 0x48, 0x32, // ''
		0x32, 0x4A, 0x48, 0x48, 0x30, // ''
		0x3A, 0x41, 0x41, 0x21, 0x7A, // ''
		0x3A, 0x42, 0x40, 0x20, 0x78, // ''
		0x00, 0x9D, 0xA0, 0xA0, 0x7D, // ''
		0x39, 0x44, 0x44, 0x44, 0x39, // ''
		0x3D, 0x40, 0x40, 0x40, 0x3D, // ''
		0x3C, 0x24, 0xFF, 0x24, 0x24, // ''
		0x48, 0x7E, 0x49, 0x43, 0x66, // ''
		0x2B, 0x2F, 0xFC, 0x2F, 0x2B, // ''
		0xFF, 0x09, 0x29, 0xF6, 0x20, // ''
		0xC0, 0x88, 0x7E, 0x09, 0x03, // ''
		0x20, 0x54, 0x54, 0x79, 0x41, // ''
		0x00, 0x00, 0x44, 0x7D, 0x41, // ''
		0x30, 0x48, 0x48, 0x4A, 0x32, // ''
		0x38, 0x40, 0x40, 0x22, 0x7A, // ''
		0x00, 0x7A, 0x0A, 0x0A, 0x72, // ''
		0x7D, 0x0D, 0x19, 0x31, 0x7D, // ''
		0x26, 0x29, 0x29, 0x2F, 0x28, // ''
		0x26, 0x29, 0x29, 0x29, 0x26, // ''
		0x30, 0x48, 0x4D, 0x40, 0x20, // ''
		0x38, 0x08, 0x08, 0x08, 0x08, // ''
		0x08, 0x08, 0x08, 0x08, 0x38, // ''
		0x2F, 0x10, 0xC8, 0xAC, 0xBA, // ''
		0x2F, 0x10, 0x28, 0x34, 0xFA, // ''
		0x00, 0x00, 0x7B, 0x00, 0x00, // ''
		0x08, 0x14, 0x2A, 0x14, 0x22, // ''
		0x22, 0x14, 0x2A, 0x14, 0x08, // ''
		0x06, 0x09, 0x09, 0x06, 0x00, // '�'
		0xAA, 0x55, 0xAA, 0x55, 0xAA, // ''
		0x00, 0x00, 0x00, 0xFF, 0x00, // ''
		0x10, 0x10, 0x10, 0xFF, 0x00, // ''
		0x14, 0x14, 0x14, 0xFF, 0x00, // ''
		0x10, 0x10, 0xFF, 0x00, 0xFF, // ''
		0x10, 0x10, 0xF0, 0x10, 0xF0, // ''
		0x14, 0x14, 0x14, 0xFC, 0x00, // ''
		0x14, 0x14, 0xF7, 0x00, 0xFF, // ''
		0x00, 0x00, 0xFF, 0x00, 0xFF, // ''
		0x14, 0x14, 0xF4, 0x04, 0xFC, // ''
		0x14, 0x14, 0x17, 0x10, 0x1F, // ''
		0x10, 0x10, 0x1F, 0x10, 0x1F, // ''
		0x14, 0x14, 0x14, 0x1F, 0x00, // ''
		0x10, 0x10, 0x10, 0xF0, 0x00, // ''
		0x00, 0x00, 0x00, 0x1F, 0x10, // ''
		0x10, 0x10, 0x10, 0x1F, 0x10, // ''
		0x10, 0x10, 0x10, 0xF0, 0x10, // ''
		0x00, 0x00, 0x00, 0xFF, 0x10, // ''
		0x10, 0x10, 0x10, 0x10, 0x10, // ''
		0x79, 0x14, 0x12, 0x14, 0x79, // '�'
		0x00, 0x00, 0x00, 0xFF, 0x14, // ''
		0x00, 0x00, 0xFF, 0x00, 0xFF, // ''
		0x00, 0x00, 0x1F, 0x10, 0x17, // ''
		0x00, 0x00, 0xFC, 0x04, 0xF4, // ''
		0x14, 0x14, 0x17, 0x10, 0x17, // ''
		0x14, 0x14, 0xF4, 0x04, 0xF4, // ''
		0x00, 0x00, 0xFF, 0x00, 0xF7, // ''
		0x14, 0x14, 0x14, 0x14, 0x14, // ''
		0x14, 0x14, 0xF7, 0x00, 0xF7, // ''
		0x14, 0x14, 0x14, 0x17, 0x14, // ''
		0x10, 0x10, 0x1F, 0x10, 0x1F, // ''
		0x14, 0x14, 0x14, 0xF4, 0x14, // ''
		0x10, 0x10, 0xF0, 0x10, 0xF0, // ''
		0x00, 0x00, 0x1F, 0x10, 0x1F, // ''
		0x00, 0x00, 0x00, 0x1F, 0x14, // ''
		0x00, 0x00, 0x00, 0xFC, 0x14, // ''
		0x00, 0x00, 0xF0, 0x10, 0xF0, // ''
		0x38, 0x45, 0x44, 0x45, 0x38, // '�'
		0x14, 0x14, 0x14, 0xFF, 0x14, // ''
		0x10, 0x10, 0x10, 0x1F, 0x00, // ''
		0x00, 0x00, 0x00, 0xF0, 0x10, // ''
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ''
		0xF0, 0xF0, 0xF0, 0xF0, 0xF0, // ''
		0x3C, 0x41, 0x40, 0x41, 0x3C, // '�'
		0x00, 0x00, 0x00, 0xFF, 0xFF, // ''
		0x0F, 0x0F, 0x0F, 0x0F, 0x0F, // ''
		0xFE, 0x01, 0x49, 0x49, 0x36, // '�'
		0x7C, 0x2A, 0x2A, 0x3E, 0x14, // ''
		0x7E, 0x02, 0x02, 0x06, 0x06, // ''
		0x02, 0x7E, 0x02, 0x7E, 0x02, // ''
		0x63, 0x55, 0x49, 0x41, 0x63, // ''
		0x20, 0x55, 0x54, 0x79, 0x40, // ''
		0x40, 0x7E, 0x20, 0x1E, 0x20, // ''
		0x06, 0x02, 0x7E, 0x02, 0x02, // ''
		0x99, 0xA5, 0xE7, 0xA5, 0x99, // ''
		0x1C, 0x2A, 0x49, 0x2A, 0x1C, // ''
		0x4C, 0x72, 0x01, 0x72, 0x4C, // ''
		0x30, 0x4A, 0x4D, 0x4D, 0x30, // ''
		0x30, 0x48, 0x78, 0x48, 0x30, // ''
		0xBC, 0x62, 0x5A, 0x46, 0x3D, // ''
		0x3E, 0x49, 0x49, 0x49, 0x00, // ''
		0x7E, 0x01, 0x01, 0x01, 0x7E, // ''
		0x2A, 0x2A, 0x2A, 0x2A, 0x2A, // ''
		0x44, 0x44, 0x5F, 0x44, 0x44, // ''
		0x40, 0x51, 0x4A, 0x44, 0x40, // ''
		0x40, 0x44, 0x4A, 0x51, 0x40, // ''
		0x00, 0x00, 0xFF, 0x01, 0x03, // ''
		0xE0, 0x80, 0xFF, 0x00, 0x00, // ''
		0x08, 0x08, 0x6B, 0x6B, 0x08, // ''
		0x38, 0x45, 0x44, 0x45, 0x38, // '�' = 246
		0x06, 0x0F, 0x09, 0x0F, 0x06, // ''
		0x00, 0x00, 0x18, 0x18, 0x00, // ''
		0x00, 0x00, 0x10, 0x10, 0x00, // ''
		0x30, 0x40, 0xFF, 0x01, 0x01, // ''
		0x00, 0x1F, 0x01, 0x01, 0x1E, // ''
		0x3C, 0x41, 0x40, 0x21, 0x7C, // '�' = 252
		0x00, 0x3C, 0x3C, 0x3C, 0x3C, // ''
		0x00, 0x00, 0x00, 0x00, 0x00, 0x4C, 0x91, 0x90, 0x91, 0x7C };

void oled_display(void) {
	oled_send(0x00, 0); // low col = 0
	oled_send(0x10, 0); // hi col = 0
	oled_send(0xB0, 0);
	i2c_start(); // I2C-Start
	i2c_transmit(OLED_ADDRESS); // Slave address
	i2c_transmit(0x40); // Set OLED Data mode
	for (uint16_t j = 0; j < 1024; j++) {
		i2c_transmit(buffer[j]); // Transmit command
	}
	i2c_stop(); // End I2C communication
}

void oled_send(uint8_t command, uint8_t datamode) {
	i2c_start(); // I2C-Start
	i2c_transmit(OLED_ADDRESS); // Slave address
	if (datamode) {
		i2c_transmit(0x40); // Set OLED Data mode
	}
	else {
		i2c_transmit(0x80); // Set OLED Command mode
	}
	i2c_transmit(command); // Transmit command
	i2c_stop(); // End I2C communication
}

uint8_t oled_read(uint8_t datamode) {
	uint8_t data;

	i2c_start(); // I2C-Start
	i2c_transmit(OLED_ADDRESS); // Slave address
	if (datamode) {
		i2c_transmit(0x40); // Set OLED Data mode
	}
	else {
		i2c_transmit(0x80); // Set OLED Command mode
	}
	i2c_start();
	i2c_transmit(OLED_ADDRESS | 1); // Slave address + read
	data = i2c_receive(1); // Transmit command
	i2c_stop(); // End I2C communication
	return data;
}

void oled_init(void) {
	_delay_ms(100); //wait for OLED hardware init

	oled_send(0xAE, 0); /*display off*/

	oled_send(0xA8, 0); /*multiplex ratio*/
	oled_send(0x3F, 0); /*duty = 1/64*/

	oled_send(0x20, 0); /*set Page Addressing Mode*/
	oled_send(0x10, 0); /*to page mode */

	oled_send(0x21, 0); //set column address
	oled_send(0x00, 0); //set column start address 1
	oled_send(0x7F, 0); //set column end address 126

	oled_send(0x22, 0); //set page address
	oled_send(0x00, 0); //set start page 0
	oled_send(0x07, 0); //set last page 7

	oled_send(0x81, 0); /*contrast control*/
	oled_send(0xFF, 0); /*full*/

	oled_send(0xA1, 0); /*set segment remap*/

	oled_send(0xC8, 0); /*Com scan direction*/
	oled_send(0xA6, 0); /*normal / reverse*/

	oled_send(0xD5, 0); /*set osc division*/
	oled_send(0xF0, 0);

	oled_send(0xD9, 0); /*set pre-charge period*/
	oled_send(0xF1, 0);

	oled_send(0xDA, 0); /*set COM pins*/
	oled_send(0x12, 0);

	oled_send(0xDB, 0); /*set vcomh*/
	oled_send(0x00, 0);

	oled_send(0x2E, 0);
	oled_send(0x40, 0);

	oled_send(0x8D, 0); /*set charge pump enable*/
	oled_send(0x14, 0);

	oled_send(0xAF, 0); /*display ON*/
}

void oled_draw_pixel(uint8_t x, uint8_t y) {
	if (x > 127 || y > 63) return;

	uint8_t mask = 1, val = 0;
	for (uint8_t i = 0; i < 8; i++) {
		if (i == (y & 0x07)) val |= mask;
		mask <<= 1;
	}
	y >>= 3;
	buffer[(y << 7) + x] |= val;

	oled_send(0x00 | (x & 0x0F), 0); // low col
	oled_send(0x10 | (x >> 4), 0); // hi col
	oled_send(0xB0 | y, 0); // Page
	oled_send(buffer[(y << 7) + x], 1);
}

void oled_draw_pattern(char c, uint8_t x, uint8_t y) {
	if (x > 127 || y > 63) return;

	oled_send(0x00 | (x & 0x0F), 0); // low col
	oled_send(0x10 | (x >> 4), 0); // hi col
	oled_send(0xB0 | (y >> 3), 0); // Page

	oled_send(c, 1);
}

static void swapvals(uint8_t *x1, uint8_t *x2) {
	uint8_t temp = *x1;
	*x1 = *x2;
	*x2 = temp;
}

static void oled_draw_vertical_line(uint8_t x, uint8_t ystart, uint8_t ystop) {
	if (ystart > ystop) swapvals(&ystart, &ystop);
	uint8_t mask, ystarttemp = (ystart & 0x07), ystoptemp = (ystop & 0x07);
	ystart >>= 3;
	ystop >>= 3;

	// Restpixel obere Page
	oled_send(0x00 | (x & 0x0F), 0); // low col
	oled_send(0x10 | (x >> 4), 0); // hi col
	oled_send(0xB0 | ystart, 0); // Page

	mask = 0xFF;
	for (uint8_t i = 0; i < ystarttemp; i++) {
		mask <<= 1;
	}
	buffer[(ystart << 7) + x] |= mask;
	oled_send(buffer[(ystart << 7) + x], 1);

	// Mittlere Pages
	for (uint8_t p = ystart + 1; p < ystop; p++) {
		buffer[(p << 7) + x] |= 0xFF;
		oled_send(0x00 | (x & 0x0F), 0); // low col
		oled_send(0x10 | (x >> 4), 0); // hi col
		oled_send(0xB0 | p, 0); // Page
		oled_send(0xFF, 1);
	}

	// Restpixel untere Page
	oled_send(0x00 | (x & 0x0F), 0); // low col
	oled_send(0x10 | (x >> 4), 0); // hi col
	oled_send(0xB0 | ystop, 0); // Page
	mask = 0xFF;
	for (uint8_t i = 7; i > ystoptemp; i--) {
		mask >>= 1;
	}
	buffer[(ystop << 7) + x] |= mask;
	oled_send(buffer[(ystop << 7) + x], 1);
}

static void oled_draw_horizontal_line(uint8_t xstart, uint8_t xstop, uint8_t y) {
	if (xstart > 127 || xstop > 127 || y > 63) return;

	if (xstart > xstop) swapvals(&xstart, &xstop);

	uint8_t mask = 1, val = 0;
	for (uint8_t i = 0; i < 8; i++) {
		if (i == (y & 0x07)) val |= mask;
		mask <<= 1;
	}
	y >>= 3;

	oled_send(0x00 | (xstart & 0x0F), 0); // low col
	oled_send(0x10 | (xstart >> 4), 0); // hi col
	oled_send(0xB0 | y, 0); // Page

	for (uint8_t x = xstart; x <= xstop; x++) {
		buffer[(y << 7) + x] |= val;
		oled_send(buffer[(y << 7) + x], 1);
	}
}

void oled_draw_line(uint8_t xstart, uint8_t ystart, uint8_t xstop, uint8_t ystop) {
	if (xstart > 127 || xstop > 127 || ystart > 63 || ystop > 63) return;

	uint8_t deltax, deltay, yinv;
	int16_t m, t, xcalc, ycalc;

	if (xstart > xstop) {
		swapvals(&xstart, &xstop);
		swapvals(&ystart, &ystop);
	}

	oled_draw_pixel(xstart, ystart);
	oled_draw_pixel(xstop, ystop);

	// Spezialf�lle
	if (xstart == xstop) {
		oled_draw_vertical_line(xstart, ystart, ystop);
		return;
	}
	if (ystart == ystop) {
		oled_draw_horizontal_line(xstart, xstop, ystart);
		return;
	}

	// Allgemeiner Fall
	deltax = xstop - xstart;
	yinv = ystart > ystop;
	deltay = (yinv ? ystart - ystop : ystop - ystart);

	if (deltax > deltay) { // If there are more "x-pixels" than "y-pixels", y has to be calculated for every x
		m = (deltay * 100 + deltax / 2) / deltax;
		if(yinv) m = -m;
		t = (int16_t)(ystart * 100 - m * xstart);

		for (uint8_t x = xstart; x <= xstop; x++) {
			ycalc = m * x + t;
			ycalc = (ycalc + 50) / 100;
			oled_draw_pixel(x, ycalc);
		}
	}
	else { // Or the other way round if there are more "y-pixels" than "x-pixels"
		m = (deltax * 100 + deltay / 2) / deltay;
		if(yinv) m = -m;
		t = (int16_t)(xstart * 100 - m * ystart);

		if(yinv) swapvals(&ystart, &ystop);
		for (uint8_t y = ystart; y <= ystop; y++) {
			xcalc = m * y + t;
			xcalc = (xcalc + 50) / 100;
			oled_draw_pixel(xcalc, y);
		}
	}
}

void oled_draw_rectangle(uint8_t xstart, uint8_t ystart, uint8_t xstop, uint8_t ystop) {
	if (xstart > 127 || xstop > 127 || ystart > 63 || ystop > 63) return;
	if (xstart > xstop) swapvals(&xstart, &xstop);
	if (ystart > ystop) swapvals(&ystart, &ystop);

	// Linke Linie
	oled_draw_vertical_line(xstart, ystart, ystop);

	// Rechte Linie
	oled_draw_vertical_line(xstop, ystart, ystop);

	// Obere Linie
	oled_draw_horizontal_line(xstart, xstop, ystart);

	// Untere Linie
	oled_draw_horizontal_line(xstart, xstop, ystop);
}

void oled_draw_circle(uint8_t xcenter, uint8_t ycenter, uint8_t radius) {
	if (xcenter > 127 || ycenter > 63 || xcenter + radius > 127 || ycenter + radius > 63 || xcenter < radius
			|| ycenter < radius) return;

	uint16_t xl, y, r = radius * radius, erg, delta, deltamin;
	uint8_t marker = 0;

	oled_draw_pixel(xcenter - radius, ycenter);
	oled_draw_pixel(xcenter + radius, ycenter);
	oled_draw_pixel(xcenter, ycenter - radius);
	oled_draw_pixel(xcenter, ycenter + radius);

	y = radius;
	for (xl = 0; xl <= radius; xl++) {
		deltamin = 65000;
		for (uint8_t run = 0; run <= radius; run++) {
			erg = xl * xl + (y - run) * (y - run);
			delta = (erg > r) ? erg - r : r - erg;
			if (delta < deltamin) {
				deltamin = delta;
				marker = run;
			}
		}
		y -= marker;

		for (uint8_t j = 0; j <= marker; j++) {
			oled_draw_pixel(xcenter + xl, ycenter + y + j);
			oled_draw_pixel(xcenter - xl, ycenter + y + j);
			oled_draw_pixel(xcenter + xl, ycenter - y - j);
			oled_draw_pixel(xcenter - xl, ycenter - y - j);
		}
	}
}

void oled_display_clear(void) {
	for (uint16_t i = 0; i < 1024; i++) {
		buffer[i] = 0;
	}
	oled_display();
}

void oled_putc(char c, uint8_t line, uint8_t column) {
	if ((line > 8) || (column > 21)) return; // Clip right and bottom

	uint8_t pixelline;

	for (uint8_t i = 0; i < 6; i++) {
		if (i == 5) pixelline = 0x00;
		else pixelline = pgm_read_byte(oledchars + (c * 5) + i);
		oled_draw_pattern(pixelline, ((column - 1) << 2) + ((column - 1) << 1) + i, ((line - 1) << 3));
		buffer[((line - 1) << 7) + ((column - 1) << 2) + ((column - 1) << 1) + i] = pixelline;
	}
}

void oled_puts(char *str, uint8_t line, uint8_t column) {
	while (*str) {
		oled_putc(*str++, line, column);
		column++;
		if (column > 21) {
			column = 1;
			line++;
			if (line > 8) line = 1;
		}
	}
}


void oled_arrize(int32_t zahl, char *feld, uint8_t digits, uint8_t vorzeichen) {
	uint8_t neededlength = 1;

	if (vorzeichen || (zahl < 0)) {
		vorzeichen = 1;
		feld[0] = (zahl < 0) ? '-' : '+';
		if (zahl < 0) zahl = -zahl;
	}

	if (digits < 1) digits = 1;

	int32_t zahlkopie = zahl;

	while (zahlkopie /= 10) {
		neededlength++;
	}
	if (neededlength < digits) neededlength = digits;

	for (uint8_t i = neededlength + vorzeichen; (i - vorzeichen); i--) {
		feld[i-1] = (zahl % 10) + 0x30;
		zahl /= 10;
	}
	feld[neededlength + vorzeichen] = '\0';
}

#endif
