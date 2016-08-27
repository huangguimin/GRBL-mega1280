#include "global.h"

unsigned char Send_RunTime_CMD(unsigned char grblnum,unsigned char CMD,unsigned char state)
{
	switch(grblnum|state)
	{
#ifdef	GRBL1
		case GRBL1|0x01:
			if(!QueueInput(&Uart1QCMDRTs, CMD))
			{
				UART1_INT_EMP_Start;
				GRBL1state.SEND_CMD = 0;
				return 0;
			}
			break;
#endif

#ifdef	GRBL2
		case GRBL2|0x01:
			if(!QueueInput(&Uart2QCMDRTs, CMD))
			{
				UART2_INT_EMP_Start;
				GRBL2state.SEND_CMD = 0;
				return 0;
			}
			break;
#endif	

#ifdef	GRBL3
		case GRBL3|0x01:
			if(!QueueInput(&Uart3QCMDRTs, CMD))
			{
				UART3_INT_EMP_Start;
				GRBL3state.SEND_CMD = 0;
				return 0;
			}
			break;
#endif
/*
#if defined(GRBL1) && defined(GRBL2)
		case GRBL1|GRBL2|0x01:
			if(!QueueInput(&Uart1QCMDRTs, CMD)&&!QueueInput(&Uart2QCMDRTs, CMD))
			{
				SnedRunTimeCMD1 = CMD;
				SnedRunTimeCMD2 = CMD;
				UART1_INT_EMP_Start;
				UART2_INT_EMP_Start;
				GRBL1state.SEND_CMD = 0;
				GRBL2state.SEND_CMD = 0;
			}
			break;
#endif

#if defined(GRBL1) && defined(GRBL3)
		case GRBL1|GRBL3|0x01:
			if(!QueueInput(&Uart1QCMDRTs, CMD)&&!QueueInput(&Uart3QCMDRTs, CMD))
			{
				SnedRunTimeCMD1 = CMD;
				SnedRunTimeCMD3 = CMD;
				UART1_INT_EMP_Start;
				UART3_INT_EMP_Start;
				GRBL1state.SEND_CMD = 0;
				GRBL3state.SEND_CMD = 0;
			}
			break;
#endif

#if defined(GRBL2) && defined(GRBL3)
		case GRBL2|GRBL3|0x01:
			if(!QueueInput(&Uart2QCMDRTs, CMD)&&!QueueInput(&Uart3QCMDRTs, CMD))
			{
				SnedRunTimeCMD2 = CMD;
				SnedRunTimeCMD3 = CMD;
				UART2_INT_EMP_Start;
				UART3_INT_EMP_Start;
				GRBL2state.SEND_CMD = 0;
				GRBL3state.SEND_CMD = 0;
			}
			break;
#endif

#if  defined(GRBL1) && defined(GRBL2) && defined(GRBL3)
		case GRBL1|GRBL2|GRBL3|0x01:
			if(!QueueInput(&Uart1QCMDRTs, CMD)&&!QueueInput(&Uart2QCMDRTs, CMD)&&!QueueInput(&Uart3QCMDRTs, CMD))
			{
				SnedRunTimeCMD1 = CMD;
				SnedRunTimeCMD2 = CMD;
				SnedRunTimeCMD3 = CMD;
				UART1_INT_EMP_Start;
				UART2_INT_EMP_Start;
				UART3_INT_EMP_Start;
				GRBL1state.SEND_CMD = 0;
				GRBL2state.SEND_CMD = 0;
				GRBL3state.SEND_CMD = 0;
			}
			break;
#endif
*/
		default:
			break;
	}
	return 1;
}

void Send_Buff_Start(unsigned char grblnum,unsigned char state)
{
	switch(grblnum|state)
	{
#ifdef 	GRBL1
		case GRBL1|0x01:
			if(!USART1_Send_word_nowait_IntStart())
				GRBL1state.OK = 0;
			break;
#endif

#ifdef	GRBL2
		case GRBL2|0x01:
			if(!USART2_Send_word_nowait_IntStart())
				GRBL2state.OK = 0;
			break;
#endif

#ifdef	GRBL3
		case GRBL3|0x01:
			if(!USART3_Send_word_nowait_IntStart())
				GRBL3state.OK = 0;
			break;
#endif
	}
}

void Send_CMD_RunTime_DelayGetState(unsigned grblnum,unsigned char state,unsigned int time)
{
	static unsigned int count1 = 0,count2 = 0,count3 = 0;
	switch(grblnum|state)
	{
#ifdef 	GRBL1
		case GRBL1|0x01:
			if((count1++>time)&&!Send_RunTime_CMD(GRBL1,'?',GRBL1state.SEND_CMD = 1))
			{
				count1 = 0;
				GRBL1state.STATE_END = 0;
			}
			break;
#endif

#ifdef	GRBL2
		case GRBL2|0x01:
			if((count2++>time)&&!Send_RunTime_CMD(GRBL2,'?',GRBL2state.SEND_CMD = 1))
			{
				count2 = 0;
				GRBL2state.STATE_END = 0;
			}
			break;
#endif

#ifdef	GRBL3
		case GRBL3|0x01:
			if((count3++>time)&&!Send_RunTime_CMD(GRBL3,'?',GRBL3state.SEND_CMD = 1))
			{
				count3 = 0;
				GRBL3state.STATE_END = 0;
			}
			break;
#endif
	}
}