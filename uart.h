
#ifndef __UART_H__
#define __UART_H__

#ifdef	MODBUS

#define UART0_INT_TX_Stop   (UCSR0B&=~(1<<TXCIE0))		//USART接收中断关闭
#define UART0_INT_TX_Start  (UCSR0B|=(1<<TXCIE0))
#define UART0_INT_TX_State  (UCSR0B & (1<<TXCIE0))

#define UART0_INT_RX_Stop   (UCSR0B&=~(1<<RXCIE0))		//USART接收中断关闭
#define UART0_INT_RX_Start  (UCSR0B|=(1<<RXCIE0))

#define UART0_INT_EMP_Stop   (UCSR0B&=~(1<<UDRIE0))		//USART接收中断关闭
#define UART0_INT_EMP_Start  (UCSR0B|=(1<<UDRIE0))

/*************串口初始化*****************/
void USART0_initial(void);
/************串口发送一个数据********************/
void USART0_Send_word(unsigned char data);
void USART0_Send_string(unsigned char * data);
/********串口接收数据中断，确定数据输出的状态***********/
#endif

#ifdef	GRBL1

#define UART1_INT_TX_Stop   (UCSR1B&=~(1<<TXCIE1))		//USART接收中断关闭
#define UART1_INT_TX_Start  (UCSR1B|=(1<<TXCIE1))
#define UART1_INT_TX_State  (UCSR1B & (1<<TXCIE1))

#define UART1_INT_RX_Stop   (UCSR1B&=~(1<<RXCIE1))		//USART接收中断关闭
#define UART1_INT_RX_Start  (UCSR1B|=(1<<RXCIE1))

#define UART1_INT_EMP_Stop   (UCSR1B&=~(1<<UDRIE1))		//USART接收中断关闭
#define UART1_INT_EMP_Start  (UCSR1B|=(1<<UDRIE1))
#define UART1_INT_REG        UCSR1B
#define UART1_INT_EMP_State  (UCSR1B&(1<<UDRIE1))
/*************串口初始化*****************/
void USART1_initial(void);
/************串口发送一个数据********************/
void USART1_Send_word(unsigned char data);
unsigned char  USART1_Send_word_nowait_IntStart();
void USART1_Send_string(unsigned char * data);
/********串口接收数据中断，确定数据输出的状态***********/

#endif

#ifdef	GRBL2

#define UART2_INT_TX_Stop   (UCSR2B&=~(1<<TXCIE2))		//USART接收中断关闭
#define UART2_INT_TX_Start  (UCSR2B|=(1<<TXCIE2))
#define UART2_INT_TX_State  (UCSR2B & (1<<TXCIE2))

#define UART2_INT_RX_Stop   (UCSR2B&=~(1<<RXCIE2))		//USART接收中断关闭
#define UART2_INT_RX_Start  (UCSR2B|=(1<<RXCIE2))

#define UART2_INT_EMP_Stop   (UCSR2B&=~(1<<UDRIE2))		//USART接收中断关闭
#define UART2_INT_EMP_Start  (UCSR2B|=(1<<UDRIE2))
#define UART2_INT_REG     	 UCSR2B
#define UART2_INT_EMP_State  (UCSR2B&(1<<UDRIE2))
/*************串口初始化*****************/
void USART2_initial(void);
/************串口发送一个数据********************/
void USART2_Send_word(unsigned char data);
unsigned char  USART2_Send_word_nowait_IntStart();
void USART2_Send_string(unsigned char * data);
/********串口接收数据中断，确定数据输出的状态***********/
#endif

#ifdef	GRBL3

#define UART3_INT_TX_Stop   (UCSR3B&=~(1<<TXCIE3))		//USART接收中断关闭
#define UART3_INT_TX_Start  (UCSR3B|=(1<<TXCIE3))
#define UART3_INT_TX_State  (UCSR3B & (1<<TXCIE3))

#define UART3_INT_RX_Stop   (UCSR3B&=~(1<<RXCIE3))		//USART接收中断关闭
#define UART3_INT_RX_Start  (UCSR3B|=(1<<RXCIE3))

#define UART3_INT_EMP_Stop   (UCSR3B&=~(1<<UDRIE3))		//USART接收中断关闭
#define UART3_INT_EMP_Start  (UCSR3B|=(1<<UDRIE3))
#define UART3_INT_REG     	 UCSR3B
#define UART3_INT_EMP_State  (UCSR3B&(1<<UDRIE3))

/*************串口初始化*****************/
void USART3_initial(void);
/************串口发送一个数据********************/
void USART3_Send_word(unsigned char data);
unsigned char  USART3_Send_word_nowait_IntStart();
void USART3_Send_string(unsigned char * data);
/********串口接收数据中断，确定数据输出的状态***********/
#endif

typedef struct BUFF_S
{
  unsigned char *pUartModbusBuffer;//缓冲
  unsigned int  buff_data_num;//需要发送的数据个数
}UartMRBUFF;

#define URSTDATANUM 120
unsigned char UartModbusBuff[URSTDATANUM];

extern UartMRBUFF UartMRB;
#endif