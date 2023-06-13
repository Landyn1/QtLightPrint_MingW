#ifndef CUDRVE_H
#define CUDRVE_H

#include "CUDrvE_global.h"

#define WINDLL __stdcall

#define ushort unsigned short
//#define byte unsigned char
typedef unsigned char byte;
#define uint unsigned int

#define BOOL int

//Luo ZW
const byte DA16_XY 								= 0x00;//6'd0		振镜直线插补指令
const byte DA16_CIRCLE 							= 0x01;//6'd1		振镜圆弧插补指令
const byte LASER 	 							= 0x02;//6'd2		激光控制指令
const byte MOTOR_RUN							= 0x03;//6'd3		步进电机插补指令
const byte LASER_DLY							= 0x04;//6'd4		激光器延时自动关闭
const byte MOTOR_SCAN							= 0x05;//6'd5		扫描模式
const byte MOTOR_HOME							= 0x06;//6'd6 		回原点指令
const byte MOTOR_SPEED							= 0x07;//6'd7		设置步进电机速度指令
const byte MOTOR_SPEED_CH						= 0x08;//6'd8		设置步进电机空程速度指令
const byte PWM0									= 0x09;//6'd9		PWM0标识
const byte PWM1									= 0x0a;//6'd10		PWM1标识
const byte PWM2									= 0x0b;//6'd11		PWM2标识（光纤激光器专用）
const byte SET_DDA_DELAY						= 0x0c;//6'd12		设置振镜运动两坐标间的延时
const byte SET_NUL_DELAY						= 0x0d;//6'd13		设置任意缓冲指令间的延时
const byte NULL_DLY								= 0x0e;//6'd14
const byte MOTOR_STOP							= 0x0f;//6'd15;
const byte ROTARY_VSPD							= 0x10;//6'd16
const byte MOTOR_XY								= 0x11;//6'd17
const byte RATIO_SET							= 0x12;//6'd18
const byte DA16_XYZ								= 0x13;//6'd0		振镜直线插补指令

const byte CU_SETUP_SET							= 0x14;//6'd20		系统设置
const byte CU_PAUSE								= 0x15;//6'd21		振镜暂停指令
const byte MOTOR_PRE							= 0x16;//6'd22
const byte SET_DATA_INDEX						= 0x17;//6'd23		设置数据索引
const byte SET_EVENT_TIMES						= 0x18;//6'd24
const byte SET_EVENT_CLOCKS						= 0x19;//6'd25
const byte CU_SETUP_CLR							= 0x1a;//6'd26		设置清除模式
const byte CU_CORRECT_SET						= 0x1b;//6'd27		振镜数据修正指令
const byte CU_REPEAT_NUMS						= 0x1c;//6'd28
const byte CU_REPEAT_DATA						= 0x1d;//6'd29
const byte CU_FLYING_FLAG						= 0x1e;//6'd30
const byte SET_OUTPUT							= 0x1f;//6'd31		IO输出指令
const byte SET_DACOUT							= 0x20;//6'd32		设置模拟输出 用作模拟功率调节
const byte BUF_BEGIN							= 0x21;//6'd33
const byte LASER_PW_SET							= 0x22;//6'd34

const byte CU_INPUT_WAIT						= 0x24;//6'd36
const byte CU_RED_DATA							= 0x25;//6'd37;

const byte OTHER_END							= 0x28;//6'd40
const byte BUF_END								= 0x29;//6'd41

const byte SET_NUL_DELAY_EXT					= 0x2a;//6'd42
const byte PWM2I								= 0x2b;//6'd43;

const byte DA16_XYJMP = 0x30;// new 23-1-9
const byte SET_RorL = 0x31;// new 23-1-14

const byte IMG_PARA = 0x3a;// new 23-2-25 设置图像加工参数

const byte JUMP_DLY = 0x3c;// new 23-1-13
const byte TUNE_DLY = 0x3d;// new 23-1-12
const byte OPEN_DLY = 0x3e;// new 23-1-9
const byte CLOSE_DLY = 0x3f;// new 23-1-12


const byte  NULLOP = 0x40;//空指令

const byte QRY_CMD_R							= 0x00 ;
const byte QRY_CMD_W							= 0x01 ;

