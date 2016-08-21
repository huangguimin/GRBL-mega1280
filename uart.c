#include "uart.h"

UartMRBUFF UartMRB = {UartModbusBuff,0};
/*************´®¿Ú³õÊ¼»¯*****************/

#ifdef      UART_0
    void USART0_initial(void)
    {
        //unsigned int a;
        //a=16000000/16/115200;//a=fosc/16/baud-1;
        //UBRR0L=a%256;
        //UBRR0H=a/256;
        UBRR0 = 16;
        UCSR0A |= (1<<U2X0);
        UCSR0B |= (1<<RXEN0)|(1<<TXEN0);        //½ÓÊÕÆ÷Óë·¢ËÍÆ÷Ê¹ÄÜ£»
        UCSR0C |= (1<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);        //ÉèÖÃÖ¡¸ñÊ½: 8 ¸öÊý¾ÝÎ», 1 ¸öÍ£Ö¹Î»£»
        UCSR0B |= (1<<RXCIE0)|(1<<TXCIE0)/*|(1<<UDRIE0)*/;        //USART½ÓÊÕÖÐ¶ÏÊ¹ÄÜ
        UART0_INT_RX_Stop;
        UART0_INT_TX_Start;
    }

    /************´®¿Ú·¢ËÍÒ»¸öÊý¾Ý********************/
    void USART0_Send_word(unsigned char data)
    {
        while (!(UCSR0A & (1<<UDRE0)));        //µÈ´ý·¢ËÍ»º³åÆ÷Îª¿Õ£»
        UDR0 = data;        //½«Êý¾Ý·ÅÈë»º³åÆ÷£¬·¢ËÍÊý¾Ý£»
    }

    void USART0_Send_string(unsigned char * data)
    {
        unsigned char i;
        for(i = 0; *(data+i) != '\0'; i++)
        {
            USART0_Send_word(*(data+i));
        }
    }

    ISR(USART0_RX_vect)
    {
        Time0_Start;
        if(UartMRB.buff_data_num < URSTDATANUM)
            UartMRB.pUartModbusBuffer[UartMRB.buff_data_num++] = UDR0;
    }

    ISR(USART0_TX_vect)
    {            
        static unsigned char count = 1;

        if(count < UartMRB.buff_data_num) 
            UDR0 = UartMRB.pUartModbusBuffer[count++];
        else
        {
            count = 1;
            UART0_INT_RX_Start;
            UartMRB.buff_data_num = 0;
        }
    }

  /*
    ISR(USART0_UDRE_vect)
    {
        
        if(QueueGetDataCount(&Uart1QCMDr))
            UDR0 = QueueOutput(&Uart1QCMDr);
        else
            UART0_INT_EMP_Stop;
        
    }*/
#endif

#ifdef      UART_1
    void USART1_initial(void)
    {
        //unsigned int a;
        //a=16000000/16/115200;//a=fosc/16/baud-1;
        //UBRR0L=a%256;
        //UBRR0H=a/256;
        UBRR1 = 16;
        UCSR1A |= (1<<U2X1);
        UCSR1B |= (1<<RXEN1)|(1<<TXEN1);        //½ÓÊÕÆ÷Óë·¢ËÍÆ÷Ê¹ÄÜ£»
        UCSR1C |= (1<<USBS1)|(1<<UCSZ10)|(1<<UCSZ11);        //ÉèÖÃÖ¡¸ñÊ½: 8 ¸öÊý¾ÝÎ», 1 ¸öÍ£Ö¹Î»£»
        UCSR1B |= (1<<RXCIE1)|(1<<TXCIE1)|(1<<UDRIE1);        //USART½ÓÊÕÖÐ¶ÏÊ¹ÄÜ
        UART1_INT_EMP_Stop;
        UART1_INT_RX_Start;
        UART1_INT_TX_Stop;
        QueueCreate(&Uart1QCMDs, Uart1QBuffs, Uart1BuffNums);
        QueueCreate(&Uart1QCMDr, Uart1QBuffr, Uart1BuffNumr);
    }

    /************´®¿Ú·¢ËÍÒ»¸öÊý¾Ý********************/
    void USART1_Send_word(unsigned char data)
    {
        while (!(UCSR1A & (1 << UDRE1)));        //µÈ´ý·¢ËÍ»º³åÆ÷Îª¿Õ£»
        UDR1 = data;        //½«Êý¾Ý·ÅÈë»º³åÆ÷£¬·¢ËÍÊý¾Ý£»
    }
    unsigned char  USART1_Send_word_no_wait(unsigned char data)
    {
        if(!(UCSR1A & (1 << UDRE1)))
            return 1; 
        UDR1 = data;  
        return 0;      
    }

    void USART1_Send_string(unsigned char * data)
    {
        unsigned char i;
        for(i = 0; *(data+i) != '\0'; i++)
        {
            USART1_Send_word(*(data+i));
        }
    }

    ISR(USART1_RX_vect)
    {           
        if(UCSR1A & (1<<DOR1))
        {
            while(1)
            {                   
                LED_Run(~LED_STATE);
                _delay_ms(1000);
                LED_Run(~LED_STATE);
                _delay_ms(1000);
            }
        }
        else
        QueueInput(&Uart1QCMDr,UDR1);
    }


    ISR(USART1_TX_vect)
    {
        unsigned char temp;
        if(QueueGetDataCount(&Uart1QCMDs))
        {
            temp = QueueOutput(&Uart1QCMDs);
            UDR1 = temp;
            if(temp == '\n')
                UART1_INT_TX_Stop; 
            //buffcount++;
        }
        else
            UART1_INT_TX_Stop;
        //UART1_INT_EMP_Start;
    }
    
