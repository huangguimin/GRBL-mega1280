
#ifndef __PIN_IO__
#define __PIN_IO__
/*****************Atmega128A PLC I/O引脚设置*************************/
#include <avr/io.h>


typedef struct _bit_struct 
{ 
    unsigned char bit0 : 1; 
    unsigned char bit1 : 1; 
    unsigned char bit2 : 1; 
    unsigned char bit3 : 1; 
    unsigned char bit4 : 1; 
    unsigned char bit5 : 1; 
    unsigned char bit6 : 1; 
    unsigned char bit7 : 1; 
}bit_field; 

#define PORT(addr)  (*((volatile  bit_field *)(&addr)))

/*********input_X**********/
#define X0   (PORT(PINA).bit3)
#define X1   (PORT(PINA).bit4)
#define X2   (PORT(PINA).bit5)
#define X3   (PORT(PINA).bit6)
#define X4   (PORT(PINA).bit7)
#define X5   (PORT(PING).bit2)
#define X6   (PORT(PINC).bit7)
#define X7   (PORT(PINC).bit6)
#define X8   (PORT(PINC).bit5)
#define X9   (PORT(PINC).bit4)
#define X10  (PORT(PINC).bit3)
#define X11  (PORT(PINC).bit2)
#define X12  (PORT(PINC).bit1)
#define X13  (PORT(PINC).bit0)
#define X14  (PORT(PING).bit1)
#define X15  (PORT(PING).bit0)
#define X16  (PORT(PIND).bit7)
#define X17  (PORT(PIND).bit6)
#define X18  (PORT(PIND).bit5)
#define X19  (PORT(PIND).bit4)
#define X20  (PORT(PIND).bit3) //外部中断3
#define X21  (PORT(PIND).bit2) //外部中断2
#define X22  (PORT(PIND).bit1) //外部中断1
#define X23  (PORT(PIND).bit0) //外部中断0

/*********output_Y**********/
#define Y0(X)    (PORT(PORTA).bit2 = X)
#define Y1(X)    (PORT(PORTA).bit0 = X)
#define Y2(X)    (PORT(PORTA).bit1 = X)
#define Y3(X)    (PORT(PORTF).bit6 = X)
#define Y4(X)    (PORT(PORTF).bit7 = X)
#define Y5(X)    (PORT(PORTF).bit4 = X)
#define Y6(X)    (PORT(PORTF).bit5 = X)
#define Y7(X)    (PORT(PORTF).bit2 = X)
#define Y8(X)    (PORT(PORTF).bit3 = X)
#define Y9(X)    (PORT(PORTF).bit0 = X)
#define Y10(X)   (PORT(PORTF).bit1 = X)
#define Y11(X)   (PORT(PORTE).bit3 = X)
#define Y12(X)   (PORT(PORTE).bit2 = X)
#define Y13(X)   (PORT(PORTE).bit5 = X)
#define Y14(X)   (PORT(PORTE).bit4 = X)
#define Y15(X)   (PORT(PORTE).bit7 = X)
#define Y16(X)   (PORT(PORTE).bit6 = X)
#define Y17(X)   (PORT(PORTB).bit5 = X)
#define Y18(X)   (PORT(PORTB).bit4 = X)
#define Y19(X)   (PORT(PORTB).bit7 = X)
#define Y20(X)   (PORT(PORTB).bit6 = X)
#define Y21(X)   (PORT(PORTG).bit4 = X)
//#define Y22(X)   PORTG=(PORTG&0xF7)|(X<<3)

/*********out Y state***********/
#define R_Y0   (PORT(PINA).bit2)
#define R_Y1   (PORT(PINA).bit0)
#define R_Y2   (PORT(PINA).bit1)
#define R_Y3   (PORT(PINF).bit6)
#define R_Y4   (PORT(PINF).bit7)
#define R_Y5   (PORT(PINF).bit4)
#define R_Y6   (PORT(PINF).bit5)
#define R_Y7   (PORT(PINF).bit2)
#define R_Y8   (PORT(PINF).bit3)
#define R_Y9   (PORT(PINF).bit0)
#define R_Y10  (PORT(PINF).bit1)
#define R_Y11  (PORT(PINE).bit3)
#define R_Y12  (PORT(PINE).bit2)
#define R_Y13  (PORT(PINE).bit5)
#define R_Y14  (PORT(PINE).bit4)
#define R_Y15  (PORT(PINE).bit7)
#define R_Y16  (PORT(PINE).bit6)
#define R_Y17  (PORT(PINB).bit5)
#define R_Y18  (PORT(PINB).bit4)
#define R_Y19  (PORT(PINB).bit7)
#define R_Y20  (PORT(PINB).bit6)
#define R_Y21  (PORT(PING).bit4)
#define R_Y22  (PORT(PING).bit3)

/********************/

/**********RUN_LED* *************/
#define LED_Run(X)  (PORT(PORTB).bit7 = X)
#define LED_STATE   (PORT(PINB).bit7)
/************自定义**********/

#endif