const byte JMW_CANCEL							= 0x00 ;
const byte CU_RESUME							= 0x01 ;
const byte JMW_RESET							= 0x02 ;
const byte CU_PAUSE_IM							= 0x03 ;
const byte SET_LED								= 0x04 ;
const byte CLR_LED								= 0x05 ;
const byte RotaryCountEn						= 0x06 ;
const byte RotaryCountDis						= 0x07 ;
const byte RotaryDirCW							= 0x08 ;
const byte RotaryDirCCW							= 0x09 ;
const byte RotaryVirtual						= 0x0a ;
const byte RotaryReal							= 0x0b ;
const byte CU_MOTOR_STOPX						= 0x0c ;
const byte CU_MOTOR_STOPY						= 0x0d ;
const byte CU_MOTOR_STOPZ						= 0x0e ;
const byte RED_OUTLINE_S						= 0x0f;
const byte RED_OUTLINE_E						= 0x10;
const byte INTER_TRIG_O							= 0x11;
const byte INTER_TRIG_C							= 0x12;
const byte SCH_SPD_H							= 0x13;
const byte SCH_SPD_L							= 0x14;
const byte MOTOR_CMD							= 0x15;
const byte LASER_RF								= 0x16;
const byte LASER_CO2							= 0x17;
const byte FIFO_SET								= 0x18;
const byte FIFO_CLR								= 0x19;
const byte CIRCULATE_START						= 0x1a;
const byte CIRCULATE_END						= 0x1b;
const byte JMW_RESET_WNET						= 0x20 ;

const byte CU_IMM_RSP0							= 0x00 ;
const byte CU_IMM_RSP1							= 0x01 ;
const byte GET_IOSTATUS0						= 0x02 ;
const byte GET_IOSTATUS1						= 0x03 ;
const byte GET_DATA_LEN0						= 0x04 ;
const byte GET_DATA_LEN1						= 0x05 ;
const byte GET_DATA_LEN2						= 0x06 ;
const byte GET_DATA_INDEX0						= 0x08 ;
const byte GET_DATA_INDEX1						= 0x09 ;
const byte GET_SCHPOS0							= 0x0a ;
const byte GET_SCHPOS1							= 0x0b ;
const byte GET_SCHPOS2							= 0x0c ;
const byte GET_SCHPOS3							= 0x0d ;
const byte GET_CODE_DATA0						= 0x0e ;
const byte GET_CODE_DATA1						= 0x0f ;
const byte GET_CODE_DATA2						= 0x10 ;
const byte GET_CODE_DATA3						= 0x11 ;
const byte GET_CODE_DATA4						= 0x12 ;
const byte GET_CODE_DATA5						= 0x13 ;
const byte GET_CODE_DATA6						= 0x14 ;
const byte GET_CODE_DATA7						= 0x15 ;
const byte GET_MOTOR_STATUS						= 0x16 ;

//以下定义针对步进电机运行模式
const ushort NormalMode                         = 0x01;				//普通插补模式
const ushort SCanStart                          = 0x02;				//扫描开始
const ushort SCanEnd                            = 0x04;				//扫描终止
const ushort SCanRun                            = 0x06;				//扫描
const ushort IdleMode                           = 0x08;				//空程模式


//函数返回值
const int    CU_NO_ERR							= 0;				//无错误
const int    CU_SENDDATA_ERR					= -1;				//发送数据错误
const int    CU_RECVDATA_ERR					= -2;				//接收数据错误
const int    CU_PARA_MODE_ERR					= -3;				//参数错误
const int    CU_SNDBUF_NOT_ENOUGH				= -4;				//发送缓冲数据长度不足
const int    CU_DA12WAY_ERR						= -5;
const int    CU_PWMWAY_ERR						= -6;				//PWM通道超出范围
const int    CU_NO_DATA							= -7;				//无数据返回
const int    CU_NODEVICE						= -8;				//运动控制器设备不存在
const int    CU_LASER_CMD_ERR					= -9;				//激光命令错误
const int    CU_LASER_DATA_ERR					= -10;				//激光数据错误
const int	 CU_BUF_ISFULL						= -11;				//缓冲区满
const int	 CU_RECV_TIMEOUT					= -12;				//接收超时
const int	 CU_FILE_NOTEXIST					= -13;				//文件不存在

const ushort CLOCKWISE							= 1;
const ushort ANTICLOCKWISE						= 0;

const ushort SET_SETUPDATA						= 1;
const ushort CLR_SETUPDATA						= 0;

const byte   ST_EMSTOP							= 0;				//急停
const byte   ST_LASER_RST						= 1;				//激光器复位
const byte   ST_LASER_PT						= 2;				//激光器参考红外指令
const byte   ST_DATA							= 3;				//激光器功率数据指令
const byte   ST_LATCH							= 4;				//激光器功率锁存指令
const byte   ST_MO								= 5;				//MO开关指令
const byte   ST_AP								= 6;				//AP开关指令

