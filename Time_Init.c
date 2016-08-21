#include "Time_Init.h"

/*--------------------Time0--------------------------------*/
volatile unsigned char TimerT3_5 = 0;

void Time0_init()
{
    TCCR0A |= (1<<WGM01);
    //TCCR0B |= (1<<CS00)|(1<<CS02);//CTC模式、启动T0，1024分频
    OCR0A = 27;//0.000064*27 = 0.00175s// 3.5字节 需要1750us 比特率115200的时候
    TIMSK0 |= (1<<OCIE0A);
    Time0_Stop;                 
}

ISR(TIMER0_COMPA_vect)
{   
    UART0_INT_RX_Stop;
    Time0_Stop;
    TimerT3_5 = 1;  
    UartMRB.buff_data_num = 0;  
}

/*--------------------Time1--------------------------------*/

void Time1_init()
{
    TCCR1B |= (1<<WGM12)|(1<<CS10)|(1<<CS12);//CTC模式、启动T1，外部时钟源1024
    OCR1A = 7812/3;//0.000064*7812.5 = 0.5s
    TCNT1 = 0;
    TIMSK1 |= (1<<OCIE1A);
    Time1_Stop;
}

char SendCmdStateFlag = 0;
ISR(TIMER1_COMPA_vect)
{   
    SendCmdStateFlag = 1;
}
/*
unsigned char mark = 0;
float tcnt1temp = 0;
extern unsigned long totallength;
extern float runspeed;

ISR(TIMER1_CAPT_vect)
{

}
*/
/*--------------------Time2--------------------------------*/
/*
void Time2_init()
{
    TCCR2A |= (1<<WGM21);//CTC模式、启动T2，8分频
    TCCR2B |= (1<<CS21);
    OCR2A = 20; //~0.00001ms
    TIMSK2 |= (1<<OCIE2A);
    TCCR2B &= 0xF8;//关闭T2
    TCNT2 = 0;
}

unsigned int time10us_count = 0;
ISR(TIMER2_COMPA_vect)
{   

}
*/
/*--------------------Time3--------------------------------*/
/*
void Time3_init()
{
    TCCR3B |= (1<<WGM32);//CTC模式、启动T1，1024分频|(1<<CS30)|(1<<CS32)
    OCR3AL = 312%256;//0.02s
    OCR3AH = 312/256;
    TIMSK |= (1<<OCIE3A);
    TCCR3B &= 0xF8;//关闭T1时钟计数  
    //TCCR3B |= (1<<CS30)|(1<<CS32);////开启T1时钟计数 
}

interrupt [TIM3_COMPA] void MPC006_Receive_Time_Out()
{
    TCCR3B &= 0xF8; //关T3定时器时钟频率
    TCNT3L = 0;
    TCNT3H = 0;       //清除T3计时寄存器     
    //USART_Send_string_1(Usart1_Send_Init_P,Usart1_Send_Length);  
}
  */