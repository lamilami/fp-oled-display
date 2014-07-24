/*
 * i2c.h
 *
 *  Created on: 24.07.2014
 *      Author: Felix
 */

#ifndef I2C_H_
#define I2C_H_

#define SDAPORT	B
#define SDA		0
#define SCLPORT	D
#define SCL		7

#define SDA_PORT			PORT(SDAPORT)
#define SDA_DDR				DDR(SDAPORT)
#define SDA_PIN				PIN(SDAPORT)

#define SCL_PORT			PORT(SCLPORT)
#define SCL_DDR				DDR(SCLPORT)
#define SCL_PIN				PIN(SCLPORT)


#define I2C_DATA_HIGH		SDA_DDR &= ~(1 << SDA); while(!(SDA_PIN & (1<<SDA)));
#define I2C_DATA_LOW		SDA_DDR |= (1 << SDA); while( (SDA_PIN & (1<<SDA)));
#define I2C_DATA_RELEASE 	SDA_DDR &= ~(1 << SDA);
#define I2C_CLOCK_HIGH		SCL_DDR &= ~(1 << SCL); while(!(SCL_PIN & (1<<SCL)));
#define I2C_CLOCK_LOW		SCL_DDR |= (1 << SCL); while( (SCL_PIN & (1<<SCL)));


void i2c_start(void);
void i2c_stop(void);
uint8_t i2c_transmit(uint8_t byte);
uint8_t i2c_receive(uint8_t ack);

#endif /* I2C_H_ */