//指令模式
const int    CMD_QUERY_MODE						= 0;				//查询模式
const int    CMD_BUF_MODE						= 1;				//下位机缓冲模式
const int    CMD_IMM_MODE						= 2;				//立即指令模式
const int    DTA_BUF_MODE						= 3;				//上位机缓冲模式

const uint	 SYS_FREQ_100M						= 100000000;
const uint	 SYS_FREQ_100M_CLK					= 10000000;
const uint   CONST_1S							= 1000000;
const uint   MAXPPS								= 100000;			//Luo ZW
const byte   DELAY_TRIG_AP						= 0;
const byte   DELAY_TRIG_IO						= 1;
const byte   DELAY_TRIG_PWM0					= 2;
const byte   DELAY_TRIG_PWM1					= 3;
const byte   DELAY_TRIG_PWM2					= 4;
const byte   DELAY_TRIG_PWM2I					= 5;
const byte   DELAY_TRIG_DAC						= 6;

const ushort CU_CORRECT_TAB						= 0x23;//6'd35		校正表

//暂停状态保存屏蔽位
#define	 PAUSE_MASK_IO							0x01
#define	 PAUSE_MASK_PWM0						0x02
#define	 PAUSE_MASK_PWM1						0x04
#define	 PAUSE_MASK_PWM2						0x08
#define	 PAUSE_MASK_LASER						0x10

#define  IO_BIT0								0x01
#define  IO_BIT1								0x02
#define  IO_BIT2								0x04
#define  IO_BIT3								0x08
#define  IO_BIT4								0x10
#define  IO_BIT5								0x20
#define  IO_BIT6								0x40
#define  IO_BIT7								0x80

#define	 LASER_LATCH							0x01
#define	 LASER_MO								0x02
#define	 LASER_AP								0x04

extern uint uiCULBufferLength;					//本地缓冲数据长度

#define MSG_LEN 512								// 消息长度，这里定长512
#define DRVBUF_SIZE 65536*140						// 驱动缓冲区长度：8M  //设计的大一点
#define BUFFER_SIZE 65536*7						// 控制卡缓冲区长度，先写死，以后在初始化函数中，通过与控制卡通信获得。

//uint buffer_index[4];							// 缓冲区index

typedef struct
{
    byte IOMask;								//IO屏蔽位
    byte IOStatus;								//IO位
    uint PWM0Freq;								//PWM0频率(Hz)
    ushort PWM0Ht;								//PWM0高脉冲时间（us）
    uint PWM1Freq;								//PWM1频率
    ushort PWM1Ht;								//PWM1高脉冲时间（us）
    uint PWM2Freq;								//PWM2频率（Hz）
    ushort PWM2Ht;								//PWM2高脉冲时间（us）
    byte LaserMask;								//激光信号屏蔽位
    byte LaserSignal;							//激光信号
    ushort SavedDataMask;						//信号屏蔽位
}CUSavedDataStruct;
/*
    IOMask			当某一位置1时，IOStatus中对应的该位生效，否则相应位无效
    LaserMask		当某一位置1时，LaserSignal中对应的该位生效，否则相应位无效
                    LaserSignal.0-LaserMask.0	Latch	锁存
                    LaserSignal.1-LaserMask.1	MO		主控振荡器开关
                    LaserSignal.2-LaserMask.2	AP		激光器开关
    SavedDataMask	当某一位置1时，对应的信号生效（SavedDataMask的优先级高于IOMask和LaserMask）
                    SavedDataMask.0				IOStatus
                    SavedDataMask.1				PWM0
                    SavedDataMask.2				PWM1
                    SavedDataMask.3				PWM2
                    SavedDataMask.4				LaserSignal
*/

typedef struct
{
    byte ip[4];
    byte mask[4];
    byte gate[4];
    byte mac[6];
    byte pad[12];
}CUIPdef,*pCUIPdef;

#define STATUS_EXT
#define STATUS_EXT2

#ifdef STATUS_EXT
    #ifdef STATUS_EXT2
        #define STATUS_LEN 64
    #else
        #define STATUS_LEN 36
    #endif
#else
    #define STATUS_LEN 24
#endif

