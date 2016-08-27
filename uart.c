#include "global.h"

UartMRBUFF UartMRB = {UartModbusBuff,0};
/*************´®¿Ú³õÊ¼»¯*****************/

#ifdef      MODBUS
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
        /*UCSR0B |= (1<<RXCIE0)|(1<<TXCIE0)|(1<<UDRIE0)*/;        //USART½ÓÊÕÖÐ¶ÏÊ¹ÄÜ
        UART0_INT_RX_Start;
        UART0_INT_TX_Stop;
        UART0_INT_EMP_Stop;
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

/*
    ISR(USART0_TX_vect)
    {            
        static unsigned char sendcount = 1;

        if(sendcount < UartMRB.buff_data_num) 
            UDR0 = UartMRB.pUartModbusBuffer[sendcount++];
        else
        {
            sendcount = 1;
            UART0_INT_RX_Start;
            UartMRB.buff_data_num = 0;
        }
    }
*/
    ISR(USART0_UDRE_vect)
    {
        static unsigned char sendcount = 0;

        if(sendcount < UartMRB.buff_data_num) 
            UDR0 = UartMRB.pUartModbusBuffer[sendcount++];
        else
        {
            UART0_INT_EMP_Stop;
            UartMRB.buff_data_num = 0;
            sendcount = 0;
        }      
    }
#endif

#ifdef      GRBL1
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
        QueueCreate(&Uart1QCMDRTs, Uart1QBuffRunTimes, Uart1RunTimes);
    }

    /************´®¿Ú·¢ËÍÒ»¸öÊý¾Ý********************/
    void USART1_Send_word(unsigned char data)
    {
        while (!(UCSR1A & (1 << UDRE1)));        //µÈ´ý·¢ËÍ»º³åÆ÷Îª¿Õ£»
        UDR1 = data;        //½«Êý¾Ý·ÅÈë»º³åÆ÷£¬·¢ËÍÊý¾Ý£»
    }

    unsigned char  USART1_Send_word_nowait_IntStart()
    {
        if(!(UCSR1A & (1 << UDRE1)))
            return 1;
        if(!QueueGetDataCount(&Uart1QCMDs))
            return 2; 
        cli();
        UDR1 = QueueOutput_Int(&Uart1QCMDs);        //½«Êý¾Ý·ÅÈë»º³åÆ÷£¬·¢ËÍÊý¾Ý£»
        UART1_INT_TX_Start;
        sei();
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
        QueueInput_Int(&Uart1QCMDr,UDR1);
    }


    ISR(USART1_TX_vect)
    {
        unsigned char temp;
        if(QueueGetDataCount(&Uart1QCMDs))
        {
            temp = QueueOutput_Int(&Uart1QCMDs);
            if(temp == '\0')
                UART1_INT_TX_Stop; 
            else
                UDR1 = temp;
        }
    }
    
    ISR(USART1_UDRE_vect)
    {
        if(QueueGetDataCount(&Uart1QCMDRTs))
        {    
            UDR1 = QueueOutput_Int(&Uart1QCMDRTs);
            UART1_INT_EMP_Stop;
        }
    }
#endif

#ifdef      GRBL2
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
        QueueCreate(&Uart2QCMDRTs, Uart2QBuffRunTimes, Uart2RunTimes);
    }

    /************´®¿Ú·¢ËÍÒ»¸öÊý¾Ý********************/
    void USART2_Send_word(unsigned char data)
    {
        while (!(UCSR2A & (1 << UDRE2)));        //µÈ´ý·¢ËÍ»º³åÆ÷Îª¿Õ£»
        UDR2 = data;        //½«Êý¾Ý·ÅÈë»º³åÆ÷£¬·¢ËÍÊý¾Ý£»
    }

    unsigned char  USART2_Send_word_nowait_IntStart()
    {
        if(!(UCSR2A & (1 << UDRE2)))
            return 1; 
        if(!QueueGetDataCount(&Uart2QCMDs))
            return 2; 
        cli();
        UDR2 = QueueOutput_Int(&Uart2QCMDs); 
        UART2_INT_TX_Start; 
        sei();
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
        QueueInput_Int(&Uart2QCMDr,UDR2);
    }


    ISR(USART2_TX_vect)
    {
        unsigned char temp;
        if(QueueGetDataCount(&Uart2QCMDs))
        {
            temp = QueueOutput_Int(&Uart2QCMDs);
            if(temp == '\0')
                UART2_INT_TX_Stop; 
            else
                UDR2 = temp;

        }
    }
    
    ISR(USART2_UDRE_vect)
    {
        if(QueueGetDataCount(&Uart2QCMDRTs))
        {    
            UDR2 = QueueOutput_Int(&Uart2QCMDRTs);
            UART2_INT_EMP_Stop;
        }
    }
