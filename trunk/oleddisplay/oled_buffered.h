/*
 * oled.h
 *
 *  Created on: 17.06.2014
 *      Author: Felix
 */

#ifndef OLEDBUFFERED_H_
#define OLEDBUFFERED_H_

#define SDAPORT	B
#define SDA		0
#define SCLPORT	D
#define SCL		7

#define OLED_ADDRESS 0x78


#define SDA_PORT			PORT(SDAPORT)
#define SDA_DDR				DDR(SDAPORT)
#define SDA_PIN				PIN(SDAPORT)

#define SCL_PORT			PORT(SCLPORT)
#define SCL_DDR				DDR(SCLPORT)
#define SCL_PIN				PIN(SCLPORT)

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
uint8_t i2c_transmit(uint8_t byte);
uint8_t i2c_receive(uint8_t ack);

void oled_display(void);

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