typedef struct
{
    byte	StatusLen;					//本结构体长度，12，应用程序中不用
    byte	GPIOIN;						//IO输入
    byte	MotorStatus;
    byte	RunStatus;
    uint	RdFifoLen;					//主缓冲区数据长度，低24位为数据长度，高8位为输出端口的状态
    ushort	CurX;						//X轴坐标
    ushort	CurY;						//Y轴坐标
    ushort	CurZ;						//Z轴坐标
    ushort	CurH;						//辅助轴坐标
    uint	RotaryCount;				//编码器计数
    ushort	RotarySpeed;				//编码器速度
    ushort	RSP_DATA_TO_HOST;			//立即指令响应，在应用程序中不用
#ifdef STATUS_EXT
    uint    MotorX;
    uint    MotorY;
    uint    MotorZ;
#endif
#ifdef STATUS_EXT2
    uint    FlyingEndFlag;
    byte    Reserve[10];
#endif
}CUStatusdef,*pCUStatusdef;

/*	MotorStatus和RunStatus包含如下状态位
    MOTOIN_RUNNING	= RunStatus.7		电机运行状态	1：有电机等待运行 0：无电机等待运行
    MOTOIN_OVER		= RunStatus.6		电机运行状态	1：正在插补输出 0：输出完成
    SCH_OVER		= RunStatus.5		系统运行状态	1：正在插补输出 0：输出完成
    SYS_PAUSE		= RunStatus.4		系统暂停状态	1：暂停			0：运行
    SHSTATUS		= RunStatus.3		数字振镜状态	查看数字振镜的状态
    LASER_ST		= RunStatus.2-1		光纤激光器状态	查看光纤激光器的状态
    Z_HOME			= RunStatus.0		Z轴原点			1：在原点       0：在工位
    Z_LIMIT_M		= MotorStatus.7		Z轴限位-		1：负端端限位   0：在工位
    Z_LIMIT_P		= MotorStatus.6		Z轴限位+		1：正端端限位   0：在工位
    Y_HOME			= MotorStatus.5     Y轴原点
    Y_LIMIT_M		= MotorStatus.4		Y轴限位-
    Y_LIMIT_P		= MotorStatus.3     Y轴限位+
    X_HOME			= MotorStatus.2		X轴原点
    X_LIMIT_M		= MotorStatus.1		X轴限位-
    X_LIMIT_P		= MotorStatus.0		X轴限位+
*/
CUDRVE_EXPORT BOOL WINDLL CUSetCurCard(int curcard);
//CH：设置当前工作的板卡

CUDRVE_EXPORT BOOL WINDLL CUOpenDevice(int HIDNums=1);
//CH：RAWHID，打开多个HID
/*3  laser control
    函数功能:	打开控制器
    输入参数:	HIDNums				打开的板卡数量，最大5
    返回值:		实际打开的板卡数量
    调用示例：
        CUOpenDevice(2);//打开2张板卡
*/

CUDRVE_EXPORT void WINDLL CUCloseDevice();
/*1
    函数功能:	关闭控制器
    输入参数:	无
    输出参数:	无
    返回值:		无
    说明:
    调用示例：
CH：可以不实现
*/


CUDRVE_EXPORT BOOL WINDLL CUIsOpen();
/*2
    函数功能:	返回控制器是否打开的状态
    输入参数:	无
    输出参数:	无
    返回值:		0:控制器已打开 -1:控制未打开
    说明:
    调用示例：
CH：可以同开设备一样实现，或者不实现，常开状态。
*/

CUDRVE_EXPORT bool WINDLL CUReadData(uint data_length, byte* data);
/*
    函数功能:	从串口读取接收缓冲区的内容
    输入参数:	UINT data_length		读取的数据长度
                byte *data				数据起始指针
    输出参数:	无
    返回值:		无
    说明:
    调用示例:	byte*command = new byte[3];
                CUReadData(3, command);
                CUReadData(3, temp_data);
*/
CUDRVE_EXPORT int WINDLL CUSetImgPara(ushort width, ushort height, unsigned char pixspacex, unsigned char pixspacey, ushort mode);//2023-2-25
CUDRVE_EXPORT int WINDLL CUOutImg(byte *pdata, ushort startx, ushort starty);//2023-3-4

CUDRVE_EXPORT int WINDLL CUSetOpenDelayUs(uint DelayTimes, ushort mode);//2023-1-12
CUDRVE_EXPORT int WINDLL CUSetCloseDelayUs(uint DelayTimes, ushort mode);//2023-1-13
CUDRVE_EXPORT int WINDLL CUSetTuneDelayUs(uint DelayTimes, ushort mode);//2023-1-13
CUDRVE_EXPORT int WINDLL CUSetJumpDelayUs(uint DelayTimes, ushort mode);//2023-1-13

