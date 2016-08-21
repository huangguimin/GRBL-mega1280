//
//
//----------  ＭＣＸ３１４Ａｓ マニュアル掲載用プログラム -----
//
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <string.h>
#include "uart.h"
#include "Time_Init.h"
#include "Pin_IO.h"
#include "modbus.h"
/*
List of Supported G-Codes in Grbl v0.9 Master:
  - Non-Modal Commands: G4, G10L2, G10L20, G28, G30, G28.1, G30.1, G53, G92, G92.1
  - Motion Modes: G0, G1, G2, G3, G38.2, G38.3, G38.4, G38.5, G80
  - Feed Rate Modes: G93, G94
  - Unit Modes: G20, G21
  - Distance Modes: G90, G91
  - Arc IJK Distance Modes: G91.1
  - Plane Select Modes: G17, G18, G19
  - Tool Length Offset Modes: G43.1, G49
  - Cutter Compensation Modes: G40
  - Coordinate System Modes: G54, G55, G56, G57, G58, G59
  - Control Modes: G61
  - Program Flow: M0, M1, M2, M30*
  - Coolant Control: M7*, M8, M9
  - Spindle Control: M3, M4, M5
  - Valid Non-Command Words: F, I, J, K, L, N, P, R, S, T, X, Y, Z
*/

#define HMI_COMD_REST		0
#define HMI_COMD_MOVE_0		1
#define HMI_COMD_MOVE_1		2
#define HMI_COMD_MOVE_2		3	
#define HMI_COMD_MOVE_3		4
#define HMI_COMD_MOVE_4		5
#define HMI_COMD_MOVE_5		6
#define HMI_COMD_MOVE_6		7	
#define HMI_COMD_MOVE_7		8
#define HMI_COMD_MOVE_8		9
#define HMI_COMD_MOVE_9		10
#define HMI_COMD_MOVE_10	11
#define HMI_COMD_MOVE_11	12

#define COMD_NEG		'-'
#define COMD_POINT		'.'	

#define COMD_GO_ON  	'~' 
#define COMD_HOLD   	'!'
#define COMD_STATE  	'?'
#define COMD_REST_GRBL  0x18

#define COMD_ENDLINE  	'\n'
#define COMD_IS  		'$'
#define COMD_H  		'H'
#define COMD_G  		'G' 
#define COMD_M  		'M'
#define COMD_F  		'F' 
#define COMD_I  		'I' 
#define COMD_J  		'J' 
#define COMD_K  		'K' 
#define COMD_L  		'L' 
#define COMD_N  		'N' 
#define COMD_P  		'P' 
#define COMD_R  		'R' 
#define COMD_S  		'S' 
#define COMD_T  		'T' 
#define COMD_X  		'X' 
#define COMD_Y  		'Y' 
#define COMD_Z  		'Z'	
#define COMD_0  		'0'
#define COMD_1          '1'
#define COMD_2			'2'
#define COMD_3			'3'
#define COMD_4			'4'
#define COMD_5			'5'
#define COMD_6			'6'	
#define COMD_7			'7'
#define COMD_8			'8'
#define COMD_9			'9'		

#define COMD_o  		'o'
#define COMD_k  		'k'

#define X_MOVE_LINE 	0
#define Y_MOVE_LINE 	1
#define Z_MOVE_LINE 	2
#define XY_MOVE_LINE 	3
#define XZ_MOVE_LINE 	4
#define YZ_MOVE_LINE 	5
#define XYZ_MOVE_LINE 	6

#define XY_MOVE_ARC 	7
#define XZ_MOVE_ARC 	8
#define YZ_MOVE_ARC 	9
#define XY_MOVE_ARC_Z 	10
#define XZ_MOVE_ARC_Y 	11
#define YZ_MOVE_ARC_X 	12

#define XY_MOVE_ARC_R 	13
#define XZ_MOVE_ARC_R 	14
#define YZ_MOVE_ARC_R 	15
#define XY_MOVE_ARC_Z_R 	16
#define XZ_MOVE_ARC_Y_R 	17
#define YZ_MOVE_ARC_X_R 	18

#define ABS_BASE	"G90"
#define REL_BASE	"G91"
#define SET_MPOS	"G92"

