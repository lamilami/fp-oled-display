/*
 * global.h
 *
 *  Created on: 29.06.2013
 *      Author: Felix
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include "portmakros.h"
#include "uart.h"
#include "i2c.h"
#include "oled_buffered.h"
#include "crcchk.h"
#include "1wire.h"

#define SIZE	16
#define TIMEOUTVAL			F_CPU*4
#define MAX_ARRAYSIZE		180

#endif /* GLOBAL_H_ */