CUDRVE_EXPORT int WINDLL CUSetNullDelayUs(uint DelayTimes, ushort mode);//2
/*
    函数功能:	设置空延时
    输入参数:	uint DelayTimes			延时时间,单位为	10ns(CUSetNullDelay)
                                                        1us(CUSetNullDelayUs)
                ushort mode				指令模式,见指令模式列表

    输出参数:		返回值:		见函数返回值列表
    说明:
    调用示例：
CH：LASERCONTROL中没有什么内容，二处，其中一处应该没有什么，应该看上层，另一处，5000us*2，10ms,应该是开光延时什么的吧。
*/


CUDRVE_EXPORT int WINDLL CUSchSetSpeed(uint SchSpeed,ushort mode);
/*1
    函数功能:	设置振镜速度
    输入参数:	uint SchSpeed			振镜速度,单位pps(脉冲/秒)
                ushort mode				指令模式,见指令模式列表

    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
CH：LASERCONTROL中没有什么内容。只是调用，要看上层。
*/
CUDRVE_EXPORT int WINDLL CUSchJmpLinear(ushort DA16_X_DATA, ushort DA16_Y_DATA, ushort mode);
/*1
函数功能:	振镜直线跳转（不出光）
输入参数:	ushort DA16_X_DATA			x轴坐标
ushort DA16_Y_DATA			y轴坐标
ushort mode					指令模式,见指令模式列表

输出参数:	无
返回值:		见函数返回值列表
说明:
调用示例：
CH：LASERCONTROL中没有什么内容。只是调用，要看上层。	应该是在固件中实现的，如果在软件中实现，就有点意思了。
*/

CUDRVE_EXPORT int WINDLL CUSchOutLinear(ushort DA16_X_DATA, ushort DA16_Y_DATA, ushort mode);
/*1
    函数功能:	振镜直线插补
    输入参数:	ushort DA16_X_DATA			x轴坐标
                ushort DA16_Y_DATA			y轴坐标
                ushort mode					指令模式,见指令模式列表

    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
CH：LASERCONTROL中没有什么内容。只是调用，要看上层。	应该是在固件中实现的，如果在软件中实现，就有点意思了。
*/



CUDRVE_EXPORT int WINDLL CUIOOut(byte IOMask, byte IOstatus, ushort mode);
/*2
    函数功能:	IO输出
    输入参数:	byte IOMask							IO允许,与8位IO一一对应,1为允许改变该IO状态,0为禁止改变该IO状态
                byte IOstatus						IO值,8位值,与8位IO一一对应,1对应输出高电平,0对应输出低电平
                ushort mode							指令模式,见指令模式列表

    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
CH：这个也只是调用，而且调用应该有错，0的时候不允许，这个就有点没有必要了，应该是都允许吧。
*/

CUDRVE_EXPORT int WINDLL CULaserOut(byte LaserCtrl,byte LaserPower, ushort mode);
/*4
    函数功能:	激光输出控制
    输入参数:	byte LaserCtrl						IO允许,与8位IO一一对应,1为允许改变该IO状态,0为禁止改变该IO状态
                byte LaserPower						IO值,8位值,与8位IO一一对应,1对应输出高电平,0对应输出低电平
                ushort mode							指令模式,见指令模式列表

    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
CH：四处在同一函数中调用，有干货。LaserCtrl的解释是不正确的。应该是不同的指令，如LATCH等。
*/

CUDRVE_EXPORT int WINDLL CUSetRedLight(byte rol, ushort mode);
CUDRVE_EXPORT int WINDLL CURedLightStart();
/*1 PathPlan
    函数功能:	通过快速指令启动红光边框扫描
    输入参数:	无
    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CURedLightEnd();
/*1 PaghPlan
    函数功能:	通过快速指令停止红光边框扫描
    输入参数:	无
    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/


CUDRVE_EXPORT int WINDLL CUMotorOutXY(uint x, uint y, uint MotorSpeedCorner, uint MotorSpeedMax, uint DecPoint, byte MotorMode, ushort mode);
/*1
    函数功能:	步进电机独立输出
    输入参数:	所有参数功能及意义同CUMotorOutXYZ
    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CUMotorOutXYZ(uint x, uint y, uint z, uint MotorSpeedCorner,uint MotorSpeedMax,uint DecPoint, byte MotorMode, ushort mode);
/*1
    函数功能:	步进电机独立输出
    输入参数:	uint x								X轴坐标值,实际有效位数为24位
                uint y								Y轴坐标值,实际有效位数为24位
                uint z								Y轴坐标值,实际有效位数为24位
                uint MotorSpeed						联动模式下，每个节点的速度
                uint MotorSpeedMax					联动模式下，当前线段的最大速度
                uint DecPoint						联动模式下，当前线段从起点开始走该距离后，开始减速
                byte MotorMode						0～3bit，联动模式下，运动模式（以上四个参数，在回原点和单轴运动时，直接设为0即可）
                                                    4～6bit，增量模式设置 1为增量模式，x/y/z为电机运动的距离，0为绝对模式，x/y/z为电机的坐标
                ushort mode							指令模式,见指令模式列表

    输出参数:	无
    返回值:		见函数返回值列表
    说明:		在绝对模式下，所有的坐标都为相对原点的正值，不允许为负值，
                在增量模式下，距离允许为负值，负的距离即反向运动，负距离的计算方法为：x/y/z=0xffffff-要运动的距离的绝对值
    调用示例：  要反向运动10000脉冲，即向原点方向运动10000（0x2710）个脉冲，则x/y/z = 0xffffff - 0x2710 = 0xffd8ef
                CUMotorOutXYZ(	0xffd8ef,0xffd8ef,0xffd8ef,
                                0,0,0,
                                0x70,
                                DTA_BUF_MODE
                            );
*/

