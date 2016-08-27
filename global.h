#ifndef 	_GLOBAL_H_
#define		_GLOBAL_H_


#define GRBL1	0x10
#define GRBL2	0x20
#define GRBL3	0x40
#define MODBUS  0x80

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <stdio.h>
#include <stdlib.h>

#include "uart.h"
#include "modbus.h"
#include "Time_Init.h"
#include "Uart_fifo.h"
#include "Pin_IO.h"
#include "ProcessingAcii.h"
#include "UartSend_To_GRBL.h"
#include "PutData_To_Queue.h"
#include "exter_int.h"

#endif