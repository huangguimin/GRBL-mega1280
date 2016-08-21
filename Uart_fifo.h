#ifndef __UART_FIFO_H__
#define __UART_FIFO_H__
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
//队列数据结构
typedef struct QUEUE_S
{
  unsigned int in_index;//入队地址
  unsigned int out_index;//出队地址
  unsigned int buf_size; //缓冲区长度
  unsigned char *pBuffer;//缓冲
  volatile unsigned int  data_count; //队列内数据个数
  //unsigned char error;
}HQUEUE,*PHQUEUE;

unsigned char QueueInput(PHQUEUE Q,unsigned char dat);
unsigned char QueueOutput(PHQUEUE Q);
//unsigned int QueueGetDataCount(PHQUEUE Q);
void QueueClear(PHQUEUE Q);
void QueueCreate(PHQUEUE Q,unsigned char *buffer,unsigned int buf_size);

//获得队列中数据个数
#define QueueGetDataCount(Q)	((Q)->data_count)	

#define Uart1BuffNums 50
#define Uart1BuffNumr 128

unsigned char Uart1QBuffs[Uart1BuffNums];
unsigned char Uart1QBuffr[Uart1BuffNumr];

#define Uart2BuffNums 50
#define Uart2BuffNumr 128
unsigned char Uart2QBuffs[Uart2BuffNums];
unsigned char Uart2QBuffr[Uart2BuffNumr];

extern HQUEUE Uart1QCMDs;
extern HQUEUE Uart1QCMDr;

extern HQUEUE Uart2QCMDs;
extern HQUEUE Uart2QCMDr;

#endif