CUDRVE_EXPORT int WINDLL CUMotorOutZ(uint z,ushort ZDir,ushort mode);
/*1
    函数功能:	Z轴步进电机输出
    输入参数:	uint z								Z轴步数
                ushort ZDir							Z轴方向，1顺时针，0逆时针
                ushort RunMode						见步进电机运行模式表
                ushort mode							指令模式,见指令模式列表

    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CUMotorGoHome(	ushort	xyz,
                            ushort	home_stop_dist,
                            uint	home_max_dist,
                            ushort	mode);
/*1
    函数功能:	步进电机回原点
    输入参数:	uint	xyz								指定回原点的轴,0x01为X轴,0x02为Y轴,0x04为Z轴，0x07为三轴同时回原点
                ushort	home_stop_dist					在缓停模式下，设定各轴过了原点传感器后允许运行的脉冲数
                uint	home_max_dist					回原点时指定允许运行的最大脉冲数
                ushort	mode							指令模式,见指令模式列表

    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/


CUDRVE_EXPORT int WINDLL CUMotorGoHomeLogic(ushort xyz,ushort mode);
/*1
    函数功能:	步进电机内部逻辑回原点，机械保持不变
    输入参数:	uint xyz							指定回原点的轴,0x01为X轴,0x02为Y轴,0x04为Z轴，0x07为三轴同时回原点（DTA_BUF_MODE模式时）
                ushort mode							指令模式,见指令模式列表

    输出参数:	无
    返回值:		见函数返回值列表
    说明:		调用该函数，仅仅将当前点设为原点，实际电机并无动作
                当mode == CMD_IMM_MODE时，三轴需要分别调用，才能正确回原点
                当mode == DTA_BUF_MODE时，三轴可以同时回原点
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CUMotorStop(ushort xyz);//1
CUDRVE_EXPORT int WINDLL CUMotorSetSpeed(uint SSPEED,
                            uint ESPEED,
                            uint ACC,
                            uint ESPEED_Idle,
                            uint ACC_IDLE,
                            ushort mode);
/*1
    函数功能:	步进电机速度设置
    输入参数:	uint SSPEED							起始速度(最小速度)
                uint ESPEED							终止速度(最大速度)
                uint ACC							加速度
                uint ESPEED_Idle					空程终止速度(最大速度)
                uint ACC_IDLE						空程加速度
                ushort mode							指令模式,见指令模式列表

    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CUMotorRunMode(ushort Motor_Mode, ushort mode);
/*1
    函数功能:	步进电机速度模式选择
    输入参数:	ushort Motor_Mode					速度模式,MOTOR_SPEED为正常运行模式,IDLE_SPEED为空程模式
                ushort mode							指令模式,见指令模式列表

    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CUWriteBuf();
/*1
    函数功能:	在DTA_BUF_MODE(上位机缓冲模式)下,将上位机缓冲数据传输到控制器
    输入参数:	无
    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CUBufEnd();
/*1
    函数功能:	终止当前任务缓冲
    输入参数:	无
    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CUSetPWM(ushort PWMWay,uint Freq, byte duty,ushort mode,BOOL Reverse = false);
/*1
    函数功能:	设置PWM
    输入参数:	ushort PWMWay					PWM通道,有效值为PWM0/PWM1/PWM2
                uint Freq						频率值,单位为HZ
                byte duty						占空比,为0~100,标识占空比为0%~100%
                ushort mode						指令模式,见指令模式列表
    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/


CUDRVE_EXPORT int WINDLL CUSetPWMUs(ushort PWMWay, uint Freq, uint HighPulseTimeUs, ushort mode, BOOL Reverse = false);
/*9
    函数功能:	设置PWM
    输入参数:	ushort PWMWay					PWM通道,有效值为PWM0/PWM1/PWM2
                uint Freq						频率值,单位为HZ
                ushort HighPulseTimeUs			高电平时间，单位us
                ushort mode						指令模式,见指令模式列表
    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
初始化卡中:CUSetPWMUs(PWM2, 5000, 1, CMD_IMM_MODE)
关闭卡中:同上设置
其他在关光中五个:同上设置
一个专门的设置中:是原样调用,需要看更高层

*/