#define MM_HIGHT	"G00"
#define MM_NORMAL	"G01"
#define MM_ARC_L	"G02"
#define MM_ARC_R	"G03"

#define SYSTEMSTATE_HOMEING	0
#define SYSTEMSTATE_RESET	1
#define SYSTEMSTATE_HOLD	2
#define SYSTEMSTATE_GOON    3
#define SYSTEMSTATE_IDLE    4


#define GRBL1	1
#define GRBL2	2
#define GRBL3	4

unsigned char SystemState = SYSTEMSTATE_IDLE;

void Put_NumToStrQueue(PHQUEUE Q,int num)
{
	char st[7];
	unsigned char i;
	itoa(num, st, 10);
	for(i = 0; st[i] != '\0'; i++)
		QueueInput(Q,st[i]);
}

typedef struct sendcommdbuff
{
	unsigned char state;
	char commstr[100];
	unsigned char bytecount;
}SCBuff,*pSCBuff;

SCBuff  XYZsendbuff1;
SCBuff  XYZsendbuff2;

void SCBuffClear(pSCBuff P)
{
	P->state = 0;
	P->commstr[0] = '\0';
	P->bytecount = 0;	
}

unsigned char Put_AciiToStrQueue(PHQUEUE Q,pSCBuff P)
{
	for(; P->commstr[P->bytecount] != '\0'; P->bytecount++)
	{
		if(QueueInput(Q,P->commstr[P->bytecount]))
			return 1;
	}
	P->bytecount = 0;
	return 0;
}

unsigned char Set_XYZ_WPos(unsigned char grblnum,const char *Xnum,const char *Ynum,const char *Znum)
{	
	PHQUEUE P = NULL;
	pSCBuff PXYZ = NULL;
	switch(grblnum)
	{
		case GRBL1:
			P = &Uart1QCMDs;
			PXYZ = &XYZsendbuff1;
			break;
		case GRBL2:
			P = &Uart2QCMDs;
			PXYZ = &XYZsendbuff2;
			break;
		case GRBL3:
			//P = &Uart3QCMDs;
			//PXYZ = &XYZsendbuff3;
			break;
	}

	switch(PXYZ->state)
	{
		case 0:
			SCBuffClear(PXYZ);
			strcat(PXYZ->commstr,SET_MPOS);
			if(strcmp(Xnum, "*"))
			{
				strcat(PXYZ->commstr,"X");
				strcat(PXYZ->commstr,Xnum);
			}
			if(strcmp(Ynum, "*"))
			{
				
				strcat(PXYZ->commstr,"Y");
				strcat(PXYZ->commstr,Ynum);
			}
			if(strcmp(Znum, "*"))
			{
				strcat(PXYZ->commstr,"Z");
				strcat(PXYZ->commstr,Znum);
			}
			strcat(PXYZ->commstr,"\n");
			PXYZ->state = 1;
			break;
		case 1:
			if(!Put_AciiToStrQueue(P,PXYZ))
			{
				PXYZ->state = 0;
				return 0;
			}	
			break;
	}
	return 1;
}

