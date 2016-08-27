#ifndef __PUTQUEUE_H__
#define __PUTQUEUE_H__

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

#define XY_MOVE_ARC_L 	7
#define XZ_MOVE_ARC_L 	8
#define YZ_MOVE_ARC_L 	9
#define XY_MOVE_ARC_Z_L 	10
#define XZ_MOVE_ARC_Y_L 	11
#define YZ_MOVE_ARC_X_L 	12

#define XY_MOVE_ARC_R_L 	13
#define XZ_MOVE_ARC_R_L 	14
#define YZ_MOVE_ARC_R_L 	15
#define XY_MOVE_ARC_Z_R_L 	16
#define XZ_MOVE_ARC_Y_R_L 	17
#define YZ_MOVE_ARC_X_R_L 	18

#define X_MOVE_LINE_H 		19
#define Y_MOVE_LINE_H 		20
#define Z_MOVE_LINE_H 		21
#define XY_MOVE_LINE_H 		22
#define XZ_MOVE_LINE_H 		23
#define YZ_MOVE_LINE_H 		24
#define XYZ_MOVE_LINE_H 	25

#define XY_MOVE_ARC_R 		26
#define XZ_MOVE_ARC_R 		27
#define YZ_MOVE_ARC_R 		28
#define XY_MOVE_ARC_Z_R 	29
#define XZ_MOVE_ARC_Y_R 	30
#define YZ_MOVE_ARC_X_R 	31

#define XY_MOVE_ARC_R_R 	32
#define XZ_MOVE_ARC_R_R 	33
#define YZ_MOVE_ARC_R_R 	34
#define XY_MOVE_ARC_Z_R_R 	35
#define XZ_MOVE_ARC_Y_R_R 	36
#define YZ_MOVE_ARC_X_R_R 	37


#define ABS_BASE 	0
#define REL_BASE 	1

#define ACII_ABS_BASE	"G90"
#define ACII_REL_BASE	"G91"
#define ACII_SET_MPOS	"G92"

#define HIGHT       0
#define LINE        1
#define ARC_L       2
#define ARC_R       3

#define ACII_HIGHT	"G00"
#define ACII_LINE	"G01"
#define ACII_ARC_L	"G02"
#define ACII_ARC_R	"G03"
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
typedef struct sendcommdbuff
{
	unsigned char state;
	char commstr[100];
	unsigned char bytecount;
}SCBuff,*pSCBuff;


void Put_NumToStrQueue(PHQUEUE Q,int num);
unsigned char Put_CMDToStrQueue(unsigned char grblnum,const char * Pacii);
void SCBuffClear(pSCBuff P);
void Init_Data_Buff(unsigned char grblnum);
unsigned char Put_AciiToStrQueue(PHQUEUE Q,pSCBuff P);
unsigned char Put_SetXYZWposToStrQueue(unsigned char grblnum,const char *Xnum,const char *Ynum,const char *Znum);
unsigned char Put_XYZMoveToStrQueue(unsigned char grblnum,unsigned char movemodle,\
								const char * Xnum,const char * Ynum,const char * Znum,		\
								const char * Inum,const char * Jnum,const char * Knum,		\
								const char * Rnum,const char * speed,unsigned char mbase);


#define EN_GRBL1 	0xFF
#define ENO_GRBL1 	0xFC
#define EN_GRBL2 	0xFF
#define ENO_GRBL2 	0xF3
#define EN_GRBL3 	0xFF
#define ENO_GRBL3 	0xCF

#define READMOVEMODLE_GRBL1(X)	((X)    &0x0000003F)
#define READMOVEMODLE_GRBL2(X)	((X>>6) &0x0000003F)
#define READMOVEMODLE_GRBL3(X)	((X>>12)&0x0000003F)

#define SETMOVEMODLE_GRBL1(X)   ((unsigned long)(X))
#define SETMOVEMODLE_GRBL2(X)   (((unsigned long)(X))<<6)
#define SETMOVEMODLE_GRBL3(X)   (((unsigned long)(X))<<12)

void AxisWordDatasClear();
typedef struct axisworddata
{
	unsigned long MoveModle; //5bit one Axis
	unsigned char OverAll;
#ifdef  GRBL1
	 			 int XStartPoint;
	 			 int XStopPoint;
	 			 int YStartPoint;
	 			 int YStopPoint;
	 			 int ZStartPoint;
	 			 int ZStopPoint;
	 			 int XMidlePoint;
	 			 int YMidlePoint;
	 			 int ZMidlePoint;
	    unsigned int XYZMoveSpeed;
	 			 int XYZACR_R;
#endif

#ifdef  GRBL2
	 			 int WStartPoint;
	 			 int RStopPoint;
	 			 int VStartPoint;
	 			 int WStopPoint;
	 			 int RStartPoint;
	 			 int VStopPoint;
	 			 int WMidlePoint;
	 			 int RMidlePoint;
	 			 int VMidlePoint;
	 	unsigned int WRVMoveSpeed;
	 			 int WRVACR_R;
#endif

#ifdef  GRBL3
	 			 int AStartPoint;
	 			 int BStopPoint;
	 			 int CStartPoint;
	 			 int AStopPoint;
	 			 int BStartPoint;
	 			 int CStopPoint;
	 			 int AMidlePoint;
	 			 int BMidlePoint;
	 			 int CMidlePoint;
	 unsigned	 int ABCMoveSpeed;
	 			 int ABCACR_R;
#endif
	unsigned int PaintModle;
}Axis_WordData,*pAxis_WordData;

extern Axis_WordData  AxisWordDatas[10];
unsigned char  Put_ProcessingMain(pAxis_WordData pAxisWordData,unsigned char ENGRBL1,unsigned char ENGRBL2,unsigned char ENGRBL3);
void test_init();

extern unsigned char putqueueflag1,putqueueflag2,putqueueflag3;

#endif