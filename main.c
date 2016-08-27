//
//
//----------  ＭＣＸ３１４Ａｓ マニュアル掲載用プログラム -----
//
#include "global.h"


int main()
{
	unsigned char HmiCommState = 0;
	unsigned char HmiCommState2 = 0;
	unsigned char HmiCommState3 = 0;

	PORTB = 0xFF;
	DDRB = 0xFF;
	
	//Time1_init();
	Modbus_Int();
#ifdef	GRBL1
	USART1_initial();
	HmiCommState = HMI_COMD_MOVE_6;
	FindAciiStClear(GRBL1);
#endif

#ifdef 	GRBL2	
	USART2_initial();
	HmiCommState2 = HMI_COMD_MOVE_6;
	FindAciiStClear(GRBL2);
#endif

#ifdef 	GRBL3	
	USART3_initial();
	HmiCommState3 = HMI_COMD_MOVE_6;
	FindAciiStClear(GRBL3);
#endif

	AxisWordDatasClear();
	test_init();
	INT_int_init();
	sei();
	Init_Data_Buff(GRBL1);
	FindAciiStClear(GRBL1);
	Init_Data_Buff(GRBL2);
	FindAciiStClear(GRBL2);
	Init_Data_Buff(GRBL3);
	FindAciiStClear(GRBL3);
	Put_CMDToStrQueue(GRBL1,"$X\nM8\n");
	GRBL1state.OK = 1;
	Put_CMDToStrQueue(GRBL2,"$X\nM8\n");
	GRBL2state.OK = 1;
	Put_CMDToStrQueue(GRBL3,"$X\nM8\n");
	GRBL3state.OK = 1;
	_delay_ms(5000);
	HmiCommState = HMI_COMD_REST;
	HmiCommState2 = HMI_COMD_REST;
	HmiCommState3 = HMI_COMD_REST;
	while(1)
	{
#ifdef 	GRBL1	

		Send_Buff_Start(GRBL1,GRBL1state.OK);
		Send_RunTime_CMD(GRBL1,COMD_REST_GRBL,GRBL1state.SEND_CMD);
		Processing_UartReceive_Acii(GRBL1);
		if(GRBL1state.RESET)
		{
			GRBL1state.RESET = 0;
			GRBL1state.SEND_CMD = 1;
		}
		if(GRBL1state.HOMING)
		{
			HmiCommState = HMI_COMD_REST;
			LED_Run(~LED_STATE);
		}
		
		Send_CMD_RunTime_DelayGetState(GRBL1,GRBL1state.STATE_END,3000);


		switch(HmiCommState)
		{
			case HMI_COMD_REST:				
				HmiCommState = HMI_COMD_MOVE_0;
				GRBL1state.HOMING = 0;
		    	break;
			case HMI_COMD_MOVE_0:
				if(!Put_SetXYZWposToStrQueue(GRBL1,"0","0","0"))
				{
					HmiCommState = HMI_COMD_MOVE_11;
					GRBL1state.OK = 1;
					putqueueflag1 = EN_GRBL1;
				}
				break;
			case HMI_COMD_MOVE_11:
				EXTERN_INT0_ON;
				Send_RunTime_CMD(GRBL1,'?',GRBL1state.SEND_CMD = 1);
				HmiCommState = HMI_COMD_MOVE_1;
		    	break;
			case HMI_COMD_MOVE_1:
				break;
	    }
#endif

#ifdef 	GRBL2

	    Send_Buff_Start(GRBL2,GRBL2state.OK);
	    Send_RunTime_CMD(GRBL2,COMD_REST_GRBL,GRBL2state.SEND_CMD);
	    Processing_UartReceive_Acii(GRBL2);
		if(GRBL2state.HOMING)
			HmiCommState2 = HMI_COMD_REST;
		if(GRBL2state.RESET)
		{
			GRBL2state.RESET = 0;
			GRBL2state.SEND_CMD = 1;
		}
		Send_CMD_RunTime_DelayGetState(GRBL2,GRBL2state.STATE_END,3000);
		

		switch(HmiCommState2)
		{
			case HMI_COMD_REST:
				HmiCommState2 = HMI_COMD_MOVE_0;
				GRBL2state.HOMING = 0;
		    	break;
			case HMI_COMD_MOVE_0:
				if(!Put_SetXYZWposToStrQueue(GRBL2,"0","0","0"))
				{	
					HmiCommState2 = HMI_COMD_MOVE_11;
					GRBL2state.OK = 1;
					//putqueueflag2 = EN_GRBL2;
				}
				break;
			case HMI_COMD_MOVE_11:
				EXTERN_INT1_ON;
				Send_RunTime_CMD(GRBL2,'?',GRBL2state.SEND_CMD = 1);
				//while(1)Modbus_Processing();
				HmiCommState2 = HMI_COMD_MOVE_1;
		    	break;
			case HMI_COMD_MOVE_1:
				break;
	    }
#endif

#ifdef	GRBL3

	    Send_Buff_Start(GRBL3,GRBL3state.OK);
		Send_RunTime_CMD(GRBL3,COMD_REST_GRBL,GRBL3state.SEND_CMD);
		Processing_UartReceive_Acii(GRBL3);
		if(GRBL3state.HOMING)
			HmiCommState3 = HMI_COMD_REST;
		if(GRBL3state.RESET)
		{
			GRBL3state.RESET = 0;
			GRBL3state.SEND_CMD = 1;
		}
		Send_CMD_RunTime_DelayGetState(GRBL3,GRBL3state.STATE_END,3000);

		switch(HmiCommState3)
		{
			case HMI_COMD_REST:
				HmiCommState3 = HMI_COMD_MOVE_0;
				GRBL3state.HOMING = 0;
		    	break;
			case HMI_COMD_MOVE_0:
				if(!Put_SetXYZWposToStrQueue(GRBL3,"0","0","0"))
				{	
					HmiCommState3 = HMI_COMD_MOVE_11;
					GRBL3state.OK = 1;
					//putqueueflag3 = EN_GRBL3;
				}
				break;
			case HMI_COMD_MOVE_11:
				EXTERN_INT5_ON;
				Send_RunTime_CMD(GRBL3,'?',GRBL3state.SEND_CMD = 1);
				HmiCommState3 = HMI_COMD_MOVE_1;
		    	break;
			case HMI_COMD_MOVE_1:
				break;
	    }
#endif
	    //_delay_ms(100);
	    //if(HmiCommState == HMI_COMD_MOVE_1&&HmiCommState2 == HMI_COMD_MOVE_1&&HmiCommState3 == HMI_COMD_MOVE_1)
	    //{
	    	Put_ProcessingMain(AxisWordDatas,putqueueflag1,putqueueflag2,putqueueflag3);
	    //}
	    LED_Run(~LED_STATE);

    if(QueueGetDataCount(&Uart1QCMDr)>TheBigNum)
        TheBigNum = QueueGetDataCount(&Uart1QCMDr);
    if(QueueGetDataCount(&Uart2QCMDr)>TheBigNum)
        TheBigNum = QueueGetDataCount(&Uart2QCMDr);
    if(QueueGetDataCount(&Uart3QCMDr)>TheBigNum)
        TheBigNum = QueueGetDataCount(&Uart3QCMDr);
	    //Send_RunTime_CMD(GRBL1|GRBL3,'?');
	    Modbus_Processing();
	}
}
