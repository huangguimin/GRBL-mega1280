#include "global.h"

#ifdef 	GRBL1
SCBuff  XYZsendbuff1;
#endif

#ifdef 	GRBL2
SCBuff  XYZsendbuff2;
#endif

#ifdef 	GRBL3
SCBuff  XYZsendbuff3;
#endif

Axis_WordData  AxisWordDatas[10];

unsigned char putqueueflag1 = ENO_GRBL1,putqueueflag2 = ENO_GRBL2,putqueueflag3 = ENO_GRBL3;

void AxisWordDatasClear()
{
	memset(AxisWordDatas,0,sizeof(AxisWordDatas));
}

void Put_NumToStrQueue(PHQUEUE Q,int num)
{
	char st[7];
	unsigned char i;
	itoa(num, st, 10);
	for(i = 0; st[i] != '\0'; i++)
		QueueInput(Q,st[i]);
}

unsigned char Put_CMDToStrQueue(unsigned char grblnum,const char * Pacii)
{
	static unsigned char i1 = 0;
	static unsigned char i2 = 0;
	static unsigned char i3 = 0;
	PHQUEUE Q = NULL;
	unsigned char * P = NULL;
	switch(grblnum)
	{
#ifdef 	GRBL1
		case GRBL1:
			Q = &Uart1QCMDs;
			P = &i1;
			break;
#endif

#ifdef	GRBL2
		case GRBL2:
			Q = &Uart2QCMDs;
			P = &i2;
			break;
#endif

#ifdef	GRBL3
		case GRBL3:
			Q = &Uart3QCMDs;
			P = &i3;
			break;
#endif

	}
/*
	do
	{
		if(QueueInput(Q,Pacii[*P]))
			return 1;
	}while(Pacii[(*P)++] != '\0');*/
	
	for(; Pacii[*P] != '\0'; (*P)++)
	{
		if(QueueInput(Q,Pacii[*P]))
			return 1;
	}
	*P = 0;
	return 0;
}

void SCBuffClear(pSCBuff P)
{
	P->state = 0;
	P->commstr[0] = '\0';
	P->bytecount = 0;	
}

void Init_Data_Buff(unsigned char grblnum)
{
	PHQUEUE P1 = NULL,P2 = NULL;
	pSCBuff PXYZ = NULL;
	switch(grblnum)
	{
#ifdef 	GRBL1
		case GRBL1:
			P1 = &Uart1QCMDr;
			P2 = &Uart1QCMDs;
			PXYZ = &XYZsendbuff1;
			break;
#endif

#ifdef	GRBL2
		case GRBL2:
			P1 = &Uart2QCMDr;
			P2 = &Uart2QCMDs;
			PXYZ = &XYZsendbuff2;
			break;
#endif

#ifdef	GRBL3
		case GRBL3:
			P1 = &Uart3QCMDs;
			P2 = &Uart3QCMDs;
			PXYZ = &XYZsendbuff3;
			break;
#endif

	}
	QueueClear(P1);
	QueueClear(P2);
	SCBuffClear(PXYZ);
}

unsigned char Put_AciiToStrQueue(PHQUEUE Q,pSCBuff P)
{

	do
	{
		if(QueueInput(Q,P->commstr[P->bytecount]))
			return 1;
	}while(P->commstr[P->bytecount++] != '\0');
/*
	for(; P->commstr[P->bytecount] != '\0'; P->bytecount++)
	{
		if(QueueInput(Q,P->commstr[P->bytecount]))
			return 1;
	}*/
	P->bytecount = 0;
	return 0;
}