unsigned char XYZ_Move_Funct(unsigned char grblnum,unsigned char modle,const char * movemodle,\
								const char * Xnum,const char * Ynum,const char * Znum,		\
								const char * Inum,const char * Jnum,const char * Knum,		\
								const char * Rnum,const char * speed,const char * mbase)
{
	PHQUEUE P = NULL;
	pSCBuff PXYZ = NULL;
	switch(grblnum)
	{
		case GRBL1:
			P = &Uart1QCMDs;
			PXYZ = &XYZsendbuff1;
			break;
		case GRBL2:
			P = &Uart2QCMDs;
			PXYZ = &XYZsendbuff2;
			break;
		case GRBL3:
			//P = &Uart3QCMDs;
			//PXYZ = &XYZsendbuff3;
			break;
	}

	switch(PXYZ->state)
	{
		case 0:
			SCBuffClear(PXYZ);
			strcat(PXYZ->commstr,movemodle);
			strcat(PXYZ->commstr,mbase);
			switch(modle)
			{
				case X_MOVE_LINE:
				case XY_MOVE_LINE:
				case XY_MOVE_ARC:
				case XY_MOVE_ARC_R:
				case XZ_MOVE_LINE:
				case XZ_MOVE_ARC:
				case XZ_MOVE_ARC_R:	
				case XYZ_MOVE_LINE:
				case XY_MOVE_ARC_Z:
				case XZ_MOVE_ARC_Y:
				case YZ_MOVE_ARC_X:
				case XY_MOVE_ARC_Z_R:
				case XZ_MOVE_ARC_Y_R:
				case YZ_MOVE_ARC_X_R: 
					strcat(PXYZ->commstr,"X");
					strcat(PXYZ->commstr,Xnum);
				case Y_MOVE_LINE:
				case YZ_MOVE_ARC:
				case YZ_MOVE_ARC_R:
				case YZ_MOVE_LINE:
					switch(modle)
					{
						case X_MOVE_LINE:
						case XZ_MOVE_LINE:
						case XZ_MOVE_ARC:
						case XZ_MOVE_ARC_R:
							break;
						default:
							strcat(PXYZ->commstr,"Y");
							strcat(PXYZ->commstr,Ynum);
							break;
					}
				case Z_MOVE_LINE:
					switch(modle)
					{
						case X_MOVE_LINE:
						case XY_MOVE_LINE:
						case XY_MOVE_ARC:
						case XY_MOVE_ARC_R:
						case Y_MOVE_LINE:
							break;
						default:
							strcat(PXYZ->commstr,"Z");
							strcat(PXYZ->commstr,Znum);
							break;
					}
					break;
			}
		
			switch(modle)
			{
				case XY_MOVE_ARC:
				case XZ_MOVE_ARC:
				case XY_MOVE_ARC_Z:
				case XZ_MOVE_ARC_Y:
					strcat(PXYZ->commstr,"I");
					strcat(PXYZ->commstr,Inum);
				case YZ_MOVE_ARC:
				case YZ_MOVE_ARC_X:
					switch(modle)
					{
						case YZ_MOVE_ARC:
						case YZ_MOVE_ARC_X:
						case XY_MOVE_ARC:
						case XY_MOVE_ARC_Z:
							strcat(PXYZ->commstr,"J");
							strcat(PXYZ->commstr,Jnum);
						case XZ_MOVE_ARC:
						case XZ_MOVE_ARC_Y:
							switch(modle)
							{
								case XY_MOVE_ARC:
								case XY_MOVE_ARC_Z:
									break;
								default:
									strcat(PXYZ->commstr,"K");
									strcat(PXYZ->commstr,Knum);
									break;
							}
							break;
					}
					break;
				case XY_MOVE_ARC_R :
				case XZ_MOVE_ARC_R :
				case YZ_MOVE_ARC_R :
				case XY_MOVE_ARC_Z_R :
				case XZ_MOVE_ARC_Y_R :
				case YZ_MOVE_ARC_X_R :
					strcat(PXYZ->commstr,"R");
					strcat(PXYZ->commstr,Rnum);
					break;
				default:
					break;
			}
			if(strcmp(movemodle, MM_HIGHT))
			{
				strcat(PXYZ->commstr,"F");
				strcat(PXYZ->commstr,speed);
			}
			strcat(PXYZ->commstr,"\n");
			PXYZ->state = 1;
			break;
		case 1:
			if(!Put_AciiToStrQueue(P,PXYZ))
			{
				PXYZ->state = 0;
				return 0;
			}
			break;
	}
	return 1;
}

void Send_RunTime_CMD(unsigned char grblnum,unsigned char CMD)
{
	switch(grblnum)
	{
		case GRBL1:
			UART1_INT_EMP_Start;
			SnedRunTimeCMD1 = CMD;
			//UDR2 = CMD;
			break;
		case GRBL2:
			UART2_INT_EMP_Start;
			SnedRunTimeCMD2 = CMD;
			break;
		case GRBL3:
			//UART3_INT_TX_Start;
			break;
		case GRBL1|GRBL2:
			UART1_INT_TX_Start;
			UART2_INT_TX_Start;
			break;
		case GRBL1|GRBL3:
			UART1_INT_TX_Start;
			//UART3_INT_TX_Start;
			break;
		case GRBL2|GRBL3:
			UART2_INT_TX_Start;
			//UART3_INT_TX_Start;
			break;
		case GRBL1|GRBL2|GRBL3:
			UART1_INT_TX_Start;
			UART2_INT_TX_Start;
			//UART3_INT_TX_Start;
			break;
		default:
			break;
	}
}

