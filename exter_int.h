#ifndef	  _EXTER_INT_
#define	  _EXTER_INT_


#define EXTERN_INT0_ON	(EIMSK |= (1 << INT0))
#define EXTERN_INT0_OFF	(EIMSK &= ~(1 << INT0))

#define EXTERN_INT1_ON	(EIMSK |= (1 << INT1))
#define EXTERN_INT1_OFF	(EIMSK &= ~(1 << INT1))

#define EXTERN_INT5_ON	(EIMSK |= (1 << INT5))
#define EXTERN_INT5_OFF	(EIMSK &= ~(1 << INT5))

void INT_int_init();

extern unsigned char Nowstategrbl1;
extern unsigned char Nowstategrbl2;
extern unsigned char Nowstategrbl3;

#define NOWSTATE_STOP 0
#define NOWSTATE_RUN  1
#define NOWSTATE_HOLD 2
#endif