#include "global.h"

#ifdef	GRBL1
FINDACIISTC FindAcii_1;
grblreturnstate GRBL1state = {0,0,0,0,0,0,0,0};
grblreturnalarm GRBL1alarm = {0,0,0,0,0,0,0,0};
#endif

#ifdef	GRBL2
FINDACIISTC FindAcii_2;
grblreturnstate GRBL2state = {0,0,0,0,0,0,0,0};
grblreturnalarm GRBL2alarm = {0,0,0,0,0,0,0,0};
#endif

#ifdef 	GRBL3
FINDACIISTC FindAcii_3;
grblreturnstate GRBL3state = {0,0,0,0,0,0,0,0};
grblreturnalarm GRBL3alarm = {0,0,0,0,0,0,0,0};
#endif

void FindAciiStClear(unsigned char grblnum)
{
	pFINDACIISTC P = NULL;
	switch(grblnum)
	{
#ifdef	GRBL1
		case GRBL1:
			P = &FindAcii_1;
			break;
#endif

#ifdef  GRBL2
		case GRBL2:
			P = &FindAcii_2;
			break;
#endif

#ifdef  GRBL3
		case GRBL3:
			P = &FindAcii_3;
			break;
#endif
	}

	P->FindAciiState = FIND;
	P->FindAciiTemp = 0;
	P->FindAciiCount = 0;
	P->AxisCount = 0; 
	P->FindAciiNum[0] = '\0';	
}


void Processing_UartReceive_Acii(unsigned char grblnum)	
{
	PHQUEUE P = NULL;
	pFINDACIISTC F = NULL;
	unsigned int *pAxisNum = NULL;
	Pgrblreturnstate Pstate = NULL;
	Pgrblreturnalarm Palarm = NULL;
	switch(grblnum)
	{
#ifdef 	GRBL1
		case GRBL1:
			P = &Uart1QCMDr;
			F = &FindAcii_1;
			pAxisNum = AxisNum;
			Pstate = &GRBL1state;
			Palarm = &GRBL1alarm;
			break;
#endif

#ifdef 	GRBL2
		case GRBL2:
			P = &Uart2QCMDr;
			F = &FindAcii_2;
			pAxisNum = AxisNum+3;
			Pstate = &GRBL2state;
			Palarm = &GRBL2alarm;
			break;
#endif

#ifdef 	GRBL3
		case GRBL3:
			P = &Uart3QCMDr;
			F = &FindAcii_3;
			pAxisNum = AxisNum+6;
			Pstate = &GRBL3state;
			Palarm = &GRBL3alarm;
			break;
#endif	
	}

	if(QueueGetDataCount(P))
	{

		switch(F->FindAciiState)
		{
			case FIND:
				switch(QueueOutput(P))
				{
					case '$'://$H
						F->FindAciiState = HOMING1;

						break;
					case 'o'://ok
						F->FindAciiState = OK1;
						break;
					case 'R'://复位GRBL-Reset
						F->FindAciiState = RESET1;
						break;
					case 'W'://WPos:
						F->FindAciiState = WPOS1;
						break;	
					case '<'://state
						F->FindAciiState = STATE1;
						break;
					case 'A'://ALARM
						F->FindAciiState = ALARM1;
						break;
				}
				break;
			//-------------homing------------------//
			case HOMING1:
				if(QueueOutput(P) == 'H')
					F->FindAciiState = HOMING2;
				else
					F->FindAciiState = FIND;
				break;
			case HOMING2:
				if(QueueOutput(P) == '\n')
				{
					F->FindAciiState = FIND;
					Pstate->HOMING = 1;
				}
				break;
			//-------------------------------//

			//-------------ok------------------//
			case OK1:
				if(QueueOutput(P) == 'k')
					F->FindAciiState = OK2;
				else
					F->FindAciiState = FIND;
				break;
			case OK2:
				if(QueueOutput(P) == '\r')
					F->FindAciiState = OK3;
				else
					F->FindAciiState = FIND;
				break;
			case OK3:
				if(QueueOutput(P) == '\n')
				{
					F->FindAciiState = FIND;
					Pstate->OK = 1;
				}
				break;
			//-------------------------------//

			//-------------reset------------------//
			case RESET1:
				if(QueueOutput(P) == 'e')
					F->FindAciiState = RESET2;
				else
					F->FindAciiState = FIND;
				break;
			case RESET2:
				if(QueueOutput(P) == '\n')
				{
					F->FindAciiState = FIND;
					Pstate->RESET = 1;
				}
				break;
			//-------------------------------//

			//-------------ALARM------------------//
			case ALARM1:
				if(QueueOutput(P) == 'L')
					F->FindAciiState = ALARM2;
				else
					F->FindAciiState = FIND;
				break;
			case ALARM2:
				if(QueueOutput(P) == ':')
					F->FindAciiState = ALARM3;
				break;			
			case ALARM3:
				if(QueueOutput(P) == ' ')
					F->FindAciiState = ALARM4;
				else
					F->FindAciiState = FIND;
				break;
			case ALARM4:
				switch(QueueOutput(P))
				{
					case 'H':
						F->FindAciiState = ALARM5;
						break;
					case 'S':
						Palarm->SOFT_LIMIT = 1;
						F->FindAciiState = FIND;
						break;
					case 'D':
						Palarm->DOOR = 1;
						F->FindAciiState = FIND;
						break;
				}
				break;
			case ALARM5:
				switch(QueueOutput(P))
				{
					case 'a':
						Palarm->HARD_LIMIT = 1;
						break;
					case 'o':
						Palarm->HOMING_FAIL = 1;
						break;
				}
				F->FindAciiState = FIND;
				break;
			//-------------------------------//

			//-------------wpos------------------//
			case WPOS1:
				if(QueueOutput(P) == 'P')
					F->FindAciiState = WPOS2;
				else
					F->FindAciiState = FIND;
				break;
			case WPOS2:
				if(QueueOutput(P) == ':')
					F->FindAciiState = WPOS3;
				break;
			case WPOS3:
				F->FindAciiTemp = QueueOutput(P);
				if(F->FindAciiTemp == ','||F->FindAciiTemp == '>')
				{
					F->FindAciiNum[F->FindAciiCount] = '\0';
					*(pAxisNum+(F->AxisCount++)) = atoi((const char *)F->FindAciiNum);
					F->FindAciiCount = 0;
					if(F->AxisCount >= 3)
					{
						F->AxisCount = 0;
						F->FindAciiState = WPOS4;
					}
				}
				else
					F->FindAciiNum[F->FindAciiCount++] = F->FindAciiTemp;
				break;
			case WPOS4:
				if(QueueOutput(P) == '\r')
					F->FindAciiState = WPOS5;
				break;
			case WPOS5:
				if(QueueOutput(P) == '\n')
				{
					F->FindAciiState = FIND;
					Pstate->STATE_END = 1;
				}
				break;
			//-------------------------------//


			//-------------state------------------//
			case STATE1:
				switch(QueueOutput(P))
				{
					case 'R':
						Pstate->RUN = 1;
						break;
					case 'I':
						Pstate->IDLE = 1;
						break;
					case 'A':
						Pstate->ALARM = 1;
						break;
					case 'H':
						Palarm->HOLD = 1;
						break;

				}
				F->FindAciiState = FIND;
				break;
			//-------------------------------//

		}
	}
}
