
#ifndef __MODBUS_H__
#define __MODBUS_H__

#include <avr/pgmspace.h>
#include <string.h>
#include "Pin_IO.h"
#include "Time_Init.h"
#include "uart.h"
#include <util/delay.h>
#include "Uart_fifo.h"

//#include "AVR429Lib.h"
#define byte8_0(var)     *((unsigned char *)&var)
#define byte8_1(var)     *((unsigned char *)&var + 1)
#define byte8_2(var)     *((unsigned char *)&var + 2)
#define byte8_3(var)     *((unsigned char *)&var + 3)

#define byte16_0(var)    *((unsigned int *)&var)
#define byte16_1(var)    *((unsigned int *)&var + 1)

#define uchar unsigned char
#define uint unsigned int

#define MACHINNUM 0x01

#define Default 255

//LB98-105ê??ˉê??ìμ?°′?￥
#define Qiang_Bit      0x01
#define Huan_Mo        0x02
#define XiMo_XiaYa     0x04
#define Shoudong_Ximo  0x08
#define Huan_Liao      0x10
#define Ding_Liao      0x20
//LB106-113进入的界面
#define ShiJiao_Model  0x01
#define CanShu_Model   0x02
#define CaoZuo_Model   0x04
#define JianShi_Model  0x08
#define XiTong_Model   0x10
#define IO_Model       0x20


//喷涂模式
#define X_WangFu           0
#define X_WangFu_Y_BuJin   1
#define X_WangFu_W_BuJin   2
#define X_WangFu_Z_BuJin   3

#define Y_WangFu           4
#define Y_WangFu_X_BuJin   5
#define Y_WangFu_W_BuJin   6
#define Y_WangFu_Z_BuJin   7

#define W_WangFu           8
#define W_WangFu_X_BuJin   9
#define W_WangFu_Y_BuJin   10
#define W_WangFu_Z_BuJin   11

#define Z_WangFu           12
#define Z_WangFu_X_BuJin   13
#define Z_WangFu_Y_BuJin   14
#define Z_WangFu_W_BuJin   15
#define X_WangFu_Y_WangFu  16


#define X_DianPen          17
#define Y_DianPen          18
#define W_DianPen          19
#define Z_DianPen          20
#define XY_XieXian_XBuJin  21
#define XY_XieXian_YBuJin  22
#define XY_XieXian_ZBuJin  23
#define XZ_XieXian_XBuJin  24
#define XZ_XieXian_YBuJin  25
#define XZ_XieXian_ZBuJin  26
#define YZ_XieXian_XBuJin  27
#define YZ_XieXian_YBuJin  28
#define YZ_XieXian_ZBuJin  29

//喷枪模式
#define PenQiang_QuanKai   0
#define PenQiang_1_Kai     1
#define PenQiang_2_Kai     2
#define PenQiang_QuanGuan  3
//组合模式
#define WanChengMian        0
#define JiXuMian            1
#define FanMian             2

//示教轴控制按钮
#define ShiJiao_Axis0_L 0x01
#define ShiJiao_Axis0_R 0x02
#define ShiJiao_Axis1_L 0x04
#define ShiJiao_Axis1_R 0x08
#define ShiJiao_Axis2_L 0x10
#define ShiJiao_Axis2_R 0x20

#define ShiJiao_Axis7_L 0x40
#define ShiJiao_Axis7_R 0x80

#define ShiJiao_Axis3_L 0x01
#define ShiJiao_Axis3_R 0x02
#define ShiJiao_Axis4_L 0x04
#define ShiJiao_Axis4_R 0x08
#define ShiJiao_Axis5_L 0x10
#define ShiJiao_Axis5_R 0x20
#define ShiJiao_Axis6_L 0x40
#define ShiJiao_Axis6_R 0x80

//示教按钮
/*
#define ShiJiao_ShouDong_KaiQiang   0x01
#define ShiJiao_HuanMo_ZhengZhuan   0x02
#define ShiJiao_ZiDong_Men          0x04
#define ShiJiao_ShouDong_XiMo       0x08
#define ShiJiao_HuanLiao_XuanZhuan  0x10
#define ShiJiao_DingLiao_ShangSheng 0x20*/