#endif

#ifdef      GRBL3
    void USART3_initial(void)
    {
        //unsigned int a;
        //a=16000000/16/115200;//a=fosc/16/baud-1;
        //UBRR0L=a%256;
        //UBRR0H=a/256;
        UBRR3 = 16;
        UCSR3A |= (1<<U2X3);
        UCSR3B |= (1<<RXEN3)|(1<<TXEN3);        //½ÓÊÕÆ÷Óë·¢ËÍÆ÷Ê¹ÄÜ£»
        UCSR3C |= (1<<USBS3)|(1<<UCSZ30)|(1<<UCSZ31);        //ÉèÖÃÖ¡¸ñÊ½: 8 ¸öÊý¾ÝÎ», 1 ¸öÍ£Ö¹Î»£»
        UCSR3B |= (1<<RXCIE3)|(1<<TXCIE3);        //USART½ÓÊÕÖÐ¶ÏÊ¹ÄÜ
        UART3_INT_EMP_Stop;
        UART3_INT_RX_Start;
        UART3_INT_TX_Stop;
        QueueCreate(&Uart3QCMDs, Uart3QBuffs, Uart3BuffNums);
        QueueCreate(&Uart3QCMDr, Uart3QBuffr, Uart3BuffNumr);
        QueueCreate(&Uart3QCMDRTs, Uart3QBuffRunTimes, Uart3RunTimes);
    }

    /************´®¿Ú·¢ËÍÒ»¸öÊý¾Ý********************/
    void USART3_Send_word(unsigned char data)
    {
        while (!(UCSR3A & (1 << UDRE3)));        //µÈ´ý·¢ËÍ»º³åÆ÷Îª¿Õ£»
        UDR3 = data;        //½«Êý¾Ý·ÅÈë»º³åÆ÷£¬·¢ËÍÊý¾Ý£»
    }

    unsigned char  USART3_Send_word_nowait_IntStart()
    {
        if(!(UCSR3A & (1 << UDRE3)))
            return 1; 
        if(!QueueGetDataCount(&Uart3QCMDs))
            return 2; 
        cli();
        UDR3 = QueueOutput_Int(&Uart3QCMDs); 
        UART3_INT_TX_Start; 
        sei();
        return 0;      
    }

    void USART3_Send_string(unsigned char * data)
    {
        unsigned char i;
        for(i = 0; *(data+i) != '\0'; i++)
        {
            USART3_Send_word(*(data+i));
        }
    }

    ISR(USART3_RX_vect)
    {
        QueueInput_Int(&Uart3QCMDr,UDR3);
    }


    ISR(USART3_TX_vect)
    {
        unsigned char temp;
        if(QueueGetDataCount(&Uart3QCMDs))
        {
            temp = QueueOutput_Int(&Uart3QCMDs);
            if(temp == '\0')
                UART3_INT_TX_Stop; 
            else
                UDR3 = temp;
        }
    }
    
    ISR(USART3_UDRE_vect)
    {
        if(QueueGetDataCount(&Uart3QCMDRTs))
        {    
            UDR3 = QueueOutput_Int(&Uart3QCMDRTs);
            UART3_INT_EMP_Stop;
        }
    }
#endif

