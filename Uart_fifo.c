/********************************
  队列管理模块
  文件名:queue.c
*******************************/
#include "global.h"

#ifdef GRBL1
HQUEUE Uart1QCMDs;
HQUEUE Uart1QCMDr;
HQUEUE Uart1QCMDRTs;
#endif

#ifdef GRBL2
HQUEUE Uart2QCMDs;
HQUEUE Uart2QCMDr;
HQUEUE Uart2QCMDRTs;
#endif

#ifdef GRBL3
HQUEUE Uart3QCMDs;
HQUEUE Uart3QCMDr;
HQUEUE Uart3QCMDRTs;
#endif
//向队列插入一字节
unsigned char QueueInput(PHQUEUE Q,unsigned char dat)
{
  if(Q->data_count < Q->buf_size)
  {
    Q->pBuffer[Q->in_index++]=dat;    //写入数据
    //Q->in_index=(Q->in_index+1) % (Q->buf_size);//调整入口地址
    if(Q->in_index >= Q->buf_size)
      Q->in_index= 0;
    cli();
    Q->data_count++;  //调整数据个数(此操作不可被中断)
    sei();
    return 0;
  }
  return 1;
  /*else
  {
    if(Q->error<255)
      Q->error++;
  }*/
}


//在中断中向队列插入一字节
unsigned char QueueInput_Int(PHQUEUE Q,unsigned char dat)
{
  if(Q->data_count < Q->buf_size)
  {
    Q->pBuffer[Q->in_index++]=dat;    //写入数据
    //Q->in_index=(Q->in_index+1) % (Q->buf_size);//调整入口地址
    if(Q->in_index >= Q->buf_size)
      Q->in_index= 0;
    Q->data_count++;  //调整数据个数(此操作不可被中断)
    return 0;
  }
  return 1;
  /*else
  {
    if(Q->error<255)
      Q->error++;
  }*/
}
//从队列读出一字节
unsigned char QueueOutput(PHQUEUE Q)
{
  unsigned char Ret=0;
  if(Q->data_count > 0)
  {
    Ret=Q->pBuffer[Q->out_index++];  //读数据
    if(Q->out_index >= Q->buf_size)  //调整出口地址
      Q->out_index = 0;
    cli();
    Q->data_count--;  //调整数据个数(此操作不可被中断)
    sei();
  }
  return Ret;
}

unsigned char QueueOutput_Int(PHQUEUE Q)
{
  unsigned char Ret=0;
  if(Q->data_count > 0)
  {
    Ret=Q->pBuffer[Q->out_index++];  //读数据
    if(Q->out_index >= Q->buf_size)  //调整出口地址
      Q->out_index = 0;
    Q->data_count--;
  }
  return Ret;
}

//清空队列,执行时不可被中断
void QueueClear(PHQUEUE Q)
{
  cli();
  Q->in_index = 0;
  Q->out_index = 0;
  Q->data_count = 0;
  sei();
  //Q->error = 0;
}

//初始化一队列
void QueueCreate(PHQUEUE Q,unsigned char *buffer,unsigned int buf_size)
{
  Q->pBuffer = buffer;
  Q->buf_size = buf_size;
  QueueClear(Q);
}
