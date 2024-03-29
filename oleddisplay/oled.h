/*
 * oled.h
 *
 *  Created on: 17.06.2014
 *      Author: Felix
 */

#ifndef OLED_H_
#define OLED_H_

#define OLED_ADDRESS 0x78


void oled_send(uint8_t command, uint8_t datamode);
uint8_t oled_read(uint8_t datamode);
void oled_init(void);
void oled_display_clear(void);

void oled_draw_pixel(uint8_t x, uint8_t y);
void oled_draw_pattern(char c, uint8_t x, uint8_t y);
void oled_draw_vertical_line(uint8_t x, uint8_t ystart, uint8_t ystop);
void oled_draw_rectangle(uint8_t xstart, uint8_t ystart, uint8_t xstop, uint8_t ystop);

void oled_putc(char c, uint8_t line, uint8_t column);
void oled_puts(char *str, uint8_t line, uint8_t column);

#endif /* OLED_H_ */
