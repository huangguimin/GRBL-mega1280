
#ifndef __UART_H__
#define __UART_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "Time_Init.h"
#include "Uart_fifo.h"
#include "Pin_IO.h"

#define     UART_0
#define     UART_1
#define     UART_2

#ifdef	UART_0
#define UART0_INT_TX_Stop   (UCSR0B&=~(1<<TXCIE0))		//USART�����жϹر�
#define UART0_INT_TX_Start  (UCSR0B|=(1<<TXCIE0))
#define UART0_INT_TX_State  (UCSR0B & (1<<TXCIE0))

#define UART0_INT_RX_Stop   (UCSR0B&=~(1<<RXCIE0))		//USART�����жϹر�
#define UART0_INT_RX_Start  (UCSR0B|=(1<<RXCIE0))

#define UART0_INT_EMP_Stop   (UCSR0B&=~(1<<UDRIE0))		//USART�����жϹر�
#define UART0_INT_EMP_Start  (UCSR0B|=(1<<UDRIE0))

/*************���ڳ�ʼ��*****************/
void USART0_initial(void);
/************���ڷ���һ������********************/
void USART0_Send_word(unsigned char data);
void USART0_Send_string(unsigned char * data);
/********���ڽ��������жϣ�ȷ�����������״̬***********/
#endif

#ifdef	UART_1

#define UART1_INT_TX_Stop   (UCSR1B&=~(1<<TXCIE1))		//USART�����жϹر�
#define UART1_INT_TX_Start  (UCSR1B|=(1<<TXCIE1))
#define UART1_INT_TX_State  (UCSR1B & (1<<TXCIE1))

#define UART1_INT_RX_Stop   (UCSR1B&=~(1<<RXCIE1))		//USART�����жϹر�
#define UART1_INT_RX_Start  (UCSR1B|=(1<<RXCIE1))

#define UART1_INT_EMP_Stop   (UCSR1B&=~(1<<UDRIE1))		//USART�����жϹر�
#define UART1_INT_EMP_Start  (UCSR1B|=(1<<UDRIE1))
#define UART1_INT_REG        UCSR1B
/*************���ڳ�ʼ��*****************/
void USART1_initial(void);
/************���ڷ���һ������********************/
void USART1_Send_word(unsigned char data);
unsigned char  USART1_Send_word_no_wait(unsigned char data);
void USART1_Send_string(unsigned char * data);
/********���ڽ��������жϣ�ȷ�����������״̬***********/
#endif

#ifdef	UART_2

#define UART2_INT_TX_Stop   (UCSR2B&=~(1<<TXCIE2))		//USART�����жϹر�
#define UART2_INT_TX_Start  (UCSR2B|=(1<<TXCIE2))
#define UART2_INT_TX_State  (UCSR2B & (1<<TXCIE2))

#define UART2_INT_RX_Stop   (UCSR2B&=~(1<<RXCIE2))		//USART�����жϹر�
#define UART2_INT_RX_Start  (UCSR2B|=(1<<RXCIE2))

#define UART2_INT_EMP_Stop   (UCSR2B&=~(1<<UDRIE2))		//USART�����жϹر�
#define UART2_INT_EMP_Start  (UCSR2B|=(1<<UDRIE2))
#define UART2_INT_REG     	 UCSR2B

/*************���ڳ�ʼ��*****************/
void USART2_initial(void);
/************���ڷ���һ������********************/
void USART2_Send_word(unsigned char data);
unsigned char  USART2_Send_word_no_wait(unsigned char data);
void USART2_Send_string(unsigned char * data);
/********���ڽ��������жϣ�ȷ�����������״̬***********/
#endif
//unsigned int USART_Receive(void);

//extern HQUEUE UartQ0;

typedef struct BUFF_S
{
  unsigned char *pUartModbusBuffer;//����
  unsigned int  buff_data_num;//��Ҫ���͵����ݸ���
}UartMRBUFF;

#define URSTDATANUM 1200
unsigned char UartModbusBuff[URSTDATANUM];

extern unsigned char SnedRunTimeCMD1;
extern unsigned char SnedRunTimeCMD2;
extern UartMRBUFF UartMRB;
#endif