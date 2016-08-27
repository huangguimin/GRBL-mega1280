#ifndef __SEND_CMD_H__
#define __SEND_CMD_H__

unsigned char Send_RunTime_CMD(unsigned char grblnum,unsigned char CMD,unsigned char state);
void Init_Data_Buff(unsigned char grblnum);

void Send_Buff_Start(unsigned char grblnum,unsigned char state);
void Send_CMD_RunTime_DelayGetState(unsigned grblnum,unsigned char state,unsigned int time);
#endif