#include "global.h"

unsigned char Nowstategrbl1 = NOWSTATE_STOP;
unsigned char Nowstategrbl2 = NOWSTATE_STOP;
unsigned char Nowstategrbl3 = NOWSTATE_STOP;

void INT_int_init()
{
	//EN	int0 int1 int5 下降沿出发中断
	/***********
	ISCn1	ISCn0	Description
	0			0	The low level of INTn generates an interrupt request.
	0			1	Any logical change on INTn generates an interrupt request
	1			0	The falling edge between two samples of INTn generates an interrupt request.
	1			1	The rising edge between two samples of INTn generates an interrupt request.
	*************/
	PORTD = (1<<PORTD0)|(1<<PORTD1);
	DDRD &= ~((1<<DDD0)|(1<<DDD1));

	PORTE |= (1<<PORTE5);
	DDRE &= ~(1<<PORTE5);

#ifdef	GRBL1
	EICRA |= (1 << ISC01);
	EXTERN_INT0_OFF;
#endif

#ifdef  GRBL2
	EICRA |= (1 << ISC11);
	EXTERN_INT1_OFF;
#endif

#ifdef  GRBL3
	EICRB |= (1 << ISC51);
	EXTERN_INT5_OFF;
#endif

}

#ifdef	GRBL1
ISR(INT0_vect)
{
	Nowstategrbl1 = NOWSTATE_STOP;
	putqueueflag2 = EN_GRBL2;
	putqueueflag3 = EN_GRBL3;
	Nowstategrbl2 = NOWSTATE_RUN;
	Nowstategrbl3 = NOWSTATE_RUN;
}
#endif

#ifdef	GRBL2
ISR(INT1_vect)
{
	Nowstategrbl2 = NOWSTATE_STOP;
	if(Nowstategrbl3 == NOWSTATE_STOP)
		putqueueflag1 = EN_GRBL3;
}
#endif

#ifdef	GRBL3
ISR(INT5_vect)
{
	
	Nowstategrbl3 = NOWSTATE_STOP;
	if(Nowstategrbl2 == NOWSTATE_STOP)
		putqueueflag1 = EN_GRBL3;
}
#endif