#define ShiJiao_ShouDong_KaiQiang   0x01
#define ShiJiao_HuanMo_ZhengZhuan   0x02
#define ShiJiao_XiMo_XiaYa          0x04
#define ShiJiao_ShouDong_XiMo       0x08
#define ShiJiao_HuanLiao_XuanZhuan  0x10
#define ShiJiao_DingLiao_ShangSheng 0x20

//主控制按钮
#define Fu_Wei              0x01
#define Ban_ZiDong          0x02
#define Quan_ZiDong         0x04
#define PenQiang_GuanBi     0x08
#define QiDong              0x10
#define Zan_Ting            0x20
#define Zhuan_Ding_Button   0x40

//各轴比例
#define X_Bili  106
#define Y_Bili  108
#define Z_Bili  107
#define W_Bili  90

#define A_Bili  160
#define B_Bili  162
#define C_Bili  177
#define D_Bili  100

#define Speed_Bili 160

unsigned int My_Reg[20];

//按键处理
#define ShiJiao_LR      (My_Bit.Bit0|My_Bit.Bit1<<1|My_Bit.Bit2<<2|My_Bit.Bit3<<3|My_Bit.Bit4<<4|My_Bit.Bit5<<5|My_Bit.Bit6<<6|My_Bit.Bit7<<7)
#define ShiJiao_Button  (My_Bit.Bit8|My_Bit.Bit9<<1|My_Bit.Bit10<<2|My_Bit.Bit11<<3|My_Bit.Bit12<<4|My_Bit.Bit13<<5|My_Bit.Bit14<<6|My_Bit.Bit15<<7)
#define ShiJiao_LR_2    (My_Bit.Bit16|My_Bit.Bit17<<1|My_Bit.Bit18<<2|My_Bit.Bit19<<3|My_Bit.Bit20<<4|My_Bit.Bit21<<5|My_Bit.Bit22<<6|My_Bit.Bit23<<7)
#define ZhuKong_Button  (My_Bit.Bit24|My_Bit.Bit25<<1|My_Bit.Bit26<<2|My_Bit.Bit27<<3|My_Bit.Bit28<<4|My_Bit.Bit29<<5|My_Bit.Bit30<<6|My_Bit.Bit31<<7)

//按钮清除

#define FuWei_Clear(D)          {My_Bit.Bit24 = (D);}
#define Ban_ZiDong_Clear(D)     {My_Bit.Bit25 = (D);}
#define Quan_ZiDong_Clear(D)    {My_Bit.Bit26 = (D);}
#define QiDong_Clear(D)         {My_Bit.Bit28 = (D);}

//返回总产量、页面等。。。。
#define Actual_Mian(V)               My_Reg[0] = V  //4X,67
#define Sensor_State(S)              My_Reg[1] = S  //4X,68
#define ShengYu_KaiMen(C)            My_Reg[2] = C  //4X,69
#define Zong_ChanLiang(Z)            My_Reg[3] = Z  //4X,70
#define Warning_Axis(W)              My_Reg[4] = W  //4X,71

#define HuanMo_ZhengZhuan_Button(B) {My_Bit.Bit9 = B;}
#define ZIDong_Men_Clear(B)         {My_Bit.Bit10 = B;}
#define ShouDong_XiMo_Clear(B)      {My_Bit.Bit11 = B;}
#define Huan_Liao_Button(B)         {My_Bit.Bit12 = B;}
#define Ding_Liao_Button(B)         {My_Bit.Bit13 = B;}
#define Trans_finish(B)             {My_Bit.Bit39 = B;}//0x,64
#define Trans_finish2(B)            {My_Bit.Bit38 = B;}//0x,63


#define JiXieShou_Butten_EN                My_Bit.Bit37
#define JiXieShou_Butten_EN_Clear(B)       {My_Bit.Bit37 = B;}

void Modbus_Int();
void Modbus_Processing(void);
/**************16位CRC校验函数,查表法********************/
uint CRC16(uchar *Pushdata,uchar length);

/**************操作函数*****************/

void Write_XYZWRV_My_Reg(uchar Adrr_Data,uint Value_Axis);         //各个轴设置运行距离

uint Read_XYZWRV_My_Reg(uchar Start_Adrr);    //返回各轴当前所在距离

