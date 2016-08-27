#ifndef __PROCESSINGACII_H__
#define __PROCESSINGACII_H__

#define RETURN_Q_EMPTY			0
#define RETURN_PROCESSING		1
#define RETURN_OK				2
#define RETURN_RESET			3
#define RETURN_HOMING			4
#define RETURN_WPOS				5
#define RETURN_STATE_END		6

#define FIND		0
#define OK1			1
#define OK2			2
#define OK3			3
#define RESET1		4
#define RESET2		5
#define HOMING1		6
#define HOMING2		7
#define HOMING3		8
#define WPOS1		9
#define WPOS2		10
#define WPOS3		12
#define WPOS4		13
#define WPOS5		14
#define STATE1		15
#define RUN1		16
#define RUN2		17
#define RUN3		18
#define RUN4		19
#define STATE2		20
#define ALARM1		21
#define ALARM2		22
#define ALARM3		23
#define ALARM4		24
#define ALARM5		25

typedef struct FindAciiSt
{
	unsigned char FindAciiState;
	unsigned char FindAciiTemp;
	unsigned char FindAciiCount;
	unsigned char AxisCount; 
	char FindAciiNum[10];
}FINDACIISTC,*pFINDACIISTC;

void FindAciiStClear(unsigned char grblnum);
void Processing_UartReceive_Acii(unsigned char grblnum);

typedef struct _bit_state 
{ 
    unsigned char OK : 1; 
    unsigned char HOMING : 1; 
    unsigned char RESET : 1; 
    unsigned char ALARM : 1; 
    unsigned char RUN : 1; 
    unsigned char IDLE : 1; 
    unsigned char SEND_CMD : 1; 
    unsigned char STATE_END : 1; 
}grblreturnstate,*Pgrblreturnstate; 

typedef struct _bit_alarm 
{ 
    unsigned char HOMING_FAIL : 1; 
    unsigned char HARD_LIMIT : 1; 
    unsigned char SOFT_LIMIT : 1; 
    unsigned char HOLD : 1; 
    unsigned char DOOR : 1; 
    unsigned char bit5 : 1; 
    unsigned char bit6 : 1; 
    unsigned char bit7 : 1; 
}grblreturnalarm,*Pgrblreturnalarm;


#ifdef	GRBL1
extern grblreturnstate GRBL1state;
extern grblreturnalarm GRBL1alarm;
#endif

#ifdef	GRBL2
extern grblreturnstate GRBL2state;
extern grblreturnalarm GRBL2alarm;
#endif

#ifdef 	GRBL3
extern grblreturnstate GRBL3state;
extern grblreturnalarm GRBL3alarm;
#endif
#endif