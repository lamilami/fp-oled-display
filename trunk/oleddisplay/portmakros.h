/*
 * portmakros.h
 *
 *  Created on: 25.04.2013
 *      Author: Felix
 */

#include "global.h"

#ifndef PORTMAKROS_H_
#define PORTMAKROS_H_

// Definitionen für IO-Port-Makros
#define 	CONCAT(x,y) 	x##y
#define 	DDR(x)  		CONCAT(DDR,x)
#define 	PORT(x) 		CONCAT(PORT,x)
#define 	PIN(x)  		CONCAT(PIN,x)

#define		TIFR(x)			CONCAT(TIFR,x)
#define		TIMSK(x)		CONCAT(TIMSK,x)
#define		TOIE(x)			CONCAT(TOIE,x)
#define		TCNT(x)			CONCAT(TCNT,x)
#define		TOV(x)			CONCAT(TOV,x)


#endif /* PORTMAKROS_H_ */