CUDRVE_EXPORT int WINDLL CUGetStatus(CUStatusdef **CUStatus);
/*7
    函数功能:	读取状态
    输入参数:	CUStatusdef **CUStatus		返回状态缓冲区指针
    输出参数:	无
    返回值:		见函数返回值列表
    说明:		本指令为立即指令
    调用示例：
    CUStatusdef *CUStatus = null;
    CUGetStatus(&CUStatus);

*/

CUDRVE_EXPORT int WINDLL CUSetup(uint SetupData, ushort SetupCmd, ushort mode);
/*2
    函数功能:	系统设置
    输入参数:	uint SetupData：		设置参数（默认值0x0000）
                BIT0：					0-数字振镜，1-模拟振镜	缺省为1
                BIT1:					0-PWM0禁止，1-PWM0允许	缺省为0
                BIT2：					0-PWM1禁止，1-PWM1允许	缺省为0
                BIT3：					0-PWM2禁止，1-PWM2允许	缺省为1
                BIT4:					0-禁止振镜时钟，1-允许振镜时钟
                BIT5：					0-飞动下降沿触发 1-上升沿触发
                BIT6:					0-不启用失真修正，1-启用失真修正
                BIT7:					0-禁止网络复位， 1-允许网络复位

                BIT8					步进电机X轴方向配置
                BIT9					步进电机Y轴方向配置
                BIT10					步进电机Z轴方向配置
                BIT13～BIT11			000		单轴模式
                                        001		回原点
                                        010		XY两轴轴联动，Z单轴
                                        011		XYZ三轴联动
                BIT14					0       X轴低限位
                                        1		X轴高限位
                BIT15					0		Y轴低限位
                                        1		Y轴高限位
                BIT16					0		Z轴低限位
                                        1		Z轴高限位
                BIT21					0		禁止激光自动延时关闭
                                        1		允许激光自动延时关闭

                BBIT17~IT31：			暂未定义
                ushort SetupCmd			0 - SetupData相应位写1时，控制器中该位被清零
                                        1-	SetupData相应位写1时，控制器中该位被置位

                ushort mode				指令模式,见指令模式列表
    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CUPausePara(CUSavedDataStruct lCUSavedDataStruct,ushort mode);
/*2
    函数功能:	暂停振镜插补过程
    输入参数:	CUSavedDataStruct lCUSavedDataStruct	详见CUSavedDataStruct的定义
    输出参数:
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CUPause();
/*1
    函数功能:	暂停振镜插补过程
    输入参数:
    输出参数:
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CUReset();
/*1
    函数功能:	系统复位
    输入参数:	无
    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CUCancel();
/*2
    函数功能:	取消当前运动过程
    输入参数:	无
    输出参数:	无
    返回值:		见函数返回值列表
    说明:
    调用示例：
*/
CUDRVE_EXPORT uint WINDLL CUGetBufferLength();
/*1
    函数功能:	获取本地缓冲区已用长度
    输入参数:	无
    输出参数:	无
    返回值:		缓冲区已用长度，单位WORDS
    说明:
    调用示例：
*/
CUDRVE_EXPORT BOOL WINDLL CUBufferIsNotFull();
/*1
    函数功能:	返回本地缓冲区使用状态，
    输入参数:	无
    输出参数:	无
    返回值:		true 缓冲区未满 false 缓冲区已满
    说明:
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CUBufStart(void);
/*1
    函数功能:	标记缓冲器指令的开始
    输入参数:	无
    输出参数:	无
    返回值:
    说明:
    调用示例：
*/


CUDRVE_EXPORT int WINDLL CUWaitHome(uint interval,
                       uint uiTimeout,
                       BOOL XHomeEn,
                       byte XHomeLevel,
                       BOOL YHomeEn,
                       byte YHomeLevel,
                       BOOL ZHomeEn,
                       byte ZHomeLevel);
