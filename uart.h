
#ifndef __UART_H__
#define __UART_H__

#ifdef	MODBUS

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

#ifdef	GRBL1

#define UART1_INT_TX_Stop   (UCSR1B&=~(1<<TXCIE1))		//USART�����жϹر�
#define UART1_INT_TX_Start  (UCSR1B|=(1<<TXCIE1))
#define UART1_INT_TX_State  (UCSR1B & (1<<TXCIE1))

#define UART1_INT_RX_Stop   (UCSR1B&=~(1<<RXCIE1))		//USART�����жϹر�
#define UART1_INT_RX_Start  (UCSR1B|=(1<<RXCIE1))

#define UART1_INT_EMP_Stop   (UCSR1B&=~(1<<UDRIE1))		//USART�����жϹر�
#define UART1_INT_EMP_Start  (UCSR1B|=(1<<UDRIE1))
#define UART1_INT_REG        UCSR1B
#define UART1_INT_EMP_State  (UCSR1B&(1<<UDRIE1))
/*************���ڳ�ʼ��*****************/
void USART1_initial(void);
/************���ڷ���һ������********************/
void USART1_Send_word(unsigned char data);
unsigned char  USART1_Send_word_nowait_IntStart();
void USART1_Send_string(unsigned char * data);
/********���ڽ��������жϣ�ȷ�����������״̬***********/

#endif

#ifdef	GRBL2

#define UART2_INT_TX_Stop   (UCSR2B&=~(1<<TXCIE2))		//USART�����жϹر�
#define UART2_INT_TX_Start  (UCSR2B|=(1<<TXCIE2))
#define UART2_INT_TX_State  (UCSR2B & (1<<TXCIE2))

#define UART2_INT_RX_Stop   (UCSR2B&=~(1<<RXCIE2))		//USART�����жϹر�
#define UART2_INT_RX_Start  (UCSR2B|=(1<<RXCIE2))

#define UART2_INT_EMP_Stop   (UCSR2B&=~(1<<UDRIE2))		//USART�����жϹر�
#define UART2_INT_EMP_Start  (UCSR2B|=(1<<UDRIE2))
#define UART2_INT_REG     	 UCSR2B
#define UART2_INT_EMP_State  (UCSR2B&(1<<UDRIE2))
/*************���ڳ�ʼ��*****************/
void USART2_initial(void);
/************���ڷ���һ������********************/
void USART2_Send_word(unsigned char data);
unsigned char  USART2_Send_word_nowait_IntStart();
void USART2_Send_string(unsigned char * data);
/********���ڽ��������жϣ�ȷ�����������״̬***********/
#endif

#ifdef	GRBL3

#define UART3_INT_TX_Stop   (UCSR3B&=~(1<<TXCIE3))		//USART�����жϹر�
#define UART3_INT_TX_Start  (UCSR3B|=(1<<TXCIE3))
#define UART3_INT_TX_State  (UCSR3B & (1<<TXCIE3))

#define UART3_INT_RX_Stop   (UCSR3B&=~(1<<RXCIE3))		//USART�����жϹر�
#define UART3_INT_RX_Start  (UCSR3B|=(1<<RXCIE3))

#define UART3_INT_EMP_Stop   (UCSR3B&=~(1<<UDRIE3))		//USART�����жϹر�
#define UART3_INT_EMP_Start  (UCSR3B|=(1<<UDRIE3))
#define UART3_INT_REG     	 UCSR3B
#define UART3_INT_EMP_State  (UCSR3B&(1<<UDRIE3))

/*************���ڳ�ʼ��*****************/
void USART3_initial(void);
/************���ڷ���һ������********************/
void USART3_Send_word(unsigned char data);
unsigned char  USART3_Send_word_nowait_IntStart();
void USART3_Send_string(unsigned char * data);
/********���ڽ��������жϣ�ȷ�����������״̬***********/
#endif

typedef struct BUFF_S
{
  unsigned char *pUartModbusBuffer;//����
  unsigned int  buff_data_num;//��Ҫ���͵����ݸ���
}UartMRBUFF;

#define URSTDATANUM 120
unsigned char UartModbusBuff[URSTDATANUM];

extern UartMRBUFF UartMRB;
#endif