unsigned char SnedRunTimeCMD1;
    ISR(USART1_UDRE_vect)
    {
        UDR1 = SnedRunTimeCMD1;
        UART1_INT_EMP_Stop;
    }
#endif

#ifdef      UART_2
    void USART2_initial(void)
    {
        //unsigned int a;
        //a=16000000/16/115200;//a=fosc/16/baud-1;
        //UBRR0L=a%256;
        //UBRR0H=a/256;
        UBRR2 = 16;
        UCSR2A |= (1<<U2X2);
        UCSR2B |= (1<<RXEN2)|(1<<TXEN2);        //½ÓÊÕÆ÷Óë·¢ËÍÆ÷Ê¹ÄÜ£»
        UCSR2C |= (1<<USBS2)|(1<<UCSZ20)|(1<<UCSZ21);        //ÉèÖÃÖ¡¸ñÊ½: 8 ¸öÊý¾ÝÎ», 1 ¸öÍ£Ö¹Î»£»
        UCSR2B |= (1<<RXCIE2)|(1<<TXCIE2);        //USART½ÓÊÕÖÐ¶ÏÊ¹ÄÜ
        UART2_INT_EMP_Stop;
        UART2_INT_RX_Start;
        UART2_INT_TX_Stop;
        QueueCreate(&Uart2QCMDs, Uart2QBuffs, Uart2BuffNums);
        QueueCreate(&Uart2QCMDr, Uart2QBuffr, Uart2BuffNumr);
    }

    /************´®¿Ú·¢ËÍÒ»¸öÊý¾Ý********************/
    void USART2_Send_word(unsigned char data)
    {
        while (!(UCSR2A & (1 << UDRE2)));        //µÈ´ý·¢ËÍ»º³åÆ÷Îª¿Õ£»
        UDR2 = data;        //½«Êý¾Ý·ÅÈë»º³åÆ÷£¬·¢ËÍÊý¾Ý£»
    }

    unsigned char  USART2_Send_word_no_wait(unsigned char data)
    {
        if(!(UCSR2A & (1 << UDRE2)))
            return 1; 
        UDR2 = data;  
        return 0;      
    }

    void USART2_Send_string(unsigned char * data)
    {
        unsigned char i;
        for(i = 0; *(data+i) != '\0'; i++)
        {
            USART2_Send_word(*(data+i));
        }
    }

    ISR(USART2_RX_vect)
    {
        if(UCSR2A & (1<<DOR2))
        {
            while(1)
            {                   
                LED_Run(~LED_STATE);
                _delay_ms(100);

                LED_Run(~LED_STATE);
                _delay_ms(100);
            }
        }
        else
            QueueInput(&Uart2QCMDr,UDR2);
        //UDR0 = temp;
    }


    ISR(USART2_TX_vect)
    {
        unsigned char temp;
        if(QueueGetDataCount(&Uart2QCMDs))
        {
            temp = QueueOutput(&Uart2QCMDs);
            UDR2 = temp;
            //UDR0 = temp;
            if(temp == '\n')
                UART2_INT_TX_Stop; 
            //buffcount++;
        }
        else
            UART2_INT_TX_Stop;
        //UART2_INT_EMP_Start;
    }
    
unsigned char SnedRunTimeCMD2;
    ISR(USART2_UDRE_vect)
    {
        UDR2 = SnedRunTimeCMD2;
        UART2_INT_EMP_Stop;
    }
#endif

/********´®¿Ú½ÓÊÕ***********/
/*
unsigned int USART_Receive( void )
{
    unsigned int i = 0x15FF;
// µÈ´ý½ÓÊÕÊý¾Ý
    do
    {
      if(!(i--)) return 300;
    }while (!(UCSR0A & (1<<RXC0)));
// ´Ó»º³åÆ÷ÖÐ»ñÈ¡²¢·µ»ØÊý¾Ý
    return UDR0;
}

*/