/*1
    函数功能:	等待电机完成回原点的动作
    输入参数:	uint interval	循环间隔，一般可设为20（ms）,即内部查询状态的周期
                uint uiTimeout	等待超时时间，比如10（s），该参数大小依赖于前面发送的数据的具体内容，
                BOOL XHomeEn	允许X轴 true：允许 false:禁止
                byte XHomeLevel X轴原点检测方式，1：高电平有效 0：低电平有效
                BOOL YHomeEn	允许Y轴 true：允许 false:禁止
                byte YHomeLevel Y轴原点检测方式，1：高电平有效 0：低电平有效
                BOOL ZHomeEn	允许Z轴 true：允许 false:禁止
                byte ZHomeLevel Z轴原点检测方式，1：高电平有效 0：低电平有效
    一般该值可以设很大
    输出参数:	无
    返回值:		见函数返回值列表
    说明:		该函数在新版固件中不再使用，新版固件中，如果电机回原点在连续的指令序列中间，则无需等待，
                如果为单独的一个指令序列（即单独的回原点动作），则可直接调用CUWaitJobEnd
    调用示例：
*/

CUDRVE_EXPORT void WINDLL CUWriteBufEnable(BOOL Enable);
/*1
    函数功能:	调用该函数后，动态库自动判断写缓冲是否满，满则立即向板卡发送
    输入参数:	BOOL Enable  true  自动判断缓冲满并发送
                             false 程序判断缓冲满，并立即调用CUWriteBuf函数发送指令
    输出参数:	无
    返回值:		见函数返回值列表
    说明:		该指令可以在任何地方调用，调用后立即生效
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CUBufFill(void);
/*1
    函数功能:	调用该函数后，将强制填充板卡缓冲区，使板卡中的所有指令立即执行
    输入参数:	无
    输出参数:	无
    返回值:		见函数返回值列表
    说明:       某些情况下，由于指令的数据量很小，直接发送到板卡上后，板卡缓冲的页面没有填充满，将会等待该页面填满后才会执行该页面中的指令。
                为解决这种情况，该函数则可直接填充满该页面，导致该页面的指令立即执行
                调用该函数之情，确保所有需要执行的指令已经发送到板卡，如果指令无法填满一个写缓冲而自动发送，则直接调用CUWriteBuf发送
    调用示例：
*/

CUDRVE_EXPORT int WINDLL CUCorrectTableInit(ushort line, ushort column, ushort x, ushort y);
/*1
    函数功能:	校正表初始化
    输入参数:	ushort line			行数 0～64 其中32为中心点
                ushort column		列数 0～64 其中32为中心点
                ushort x			每个节点的X轴坐标
                ushort y			每个节点的Y周坐标
    输出参数:	无
    返回值:		见函数返回值列表
    说明:		本表共有65行65列，其中0～31对应负轴部分，33～64对应正轴部分，32为坐标轴
    调用示例：
        for(int i=0;i<65;i++)
        {
            for(int j=0;j<65;j++)
            {
                CUCorrectTableInit(i,j,j*1024,i*1024);
            }
        }
*/

extern int WriteDataWithMode(ushort mode, byte* data, uint data_length=7);
/*
    函数功能:	写入数据
    输入参数:	ushort mode				指令模式
                uint data_length		数据长度
                byte* data				数据本体
    输出参数:	无
    返回值:		见函数返回值列表
    说明:		按照mode不同向缓冲区中写入数据或直接发送指令，
                如果缓冲区大小不能支持本次写入则将缓冲区数据
                写入串口并将缓冲区清空后将本次的数据写入缓冲区
    调用示例:
        byte *data = new byte[20];
        ... PUT DATA INTO data
        WriteDataToWithMode(CMD_BUF_MODE, 20, data);
*/

extern int WriteDataToBufer(uint data_length, byte* data);
/*
    函数功能:	写入数据
    输入参数:	uint data_length		数据长度
                byte* data				数据本体
    输出参数:	无
    返回值:		见函数返回值列表
    说明:		向缓冲区中写入数据，如果缓冲区大小不能支持本次写入则将缓冲区数据
                写入串口并将缓冲区清空后将本次的数据写入缓冲区
    调用示例:
        byte *data = new byte[20];
        ... PUT DATA INTO data
        WriteDataToBuffer(20, data);
*/

extern void UnsignedShortTobyte(ushort origin, byte* data, int data_index);

extern void UnsignedIntTobyte(uint origin, byte* data, int data_index);

extern void IntTobyte(int origin, byte* data, int data_index);

#endif // CUDRVE_H