unsigned char Put_SetXYZWposToStrQueue(unsigned char grblnum,const char *Xnum,const char *Ynum,const char *Znum)
{	
	PHQUEUE P = NULL;
	pSCBuff PXYZ = NULL;
	switch(grblnum)
	{
#ifdef 	GRBL1
		case GRBL1:
			P = &Uart1QCMDs;
			PXYZ = &XYZsendbuff1;
			break;
#endif

#ifdef 	GRBL2
		case GRBL2:
			P = &Uart2QCMDs;
			PXYZ = &XYZsendbuff2;
			break;
#endif

#ifdef	GRBL3
		case GRBL3:
			P = &Uart3QCMDs;
			PXYZ = &XYZsendbuff3;
			break;
#endif
	}

	switch(PXYZ->state)
	{
		case 0:
			SCBuffClear(PXYZ);
			strcat(PXYZ->commstr,ACII_SET_MPOS);
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

unsigned char Put_XYZMoveToStrQueue(unsigned char grblnum,unsigned char movemodle,\
								const char * Xnum,const char * Ynum,const char * Znum,		\
								const char * Inum,const char * Jnum,const char * Knum,		\
								const char * Rnum,const char * speed,unsigned char mbase)
{
	PHQUEUE P = NULL;
	pSCBuff PXYZ = NULL;
	switch(grblnum)
	{
#ifdef GRBL1
		case GRBL1:
			P = &Uart1QCMDs;
			PXYZ = &XYZsendbuff1;
			break;
#endif

#ifdef	GRBL2
		case GRBL2:
			P = &Uart2QCMDs;
			PXYZ = &XYZsendbuff2;
			break;
#endif

#ifdef	GRBL3
		case GRBL3:
			P = &Uart3QCMDs;
			PXYZ = &XYZsendbuff3;
			break;
#endif
	}

	switch(PXYZ->state)
	{
		case 0:
			SCBuffClear(PXYZ);
			switch(movemodle)
			{
				case X_MOVE_LINE_H :
				case Y_MOVE_LINE_H :
				case Z_MOVE_LINE_H :
				case XY_MOVE_LINE_H :
				case XZ_MOVE_LINE_H :
				case YZ_MOVE_LINE_H :
				case XYZ_MOVE_LINE_H :		
					strcat(PXYZ->commstr,ACII_HIGHT);
					break;
				case X_MOVE_LINE :
				case Y_MOVE_LINE :
				case Z_MOVE_LINE :
				case XY_MOVE_LINE :
				case XZ_MOVE_LINE :
				case YZ_MOVE_LINE :
				case XYZ_MOVE_LINE :	
					strcat(PXYZ->commstr,ACII_LINE);
					break;
				case XY_MOVE_ARC_L : 	
				case XZ_MOVE_ARC_L : 	
				case YZ_MOVE_ARC_L : 	
				case XY_MOVE_ARC_Z_L : 	
				case XZ_MOVE_ARC_Y_L : 	
				case YZ_MOVE_ARC_X_L : 	
					strcat(PXYZ->commstr,ACII_ARC_L);
					break;
				case XY_MOVE_ARC_R : 	
				case XZ_MOVE_ARC_R : 	
				case YZ_MOVE_ARC_R : 	
				case XY_MOVE_ARC_Z_R : 	
				case XZ_MOVE_ARC_Y_R : 	
				case YZ_MOVE_ARC_X_R : 
					strcat(PXYZ->commstr,ACII_ARC_R);
					break;
			}

			if(mbase == ABS_BASE)
				strcat(PXYZ->commstr,ACII_ABS_BASE);
			else
				strcat(PXYZ->commstr,ACII_REL_BASE);
			switch(movemodle)
			{
				case X_MOVE_LINE:
				case XY_MOVE_LINE:
				case XY_MOVE_ARC_L:
				case XY_MOVE_ARC_R_L:
				case XZ_MOVE_LINE:
				case XZ_MOVE_ARC_L:
				case XZ_MOVE_ARC_R_L:	
				case XYZ_MOVE_LINE:
				case XY_MOVE_ARC_Z_L:
				case XZ_MOVE_ARC_Y_L:
				case YZ_MOVE_ARC_X_L:
				case XY_MOVE_ARC_Z_R_L:
				case XZ_MOVE_ARC_Y_R_L:
				case YZ_MOVE_ARC_X_R_L:

				case X_MOVE_LINE_H:
				case XY_MOVE_LINE_H:
				case XY_MOVE_ARC_R:
				case XY_MOVE_ARC_R_R:
				case XZ_MOVE_LINE_H:
				case XZ_MOVE_ARC_R:
				case XZ_MOVE_ARC_R_R:	
				case XYZ_MOVE_LINE_H:
				case XY_MOVE_ARC_Z_R:
				case XZ_MOVE_ARC_Y_R:
				case YZ_MOVE_ARC_X_R:
				case XY_MOVE_ARC_Z_R_R:
				case XZ_MOVE_ARC_Y_R_R:
				case YZ_MOVE_ARC_X_R_R: 
					strcat(PXYZ->commstr,"X");
					strcat(PXYZ->commstr,Xnum);
				case Y_MOVE_LINE:
				case YZ_MOVE_ARC_L:
				case YZ_MOVE_ARC_R_L:
				case YZ_MOVE_LINE:

				case Y_MOVE_LINE_H:
				case YZ_MOVE_ARC_R:
				case YZ_MOVE_ARC_R_R:
				case YZ_MOVE_LINE_H:
					switch(movemodle)
					{
						case X_MOVE_LINE:
						case XZ_MOVE_LINE:
						case XZ_MOVE_ARC_L:
						case XZ_MOVE_ARC_R_L:

						case X_MOVE_LINE_H:
						case XZ_MOVE_LINE_H:
						case XZ_MOVE_ARC_R:
						case XZ_MOVE_ARC_R_R:
							break;
						default:
							strcat(PXYZ->commstr,"Y");
							strcat(PXYZ->commstr,Ynum);
							break;
					}
				case Z_MOVE_LINE:
					switch(movemodle)
					{
						case X_MOVE_LINE:
						case XY_MOVE_LINE:
						case XY_MOVE_ARC_L:
						case XY_MOVE_ARC_R_L:
						case Y_MOVE_LINE:

						case X_MOVE_LINE_H:
						case XY_MOVE_LINE_H:
						case XY_MOVE_ARC_R:
						case XY_MOVE_ARC_R_R:
						case Y_MOVE_LINE_H:
							break;
						default:
							strcat(PXYZ->commstr,"Z");
							strcat(PXYZ->commstr,Znum);
							break;
					}
					break;
			}
		
			switch(movemodle)
			{
				case XY_MOVE_ARC_L:
				case XZ_MOVE_ARC_L:
				case XY_MOVE_ARC_Z_L:
				case XZ_MOVE_ARC_Y_L:

				case XY_MOVE_ARC_R:
				case XZ_MOVE_ARC_R:
				case XY_MOVE_ARC_Z_R:
				case XZ_MOVE_ARC_Y_R:
					strcat(PXYZ->commstr,"I");
					strcat(PXYZ->commstr,Inum);
				case YZ_MOVE_ARC_L:
				case YZ_MOVE_ARC_X_L:

				case YZ_MOVE_ARC_R:
				case YZ_MOVE_ARC_X_R:
					switch(movemodle)
					{
						case YZ_MOVE_ARC_L:
						case YZ_MOVE_ARC_X_L:
						case XY_MOVE_ARC_L:
						case XY_MOVE_ARC_Z_L:

						case YZ_MOVE_ARC_R:
						case YZ_MOVE_ARC_X_R:
						case XY_MOVE_ARC_R:
						case XY_MOVE_ARC_Z_R:
							strcat(PXYZ->commstr,"J");
							strcat(PXYZ->commstr,Jnum);
						case XZ_MOVE_ARC_L:
						case XZ_MOVE_ARC_Y_L:

						case XZ_MOVE_ARC_R:
						case XZ_MOVE_ARC_Y_R:
							switch(movemodle)
							{
								case XY_MOVE_ARC_L:
								case XY_MOVE_ARC_Z_L:

								case XY_MOVE_ARC_R:
								case XY_MOVE_ARC_Z_R:
									break;
								default:
									strcat(PXYZ->commstr,"K");
									strcat(PXYZ->commstr,Knum);
									break;
							}
							break;
					}
					break;
				case XY_MOVE_ARC_R_L :
				case XZ_MOVE_ARC_R_L :
				case YZ_MOVE_ARC_R_L :
				case XY_MOVE_ARC_Z_R_L :
				case XZ_MOVE_ARC_Y_R_L :
				case YZ_MOVE_ARC_X_R_L :

				case XY_MOVE_ARC_R_R :
				case XZ_MOVE_ARC_R_R :
				case YZ_MOVE_ARC_R_R :
				case XY_MOVE_ARC_Z_R_R :
				case XZ_MOVE_ARC_Y_R_R :
				case YZ_MOVE_ARC_X_R_R :
					strcat(PXYZ->commstr,"R");
					strcat(PXYZ->commstr,Rnum);
					break;
				default:
					break;
			}
			
			strcat(PXYZ->commstr,"F");
			strcat(PXYZ->commstr,speed);
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

#ifdef	GRBL1

#define MARKSTATE2BIT_03_0	0x00
#define MARKSTATE2BIT_03_1	0x01
#define MARKSTATE2BIT_03_2	0x02
#define MARKSTATE2BIT_03_3	0x03

#endif

#ifdef	GRBL2

#define MARKSTATE2BIT_0C_0	0x00
#define MARKSTATE2BIT_0C_1	0x04
#define MARKSTATE2BIT_0C_2	0x08
#define MARKSTATE2BIT_0C_3	0x0C

#endif

#ifdef	GRBL3

#define MARKSTATE2BIT_30_0	0x00
#define MARKSTATE2BIT_30_1	0x10
#define MARKSTATE2BIT_30_2	0x20
#define MARKSTATE2BIT_30_3	0x30

#endif

unsigned char Put_ProcessingMain(pAxis_WordData pAxisWordData,unsigned char ENGRBL1,unsigned char ENGRBL2,unsigned char ENGRBL3)
{
#if	defined(GRBL1)&&defined(GRBL2)&&defined(GRBL3)
	static char SP1[3][7];
	static char SP2[3][7];
	static char SP3[3][7];
	static char MP1[3][7];
	static char MP2[3][7];
	static char MP3[3][7];
	static char AcrR[3][7];
	static char Speed[3][7];
	static unsigned char state = MARKSTATE2BIT_03_1|MARKSTATE2BIT_0C_1|MARKSTATE2BIT_30_1;

#elif defined(GRBL1)&&defined(GRBL2)
	static char SP1[2][7];
	static char SP2[2][7];
	static char SP3[2][7];
	static char MP1[2][7];
	static char MP2[2][7];
	static char MP3[2][7];
	static char AcrR[2][7];
	static char Speed[2][7];
	static unsigned char state = MARKSTATE2BIT_03_1|MARKSTATE2BIT_0C_1;
#elif defined(GRBL1)
	static char SP1[1][7];
	static char SP2[1][7];
	static char SP3[1][7];
	static char MP1[1][7];
	static char MP2[1][7];
	static char MP3[1][7];
	static char AcrR[1][7];
	static char Speed[1][7];
	static unsigned char state = MARKSTATE2BIT_03_1;
#endif
    static unsigned char datacount1 = 0,datacount2 = 0,datacount3 = 0;

#ifdef GRBL1
	switch((state&0x03)&ENGRBL1)
	{
		case MARKSTATE2BIT_03_1:
			itoa(pAxisWordData[datacount1].XStopPoint,  SP1[0], 10);
			itoa(pAxisWordData[datacount1].YStopPoint,  SP2[0], 10);
			itoa(pAxisWordData[datacount1].ZStopPoint,  SP3[0], 10);
			itoa(pAxisWordData[datacount1].XMidlePoint, MP1[0], 10);
			itoa(pAxisWordData[datacount1].YMidlePoint, MP2[0], 10);
			itoa(pAxisWordData[datacount1].ZMidlePoint, MP3[0], 10);
			itoa(pAxisWordData[datacount1].XYZACR_R,    AcrR[0], 10);
			itoa(pAxisWordData[datacount1].XYZMoveSpeed,Speed[0], 10);
			state = (state & ~0x03)|MARKSTATE2BIT_03_2;

		case MARKSTATE2BIT_03_2:
			if(!Put_XYZMoveToStrQueue(	GRBL1,READMOVEMODLE_GRBL1(pAxisWordData[datacount1].MoveModle),\
									(const char*)SP1[0],(const char*)SP2[0],(const char*)SP3[0],\
									(const char*)MP1[0],(const char*)MP2[0],(const char*)MP3[0],\
									(const char*)AcrR[0],(const char*)Speed[0],REL_BASE))
			{
				if(datacount1 == 2)
					state = (state & ~0x03)|MARKSTATE2BIT_03_3;
				else
					state = (state & ~0x03)|MARKSTATE2BIT_03_0;	
			}
			break;
		case MARKSTATE2BIT_03_0:
			break;
		case MARKSTATE2BIT_03_3:
			if(!Put_CMDToStrQueue(GRBL1,"M9\nM8\n"))
			{
				state = (state & ~0x03)|MARKSTATE2BIT_03_0;
				putqueueflag1 = ENO_GRBL1;
			}
			break;
	}
#endif

#ifdef GRBL2
	switch((state&0x0C)&ENGRBL2)
	{
		case MARKSTATE2BIT_0C_1:
			itoa(pAxisWordData[datacount2].WStopPoint,  SP1[1], 10);
			itoa(pAxisWordData[datacount2].RStopPoint,  SP2[1], 10);
			itoa(pAxisWordData[datacount2].VStopPoint,  SP3[1], 10);
			itoa(pAxisWordData[datacount2].WMidlePoint, MP1[1], 10);
			itoa(pAxisWordData[datacount2].RMidlePoint, MP2[1], 10);
			itoa(pAxisWordData[datacount2].VMidlePoint, MP3[1], 10);
			itoa(pAxisWordData[datacount2].WRVACR_R,    AcrR[1], 10);
			itoa(pAxisWordData[datacount2].WRVMoveSpeed,Speed[1], 10);
			state = (state & ~0x0C)|MARKSTATE2BIT_0C_2;
		case MARKSTATE2BIT_0C_2:
			if(!Put_XYZMoveToStrQueue(	GRBL2,READMOVEMODLE_GRBL2(pAxisWordData[datacount2].MoveModle),\
									(const char*)SP1[1],(const char*)SP2[1],(const char*)SP3[1],\
									(const char*)MP1[1],(const char*)MP2[1],(const char*)MP3[1],\
									(const char*)AcrR[1],(const char*)Speed[1],REL_BASE))
			{
				//if(datacount2 == 2)
					state = (state & ~0x0C)|MARKSTATE2BIT_0C_3;
				//else
				//	state = (state & ~0x0C)|MARKSTATE2BIT_0C_0;
			}
			break;
		case MARKSTATE2BIT_0C_0:
			break;
		case MARKSTATE2BIT_0C_3:
			if(!Put_CMDToStrQueue(GRBL2,"M9\nM8\n"))
			{
				state = (state & ~0x0C)|MARKSTATE2BIT_0C_0;
				putqueueflag2 = ENO_GRBL2;
			}
			break;
	}
#endif

#ifdef GRBL3
	switch((state&0x30)&ENGRBL3)
	{
		case MARKSTATE2BIT_30_1:
			itoa(pAxisWordData[datacount3].AStopPoint,  SP1[2], 10);
			itoa(pAxisWordData[datacount3].BStopPoint,  SP2[2], 10);
			itoa(pAxisWordData[datacount3].CStopPoint,  SP3[2], 10);
			itoa(pAxisWordData[datacount3].AMidlePoint, MP1[2], 10);
			itoa(pAxisWordData[datacount3].BMidlePoint, MP2[2], 10);
			itoa(pAxisWordData[datacount3].CMidlePoint, MP3[2], 10);
			itoa(pAxisWordData[datacount3].ABCACR_R,    AcrR[2], 10);
			itoa(pAxisWordData[datacount3].ABCMoveSpeed,Speed[2], 10);
			state = (state & ~0x30)|MARKSTATE2BIT_30_2;
		case MARKSTATE2BIT_30_2:
			if(!Put_XYZMoveToStrQueue(	GRBL3,READMOVEMODLE_GRBL3(pAxisWordData[datacount3].MoveModle),\
									(const char*)SP1[2],(const char*)SP2[2],(const char*)SP3[2],\
									(const char*)MP1[2],(const char*)MP2[2],(const char*)MP3[2],\
									(const char*)AcrR[2],(const char*)Speed[2],REL_BASE))
			{
				//if(datacount3 == 2)
					state = (state & ~0x30)|MARKSTATE2BIT_30_3;
				//else
				//	state = (state & ~0x30)|MARKSTATE2BIT_30_0;
				
			}
			break;
		case MARKSTATE2BIT_30_0:
			
			break;
		case MARKSTATE2BIT_30_3:
			if(!Put_CMDToStrQueue(GRBL3,"M9\nM8\n"))
			{
				state = (state & ~0x30)|MARKSTATE2BIT_30_0;
				putqueueflag3 = ENO_GRBL3;
			}
			break;
	}
#endif


#ifdef GRBL1
	if(!(state&0x03))
	{
		state = (state & ~0x03)|MARKSTATE2BIT_03_1;
		if(++datacount1 >= 4)
		{
			datacount1 = 0;	
			return  0;
		}
	}
#endif

#ifdef GRBL2
	if(!(state&0x0C))
	{
		state = (state & ~0x0C)|MARKSTATE2BIT_0C_1;
		if(++datacount2 >= 4)
		{
			datacount2 = 0;
			return  0;
		}
	}
#endif

#ifdef GRBL3

	if(!(state&0x30))
	{		
		state = (state & ~0x30)|MARKSTATE2BIT_30_1;
		if(++datacount3 >= 4)
		{
			datacount3 = 0;
			return  0;
		}
	}
#endif
	return  1;
}

void test_init()
{
	AxisWordDatas[0].MoveModle = SETMOVEMODLE_GRBL1(X_MOVE_LINE)|SETMOVEMODLE_GRBL2(X_MOVE_LINE)|SETMOVEMODLE_GRBL3(X_MOVE_LINE); //5bit one Axis
	AxisWordDatas[1].MoveModle = SETMOVEMODLE_GRBL1(X_MOVE_LINE)|SETMOVEMODLE_GRBL2(X_MOVE_LINE)|SETMOVEMODLE_GRBL3(X_MOVE_LINE); //5bit one Axis
	AxisWordDatas[2].MoveModle = SETMOVEMODLE_GRBL1(XY_MOVE_LINE)|SETMOVEMODLE_GRBL2(XY_MOVE_ARC_L)|SETMOVEMODLE_GRBL3(XY_MOVE_LINE); //5bit one Axis
	AxisWordDatas[3].MoveModle = SETMOVEMODLE_GRBL1(XY_MOVE_LINE)|SETMOVEMODLE_GRBL2(XY_MOVE_ARC_R)|SETMOVEMODLE_GRBL3(XY_MOVE_LINE); //5bit one Axis

#ifdef GRBL1

	AxisWordDatas[0].XStopPoint = 200;
	AxisWordDatas[0].XYZMoveSpeed = 4000;
	
	AxisWordDatas[1].XStopPoint = -200;
	AxisWordDatas[1].XYZMoveSpeed = 4000;

	AxisWordDatas[2].XStopPoint = 200;
	AxisWordDatas[2].YStopPoint = 100;
	AxisWordDatas[2].XYZMoveSpeed = 4000;

	AxisWordDatas[3].XStopPoint = -200;
	AxisWordDatas[3].YStopPoint = -100;
	AxisWordDatas[3].XYZMoveSpeed = 4000;

#endif

#ifdef GRBL2

	AxisWordDatas[0].WStopPoint = 200;
	AxisWordDatas[0].WRVMoveSpeed = 4000;

	AxisWordDatas[1].WStopPoint = -200;
	AxisWordDatas[1].WRVMoveSpeed = 4000;

	AxisWordDatas[2].WStopPoint = 200;
	AxisWordDatas[2].RStopPoint = 0;
	AxisWordDatas[2].WMidlePoint = 100;
	AxisWordDatas[2].RMidlePoint = 0;
	AxisWordDatas[2].WRVMoveSpeed = 4000;

	AxisWordDatas[3].WStopPoint = -200;
	AxisWordDatas[3].RStopPoint = 0;
	AxisWordDatas[3].WMidlePoint = -100;
	AxisWordDatas[3].RMidlePoint = 0;
	AxisWordDatas[3].WRVMoveSpeed = 4000;

#endif

#ifdef GRBL3

	AxisWordDatas[0].AStopPoint = 200;
	AxisWordDatas[0].ABCMoveSpeed = 4000;

	AxisWordDatas[1].AStopPoint = -200;
	AxisWordDatas[1].ABCMoveSpeed = 4000;

	AxisWordDatas[2].AStopPoint = 100;
	AxisWordDatas[2].BStopPoint = 100;
	AxisWordDatas[2].ABCMoveSpeed = 4000;

	AxisWordDatas[3].AStopPoint = -100;
	AxisWordDatas[3].BStopPoint = -100;
	AxisWordDatas[3].ABCMoveSpeed = 4000;

#endif

}