/*
unsigned char Auto_Processing(PHQUEUE Q,unsigned char witchstate)
{
	switch(witchstate)
}
*/
#define RETURN_Q_EMPTY			0
#define RETURN_PROCESSING		1
#define RETURN_OK				2
#define RETURN_RESET			3
#define RETURN_HOMING			4
#define RETURN_WPOS				5
#define RETURN_WPOS_END			6

typedef struct FindAciiSt
{
	unsigned char FindAciiState;
	unsigned char FindAciiTemp;
	unsigned char FindAciiCount;
	unsigned char AxisCount; 
	char FindAciiNum[10];
}FINDACIISTC,*pFINDACIISTC;

FINDACIISTC FindAcii_1;
FINDACIISTC FindAcii_2;

void FindAciiStClear(pFINDACIISTC P)
{
	P->FindAciiState = 0;
	P->FindAciiTemp = 0;
	P->FindAciiCount = 0;
	P->AxisCount = 0; 
	P->FindAciiNum[0] = '\0';	
}

unsigned char Processing_UartReceive_Acii(unsigned char grblnum)	
{
	PHQUEUE P = NULL;
	pFINDACIISTC F = NULL;

	switch(grblnum)
	{
		case GRBL1:
			P = &Uart1QCMDr;
			F = &FindAcii_1;
			break;
		case GRBL2:
			P = &Uart2QCMDr;
			F = &FindAcii_2;
			break;
		case GRBL3:
			//P = &Uart3QCMDs;
			//PXYZ = &XYZsendbuff3;
			break;
	}

	if(QueueGetDataCount(P))
	{

		switch(F->FindAciiState)
		{
			case 0:
				switch(QueueOutput(P))
				{
					case '$'://$H
						F->FindAciiState = 1;

						break;
					case 'o'://ok
						F->FindAciiState = 2;
						break;
					case 'R'://复位GRBL-Reset
						F->FindAciiState = 4;
						break;
					/*case 'W'://WPos:
						F->FindAciiState = 6;
						break;
						*/
					case '>':
						F->FindAciiState = 10;
						break;
				}
				break;
			case 1:
				if(QueueOutput(P) == 'H')
					F->FindAciiState = 11;
				else
					F->FindAciiState = 0;
				break;
			case 11:
				if(QueueOutput(P) == '\n')
				{
					F->FindAciiState = 0;
					return RETURN_HOMING;
				}
				break;

			case 2:
				if(QueueOutput(P) == 'k')
					F->FindAciiState = 12;
				else
					F->FindAciiState = 0;
				break;
			case 12:
				if(QueueOutput(P) == '\r')
					F->FindAciiState = 22;
				else
					F->FindAciiState = 0;
				break;
			case 22:
				if(QueueOutput(P) == '\n')
				{
					F->FindAciiState = 0;
					return RETURN_OK;
				}
				break;

			case 4:
				if(QueueOutput(P) == 'e')
					F->FindAciiState = 14;
				else
					F->FindAciiState = 0;
				break;
			case 14:
				if(QueueOutput(P) == '\n')
				{
					F->FindAciiState = 0;
					return RETURN_RESET;
				}
				break;

			case 10:
				if(QueueOutput(P) == '\r')
					F->FindAciiState = 20;
				else
					F->FindAciiState = 0;
				break;
			case 20:
				if(QueueOutput(P) == '\n')
				{
					F->FindAciiState = 0;
					return RETURN_WPOS_END;
				}
				break;
				
			case 6:
				if(QueueOutput(P) == 'P')
					F->FindAciiState = 7;
				else
					F->FindAciiState = 0;
				break;
			case 7:
				if(QueueOutput(P) == ':')
					F->FindAciiState = 8;
				break;
			case 8:
				F->FindAciiTemp = QueueOutput(P);
				if(F->FindAciiTemp == ',')
				{
					F->FindAciiNum[F->FindAciiCount] = '\0';
					AxisNum[F->AxisCount++] = atof((const char *)F->FindAciiNum);
					F->FindAciiCount = 0;
					if(F->AxisCount >= 3)
					{
						F->AxisCount = 0;
						F->FindAciiState = 9;
						return RETURN_WPOS;
					}
				}
				else
					F->FindAciiNum[F->FindAciiCount++] = F->FindAciiTemp;
				break;
			case 9:
				if(QueueOutput(P) == '>')
				{
					F->FindAciiState = 0;
					return RETURN_WPOS_END;
				}
				break;
		}
		return RETURN_PROCESSING;
	}
	else
		return RETURN_Q_EMPTY;
}