unsigned char In_X(uchar Adrr_X);                            //读出各X输入的状态
void Write_Y_and_Bit(uchar Adrr_Y_Bit, uchar Value_Y_Bit);            //设置各Y输出状态
unsigned char Reg_Y_bit(uchar Adrr_Y);


//void Empty_Buf(uchar *buf,uchar num);

typedef struct XYZ_Value{
                    long X_Start_Point;
                    long Y_Start_Point;
                    long Z_Start_Point;
                    long W_Start_Point;
                    long V_Start_Point;
                    long R_Start_Point;

                    long X_Stop_Point;
                    long Y_Stop_Point;
                    long Z_Stop_Point;
                    long W_Stop_Point;
                    long V_Stop_Point;
                    long R_Stop_Point;

                    uint X_Speed;
                    uint Y_Speed;
                    uint Z_Speed;
                    uint W_Speed;
                    uint V_Speed;
                    uint R_Speed;

                    uint WangFu_CiShu;
                    uint BuJin_HangCi;
                    long BuJin_HangJu;
                    uchar TingQiang_XuanZe;
                    uchar PenQiang_Model;
                    uchar PenTu_Model;
                    uchar ZuHe_Model;
                    long Actual_Mian;
                    }XYZ_Value;

typedef struct System_Value{
                    uint X_Init_Speed;
                    uint X_Back_Speed;
                    uint Y_Init_Speed;
                    uint Y_Back_Speed;
                    long X_Safe_Point;
                    long Y_Safe_Point;
                    uint W_Init_Speed;
                    uint Z_Init_Speed;
                    uint Z_Back_Speed;
                    long Z_Safe_Point;
                    long W_Safe_Point;
                    float SpeedX;

                    long X_AnQuan_FanWei;
                    long Y_AnQuan_FanWei;
                    uint CuiMo_Speed;
                    long Z_AnQuan_FanWei;
                    long W_AnQuan_FanWei;
                    uint DingDianQi_YanShi;

                    long ShuiBeng_YanShi;
                    uint ShuLiang_XiMo;
                    uint CuiMo_CiShu;
                    uint ShangCuiQi_CiShu;
                    uint KaiQiang_YanShi;
                    uint WuHua_YanShi;
                    //uint Ya_Mo_YanShi;
                    }System_Value;
typedef struct XiMoVaule
            {
                    long A_Start_Point;
                    long B_Start_Point;
                    long C_Point;
                    long A_Stop_Point;
                    long B_Stop_Point;
                    uint XiMo_WangFu_Speed;
                    uchar XiMo_BuJin_Num;
                    uchar XiMo_WangFu_Num;
                    uchar XiMo_Model;
                    uchar XiMo_ZuHe_Model;
            }XiMoVaule;

typedef struct JiXieShou
            {
                long Move_Start;
                long Move_Stop;
                uint Move_Speed;
            }JiXieShou;

typedef struct BitBuf{
                         unsigned Bit0:1;
					unsigned Bit1:1;
					unsigned Bit2:1;
					unsigned Bit3:1;
					unsigned Bit4:1;
					unsigned Bit5:1;
					unsigned Bit6:1;
					unsigned Bit7:1;
					unsigned Bit8:1;
					unsigned Bit9:1;
					unsigned Bit10:1;
					unsigned Bit11:1;
					unsigned Bit12:1;
					unsigned Bit13:1;
					unsigned Bit14:1;
					unsigned Bit15:1;
					unsigned Bit16:1;
					unsigned Bit17:1;
					unsigned Bit18:1;
					unsigned Bit19:1;
					unsigned Bit20:1;
					unsigned Bit21:1;
					unsigned Bit22:1;
					unsigned Bit23:1;
					unsigned Bit24:1;
					unsigned Bit25:1;
					unsigned Bit26:1;
					unsigned Bit27:1;
					unsigned Bit28:1;
					unsigned Bit29:1;
					unsigned Bit30:1;
					unsigned Bit31:1;
					unsigned Bit32:1;
					unsigned Bit33:1;
					unsigned Bit34:1;
					unsigned Bit35:1;
					unsigned Bit36:1;
					unsigned Bit37:1;
					unsigned Bit38:1;
					unsigned Bit39:1;
                    }BitBuf;
volatile  BitBuf My_Bit;

extern float AxisNum[];
#endif
