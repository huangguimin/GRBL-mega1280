#ifndef __UART_FIFO_H__
#define __UART_FIFO_H__

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
unsigned char QueueInput_Int(PHQUEUE Q,unsigned char dat);
unsigned char QueueOutput(PHQUEUE Q);
unsigned char QueueOutput_Int(PHQUEUE Q);
//unsigned int QueueGetDataCount(PHQUEUE Q);
void QueueClear(PHQUEUE Q);
void QueueCreate(PHQUEUE Q,unsigned char *buffer,unsigned int buf_size);

//获得队列中数据个数
#define QueueGetDataCount(Q)	((Q)->data_count)	

#ifdef 	GRBL1

#define Uart1BuffNums 100
#define Uart1BuffNumr 100
unsigned char Uart1QBuffs[Uart1BuffNums];
unsigned char Uart1QBuffr[Uart1BuffNumr];
extern HQUEUE Uart1QCMDs;
extern HQUEUE Uart1QCMDr;
#define Uart1RunTimes 3
unsigned char Uart1QBuffRunTimes[Uart1RunTimes];
extern HQUEUE Uart1QCMDRTs;

#endif

#ifdef 	GRBL2

#define Uart2BuffNums 100
#define Uart2BuffNumr 100
unsigned char Uart2QBuffs[Uart2BuffNums];
unsigned char Uart2QBuffr[Uart2BuffNumr];
extern HQUEUE Uart2QCMDs;
extern HQUEUE Uart2QCMDr;
#define Uart2RunTimes 3
unsigned char Uart2QBuffRunTimes[Uart2RunTimes];
extern HQUEUE Uart2QCMDRTs;

#endif

#ifdef GRBL3

#define Uart3BuffNums 100
#define Uart3BuffNumr 100
unsigned char Uart3QBuffs[Uart3BuffNums];
unsigned char Uart3QBuffr[Uart3BuffNumr];
extern HQUEUE Uart3QCMDs;
extern HQUEUE Uart3QCMDr;
#define Uart3RunTimes 3
unsigned char Uart3QBuffRunTimes[Uart3RunTimes];
extern HQUEUE Uart3QCMDRTs;
#endif
#endif