void Init_Data_Buff(unsigned char grblnum)
{
	PHQUEUE P1 = NULL,P2 = NULL;
	pSCBuff PXYZ = NULL;
	switch(grblnum)
	{
		case GRBL1:
			P1 = &Uart1QCMDr;
			P2 = &Uart1QCMDs;
			PXYZ = &XYZsendbuff1;
			break;
		case GRBL2:
			P1 = &Uart2QCMDr;
			P2 = &Uart2QCMDs;
			PXYZ = &XYZsendbuff2;
			break;
		case GRBL3:
			//P1 = &Uart3QCMDs;
			//P2 = &Uart3QCMDs;
			//PXYZ = &XYZsendbuff3;
			break;
	}
	QueueClear(P1);
	QueueClear(P2);
	SCBuffClear(PXYZ);
}

void Grbl_SendBuff_Start(unsigned char grblnum, unsigned char date)
{
	switch(grblnum)
	{
		case GRBL1:
			USART1_Send_word(date);	
			UART1_INT_TX_Start;
			break;
		case GRBL2:
			USART2_Send_word(date);
			UART2_INT_TX_Start;
			break;
		case GRBL3:
			//USART3_Send_word(date);
			break;
	}
}

unsigned char count = 0,count2 = 0;
int main()
{
	unsigned char HmiCommState = 0;
	unsigned char HmiCommState2 = 0;
	long numcount1 = 0,numcount2 = 0;
	unsigned char readgrblstate1 = 0,readgrblstate2 = 0;
	PORTB = 0xFF;
	DDRB = 0xFF;
	
	//Time1_init();
	Modbus_Int();
	USART1_initial();
	USART2_initial();
	HmiCommState = HMI_COMD_MOVE_6;
	HmiCommState2 = HMI_COMD_MOVE_6;

	FindAciiStClear(&FindAcii_1);
	FindAciiStClear(&FindAcii_2);
	sei();
	//_delay_ms(1000);
	while(1)
	{
	
		switch(Processing_UartReceive_Acii(GRBL1))
		{
			
			case RETURN_OK		 	:
				if(QueueGetDataCount(&Uart1QCMDs))
					Grbl_SendBuff_Start(GRBL1, QueueOutput(&Uart1QCMDs));
				break;
			case RETURN_RESET	 	:
				Send_RunTime_CMD(GRBL1,COMD_REST_GRBL);
				break;
			case RETURN_HOMING	 	:
				HmiCommState = HMI_COMD_REST;
				Init_Data_Buff(GRBL1);
				FindAciiStClear(&FindAcii_1);
				count = 0;
				break;
			case RETURN_WPOS		:
				break;
			case RETURN_Q_EMPTY	 	:
				break;
			case RETURN_PROCESSING 	:
				break;
			case RETURN_WPOS_END:
				//Send_RunTime_CMD(GRBL1,'?');
				readgrblstate1 = 1;
				break;
		}
		
		if(readgrblstate1&&numcount1>1000)
		{
				readgrblstate1 = 0;
				numcount1 = 0;
				Send_RunTime_CMD(GRBL1,'?');
		}
		else
			numcount1++;


		switch(HmiCommState)
		{
			case HMI_COMD_REST:
				QueueInput(&Uart1QCMDs,COMD_IS);
				QueueInput(&Uart1QCMDs,COMD_X);
				QueueInput(&Uart1QCMDs,COMD_ENDLINE);
				Grbl_SendBuff_Start(GRBL1, QueueOutput(&Uart1QCMDs));
				HmiCommState = HMI_COMD_MOVE_0;
		    	break;
			case HMI_COMD_MOVE_0:
				if(QueueGetDataCount(&Uart1QCMDs))
					break;
				if(!Set_XYZ_WPos(GRBL1,"0","0","0"))
				{
					HmiCommState = HMI_COMD_MOVE_11;
					Grbl_SendBuff_Start(GRBL1, QueueOutput(&Uart1QCMDs));
				}
				break;
			case HMI_COMD_MOVE_11:
				if(QueueGetDataCount(&Uart1QCMDs))
					break;
				Send_RunTime_CMD(GRBL1,'?');
				HmiCommState = HMI_COMD_MOVE_1;
		    	break;
			case HMI_COMD_MOVE_1:
				if(!XYZ_Move_Funct(GRBL1,X_MOVE_LINE,MM_NORMAL,"200","100","0","0","0","0","0","4000",REL_BASE))
					HmiCommState = HMI_COMD_MOVE_2;
		    	break;
			case HMI_COMD_MOVE_2:
				if(!XYZ_Move_Funct(GRBL1,Y_MOVE_LINE,MM_NORMAL,"100","100","0","0","0","0","0","4000",REL_BASE))
					HmiCommState = HMI_COMD_MOVE_3;
		    	break;
			case HMI_COMD_MOVE_3:
				if(!XYZ_Move_Funct(GRBL1,X_MOVE_LINE,MM_NORMAL,"-200","100","0","0","0","0","0","4000",REL_BASE))
					HmiCommState = HMI_COMD_MOVE_4;
		    	break;
			case HMI_COMD_MOVE_4:
				if(!XYZ_Move_Funct(GRBL1,Y_MOVE_LINE,MM_NORMAL,"100","-100","0","0","0","0","0","4000",REL_BASE))				
					HmiCommState = HMI_COMD_MOVE_7;
		    	break;
		    case HMI_COMD_MOVE_7: 
		    	if(!XYZ_Move_Funct(GRBL1,XY_MOVE_ARC,MM_ARC_L,"200","0","0","100","0","0","0","4000",REL_BASE))
		    		HmiCommState = HMI_COMD_MOVE_8;
		    	break;
		    case HMI_COMD_MOVE_8: 
		    	if(!XYZ_Move_Funct(GRBL1,XY_MOVE_ARC,MM_ARC_R,"-200","0","0","-100","0","0","0","4000",REL_BASE))
		    		HmiCommState = HMI_COMD_MOVE_9;
		    	break;
		    case HMI_COMD_MOVE_9: 
		    	if(!XYZ_Move_Funct(GRBL1,XY_MOVE_ARC_R,MM_ARC_L,"200","0","0","0","0","0","100","4000",REL_BASE))
		    		HmiCommState = HMI_COMD_MOVE_10;
		    	break;
		    case HMI_COMD_MOVE_10: 
		    	if(!XYZ_Move_Funct(GRBL1,XY_MOVE_ARC_R,MM_ARC_R,"-200","0","0","0","0","0","100","4000",REL_BASE))
		    		HmiCommState = HMI_COMD_MOVE_5;
		    	break;

			case HMI_COMD_MOVE_5:
				if(count++ >= 5)
				{
					HmiCommState = HMI_COMD_MOVE_6;
					count = 0;
				}
				else
					HmiCommState = HMI_COMD_MOVE_1;
		    	break;
		    case HMI_COMD_MOVE_6:
		    	break;
	    }

	    switch(Processing_UartReceive_Acii(GRBL2))
		{
			case RETURN_OK		 	:
				if(QueueGetDataCount(&Uart2QCMDs))
					Grbl_SendBuff_Start(GRBL2, QueueOutput(&Uart2QCMDs));
				break;
			case RETURN_RESET	 	:
				Send_RunTime_CMD(GRBL2,COMD_REST_GRBL);
				break;
			case RETURN_HOMING	 	:
				HmiCommState2 = HMI_COMD_REST;
				Init_Data_Buff(GRBL2);
				FindAciiStClear(&FindAcii_2);
				count2 = 0;
				break;
			case RETURN_WPOS		:
				break;
			case RETURN_Q_EMPTY	 	:
				break;
			case RETURN_PROCESSING 	:
				break;
			case RETURN_WPOS_END:
				//Send_RunTime_CMD(GRBL2,'?');
				//HmiCommState2 = HMI_COMD_MOVE_1;
				readgrblstate2 = 2;
				break;
		}
		
		if(readgrblstate2&&numcount2>1000)
		{
				readgrblstate2 = 0;
				numcount2 = 0;
				Send_RunTime_CMD(GRBL2,'?');
				//Send_RunTime_CMD(GRBL1,'?');
		}
		else
			numcount2++;
		

		switch(HmiCommState2)
		{
			case HMI_COMD_REST:
				QueueInput(&Uart2QCMDs,COMD_IS);
				QueueInput(&Uart2QCMDs,COMD_H);
				QueueInput(&Uart2QCMDs,COMD_ENDLINE);
				Grbl_SendBuff_Start(GRBL2, QueueOutput(&Uart2QCMDs));
				HmiCommState2 = HMI_COMD_MOVE_0;
		    	break;
			case HMI_COMD_MOVE_0:
				//if(QueueGetDataCount(&Uart2QCMDs))
				//	break;
				if(!Set_XYZ_WPos(GRBL2,"0","0","0"))
				{	
					HmiCommState2 = HMI_COMD_MOVE_11;
					Grbl_SendBuff_Start(GRBL2, QueueOutput(&Uart2QCMDs));
				}
				break;
			case HMI_COMD_MOVE_11:
				//if(QueueGetDataCount(&Uart2QCMDs))
				//	break;
				Send_RunTime_CMD(GRBL2,'?');
				//while(1)Modbus_Processing();
				HmiCommState2 = HMI_COMD_MOVE_1;
		    	break;
			case HMI_COMD_MOVE_1:
				if(!XYZ_Move_Funct(GRBL2,X_MOVE_LINE,MM_NORMAL,"200","100","0","0","0","0","0","4000",REL_BASE))
					HmiCommState2 = HMI_COMD_MOVE_2;
		    	break;
			case HMI_COMD_MOVE_2:
				if(!XYZ_Move_Funct(GRBL2,Y_MOVE_LINE,MM_NORMAL,"100","100","0","0","0","0","0","4000",REL_BASE))
					HmiCommState2 = HMI_COMD_MOVE_3;
		    	break;
			case HMI_COMD_MOVE_3:
				if(!XYZ_Move_Funct(GRBL2,X_MOVE_LINE,MM_NORMAL,"-200","100","0","0","0","0","0","4000",REL_BASE))
					HmiCommState2 = HMI_COMD_MOVE_4;
		    	break;
			case HMI_COMD_MOVE_4:
				if(!XYZ_Move_Funct(GRBL2,Y_MOVE_LINE,MM_NORMAL,"100","-100","0","0","0","0","0","4000",REL_BASE))				
					HmiCommState2 = HMI_COMD_MOVE_7;
		    	break;
		    case HMI_COMD_MOVE_7: 
		    	if(!XYZ_Move_Funct(GRBL2,XY_MOVE_ARC,MM_ARC_L,"200","0","0","100","0","0","0","4000",REL_BASE))
		    		HmiCommState2 = HMI_COMD_MOVE_8;
		    	break;
		    case HMI_COMD_MOVE_8: 
		    	if(!XYZ_Move_Funct(GRBL2,XY_MOVE_ARC,MM_ARC_R,"-200","0","0","-100","0","0","0","4000",REL_BASE))
		    		HmiCommState2 = HMI_COMD_MOVE_9;
		    	break;
		    case HMI_COMD_MOVE_9: 
		    	if(!XYZ_Move_Funct(GRBL2,XY_MOVE_ARC_R,MM_ARC_L,"200","0","0","0","0","0","100","4000",REL_BASE))
		    		HmiCommState2 = HMI_COMD_MOVE_10;
		    	break;
		    case HMI_COMD_MOVE_10: 
		    	if(!XYZ_Move_Funct(GRBL2,XY_MOVE_ARC_R,MM_ARC_R,"-200","0","0","0","0","0","100","4000",REL_BASE))
		    		HmiCommState2 = HMI_COMD_MOVE_5;
		    	break;

			case HMI_COMD_MOVE_5:
				if(count2++ >= 5)
				{
					HmiCommState2 = HMI_COMD_MOVE_6;
					count2 = 0;
				}
				else
					HmiCommState2 = HMI_COMD_MOVE_1;
		    	break;
		    case HMI_COMD_MOVE_6:
		    	break;
	    }
	    //_delay_ms(100);
	    LED_Run(~LED_STATE);
	    //Send_RunTime_CMD(GRBL1|GRBL2,'?');
	   // Modbus_Processing();
	}
}
