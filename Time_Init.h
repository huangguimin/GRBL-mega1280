#ifndef __TIME_INIT_H__
#define __TIME_INIT_H__
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "Pin_IO.h"
#include <util/delay.h>

#define Time0_Start	(TCCR0B |= (1<<CS00)|(1<<CS02),TCNT0 = 0)//1024f
#define Time0_Stop	(TCCR0B &= 0xF8,TCNT0 = 0)

#define Time1_Start	(TCCR1B |= (1<<CS10)|(1<<CS12),TCNT1 = 0)//1024f
#define Time1_Stop	(TCCR1B &= 0xF8,TCNT1 = 0)
//#define Time1_Start	(TCCR1B |= (1<<CS10)|(1<<CS12),TCNT1 = 0)
//#define Time1_Stop	(TCCR1B &= 0xF8,TCNT1 = 0)
void Time0_init();
void Time1_init();
//void Time2_init();
//void Time3_init();
extern char SendCmdStateFlag;
extern volatile unsigned char TimerT3_5;

#endif