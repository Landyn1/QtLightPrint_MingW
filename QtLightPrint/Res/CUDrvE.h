#pragma once

#ifdef CUDRVE_EXPORTS 
#define CUDRVE_API __declspec(dllexport)
#else
#define CUDRVE_API __declspec(dllimport)
#endif

#define WINDLL __stdcall

#define ushort unsigned short
#define byte unsigned char
#define uint unsigned int

#define BOOL int

//Luo ZW
const byte DA16_XY 							= 0x00;//6'd0		��ֱ�߲岹ָ��
const byte DA16_CIRCLE 							= 0x01;//6'd1		��Բ���岹ָ��
const byte LASER 	 							= 0x02;//6'd2		�������ָ��
const byte MOTOR_RUN							= 0x03;//6'd3		��������岹ָ��
const byte LASER_DLY							= 0x04;//6'd4		��������ʱ�Զ��ر�
const byte MOTOR_SCAN							= 0x05;//6'd5		ɨ��ģʽ
const byte MOTOR_HOME							= 0x06;//6'd6 		��ԭ��ָ��
const byte MOTOR_SPEED							= 0x07;//6'd7		���ò�������ٶ�ָ��
const byte MOTOR_SPEED_CH						= 0x08;//6'd8		���ò�������ճ��ٶ�ָ��
const byte PWM0									= 0x09;//6'd9		PWM0��ʶ
const byte PWM1									= 0x0a;//6'd10		PWM1��ʶ
const byte PWM2									= 0x0b;//6'd11		PWM2��ʶ�����˼�����ר�ã�
const byte SET_DDA_DELAY						= 0x0c;//6'd12		�������˶�����������ʱ
const byte SET_NUL_DELAY						= 0x0d;//6'd13		�������⻺��ָ������ʱ
const byte NULL_DLY								= 0x0e;//6'd14
const byte MOTOR_STOP							= 0x0f;//6'd15;
const byte ROTARY_VSPD							= 0x10;//6'd16
const byte MOTOR_XY								= 0x11;//6'd17
const byte RATIO_SET							= 0x12;//6'd18
const byte DA16_XYZ								= 0x13;//6'd0		��ֱ�߲岹ָ��

const byte CU_SETUP_SET							= 0x14;//6'd20		ϵͳ����
const byte CU_PAUSE								= 0x15;//6'd21		����ָͣ��
const byte MOTOR_PRE							= 0x16;//6'd22
const byte SET_DATA_INDEX						= 0x17;//6'd23		������������
const byte SET_EVENT_TIMES						= 0x18;//6'd24
const byte SET_EVENT_CLOCKS						= 0x19;//6'd25
const byte CU_SETUP_CLR							= 0x1a;//6'd26		�������ģʽ
const byte CU_CORRECT_SET						= 0x1b;//6'd27		����������ָ��
const byte CU_REPEAT_NUMS						= 0x1c;//6'd28
const byte CU_REPEAT_DATA						= 0x1d;//6'd29
const byte CU_FLYING_FLAG						= 0x1e;//6'd30
const byte SET_OUTPUT							= 0x1f;//6'd31		IO���ָ��
const byte SET_DACOUT							= 0x20;//6'd32		����ģ����� ����ģ�⹦�ʵ���
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

const byte IMG_PARA = 0x3a;// new 23-2-25 ����ͼ��ӹ�����

const byte JUMP_DLY = 0x3c;// new 23-1-13
const byte TUNE_DLY = 0x3d;// new 23-1-12
const byte OPEN_DLY = 0x3e;// new 23-1-9
const byte CLOSE_DLY = 0x3f;// new 23-1-12


const byte  NULLOP = 0x40;//��ָ��

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

//���¶�����Բ����������ģʽ
const ushort NormalMode                         = 0x01;				//��ͨ�岹ģʽ
const ushort SCanStart                          = 0x02;				//ɨ�迪ʼ
const ushort SCanEnd                            = 0x04;				//ɨ����ֹ
const ushort SCanRun                            = 0x06;				//ɨ��
const ushort IdleMode                           = 0x08;				//�ճ�ģʽ


//��������ֵ
const int    CU_NO_ERR							= 0;				//�޴���
const int    CU_SENDDATA_ERR					= -1;				//�������ݴ���
const int    CU_RECVDATA_ERR					= -2;				//�������ݴ���
const int    CU_PARA_MODE_ERR					= -3;				//��������
const int    CU_SNDBUF_NOT_ENOUGH				= -4;				//���ͻ������ݳ��Ȳ���
const int    CU_DA12WAY_ERR						= -5;
const int    CU_PWMWAY_ERR						= -6;				//PWMͨ��������Χ
const int    CU_NO_DATA							= -7;				//�����ݷ���
const int    CU_NODEVICE						= -8;				//�˶��������豸������
const int    CU_LASER_CMD_ERR					= -9;				//�����������
const int    CU_LASER_DATA_ERR					= -10;				//�������ݴ���
const int	 CU_BUF_ISFULL						= -11;				//��������
const int	 CU_RECV_TIMEOUT					= -12;				//���ճ�ʱ
const int	 CU_FILE_NOTEXIST					= -13;				//�ļ�������

const ushort CLOCKWISE							= 1;
const ushort ANTICLOCKWISE						= 0;

const ushort SET_SETUPDATA						= 1;
const ushort CLR_SETUPDATA						= 0;

const byte   ST_EMSTOP							= 0;				//��ͣ
const byte   ST_LASER_RST						= 1;				//��������λ
const byte   ST_LASER_PT						= 2;				//�������ο�����ָ��
const byte   ST_DATA							= 3;				//��������������ָ��
const byte   ST_LATCH							= 4;				//��������������ָ��
const byte   ST_MO								= 5;				//MO����ָ��
const byte   ST_AP								= 6;				//AP����ָ��

//ָ��ģʽ
const int    CMD_QUERY_MODE						= 0;				//��ѯģʽ			
const int    CMD_BUF_MODE						= 1;				//��λ������ģʽ
const int    CMD_IMM_MODE						= 2;				//����ָ��ģʽ
const int    DTA_BUF_MODE						= 3;				//��λ������ģʽ

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

const ushort CU_CORRECT_TAB						= 0x23;//6'd35		У����

//��ͣ״̬��������λ
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

extern uint uiCULBufferLength;					//���ػ������ݳ���

#define MSG_LEN 512								// ��Ϣ���ȣ����ﶨ��512
#define DRVBUF_SIZE 65536*140						// �������������ȣ�8M  //��ƵĴ�һ��
#define BUFFER_SIZE 65536*7						// ���ƿ����������ȣ���д�����Ժ��ڳ�ʼ�������У�ͨ������ƿ�ͨ�Ż�á�

uint buffer_index[4];							// ������index

typedef struct 
{
    byte IOMask;								//IO����λ
    byte IOStatus;								//IOλ
    uint PWM0Freq;								//PWM0Ƶ��(Hz)
    ushort PWM0Ht;								//PWM0������ʱ�䣨us��
    uint PWM1Freq;								//PWM1Ƶ��
    ushort PWM1Ht;								//PWM1������ʱ�䣨us��
    uint PWM2Freq;								//PWM2Ƶ�ʣ�Hz��
    ushort PWM2Ht;								//PWM2������ʱ�䣨us��
    byte LaserMask;								//�����ź�����λ
    byte LaserSignal;							//�����ź�
    ushort SavedDataMask;						//�ź�����λ
}CUSavedDataStruct;
/*
	IOMask			��ĳһλ��1ʱ��IOStatus�ж�Ӧ�ĸ�λ��Ч��������Ӧλ��Ч
	LaserMask		��ĳһλ��1ʱ��LaserSignal�ж�Ӧ�ĸ�λ��Ч��������Ӧλ��Ч
					LaserSignal.0-LaserMask.0	Latch	����
					LaserSignal.1-LaserMask.1	MO		������������
					LaserSignal.2-LaserMask.2	AP		����������
	SavedDataMask	��ĳһλ��1ʱ����Ӧ���ź���Ч��SavedDataMask�����ȼ�����IOMask��LaserMask��
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
	byte	StatusLen;					//���ṹ�峤�ȣ�12��Ӧ�ó����в���
	byte	GPIOIN;						//IO����
	byte	MotorStatus;				
	byte	RunStatus;					
	uint	RdFifoLen;					//�����������ݳ��ȣ���24λΪ���ݳ��ȣ���8λΪ����˿ڵ�״̬
	ushort	CurX;						//X������
	ushort	CurY;						//Y������
	ushort	CurZ;						//Z������
	ushort	CurH;						//����������
	uint	RotaryCount;				//����������
	ushort	RotarySpeed;				//�������ٶ�
	ushort	RSP_DATA_TO_HOST;			//����ָ����Ӧ����Ӧ�ó����в���
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

/*	MotorStatus��RunStatus��������״̬λ
	MOTOIN_RUNNING	= RunStatus.7		�������״̬	1���е���ȴ����� 0���޵���ȴ�����
	MOTOIN_OVER		= RunStatus.6		�������״̬	1�����ڲ岹��� 0��������
	SCH_OVER		= RunStatus.5		ϵͳ����״̬	1�����ڲ岹��� 0��������
	SYS_PAUSE		= RunStatus.4		ϵͳ��ͣ״̬	1����ͣ			0������
	SHSTATUS		= RunStatus.3		������״̬	�鿴�����񾵵�״̬
	LASER_ST		= RunStatus.2-1		���˼�����״̬	�鿴���˼�������״̬
	Z_HOME			= RunStatus.0		Z��ԭ��			1����ԭ��       0���ڹ�λ
	Z_LIMIT_M		= MotorStatus.7		Z����λ-		1�����˶���λ   0���ڹ�λ
	Z_LIMIT_P		= MotorStatus.6		Z����λ+		1�����˶���λ   0���ڹ�λ
	Y_HOME			= MotorStatus.5     Y��ԭ��
	Y_LIMIT_M		= MotorStatus.4		Y����λ-
	Y_LIMIT_P		= MotorStatus.3     Y����λ+
	X_HOME			= MotorStatus.2		X��ԭ��
	X_LIMIT_M		= MotorStatus.1		X����λ-
	X_LIMIT_P		= MotorStatus.0		X����λ+
*/
CUDRVE_API BOOL WINDLL CUSetCurCard(int curcard);
//CH�����õ�ǰ�����İ忨

CUDRVE_API int WINDLL CUOpenDevice(int HIDNums=1);
//CH��RAWHID���򿪶��HID
/*3  laser control
	��������:	�򿪿�����
	�������:	HIDNums				�򿪵İ忨���������5
	����ֵ:		ʵ�ʴ򿪵İ忨����
	����ʾ����
		CUOpenDevice(2);//��2�Ű忨
*/

CUDRVE_API void WINDLL CUCloseDevice();
/*1
	��������:	�رտ�����
	�������:	��
	�������:	��
	����ֵ:		��
	˵��:		
	����ʾ����
CH�����Բ�ʵ��
*/


CUDRVE_API BOOL WINDLL CUIsOpen();
/*2 
	��������:	���ؿ������Ƿ�򿪵�״̬
	�������:	��
	�������:	��
	����ֵ:		0:�������Ѵ� -1:����δ��
	˵��:		
	����ʾ����
CH������ͬ���豸һ��ʵ�֣����߲�ʵ�֣�����״̬��
*/

CUDRVE_API int WINDLL CUReadData(uint data_length, byte* data);
/*
	��������:	�Ӵ��ڶ�ȡ���ջ�����������
	�������:	UINT data_length		��ȡ�����ݳ���
				byte *data				������ʼָ��
	�������:	��
	����ֵ:		��
	˵��:		
	����ʾ��:	byte*command = new byte[3];
				CUReadData(3, command);
*/
CUDRVE_API int WINDLL CUSetImgPara(ushort width, ushort height, unsigned char pixspacex, unsigned char pixspacey, ushort mode);//2023-2-25
CUDRVE_API int WINDLL CUOutImg(byte *pdata, ushort startx, ushort starty);//2023-3-4

CUDRVE_API int WINDLL CUSetOpenDelayUs(uint DelayTimes, ushort mode);//2023-1-12
CUDRVE_API int WINDLL CUSetCloseDelayUs(uint DelayTimes, ushort mode);//2023-1-13
CUDRVE_API int WINDLL CUSetTuneDelayUs(uint DelayTimes, ushort mode);//2023-1-13
CUDRVE_API int WINDLL CUSetJumpDelayUs(uint DelayTimes, ushort mode);//2023-1-13

CUDRVE_API int WINDLL CUSetNullDelayUs(uint DelayTimes, ushort mode);
/*//2
	��������:	���ÿ���ʱ
	�������:	uint DelayTimes			��ʱʱ��,��λΪ	10ns(CUSetNullDelay)
														1us(CUSetNullDelayUs)
				ushort mode				ָ��ģʽ,��ָ��ģʽ�б�
				
	�������:		����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
CH��LASERCONTROL��û��ʲô���ݣ�����������һ��Ӧ��û��ʲô��Ӧ�ÿ��ϲ㣬��һ����5000us*2��10ms,Ӧ���ǿ�����ʱʲô�İɡ�
*/


CUDRVE_API int WINDLL CUSchSetSpeed(uint SchSpeed,ushort mode/*,int hidnum=0*/);
/*1
	��������:	�������ٶ�
	�������:	uint SchSpeed			���ٶ�,��λpps(����/��)
				ushort mode				ָ��ģʽ,��ָ��ģʽ�б�
				
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
CH��LASERCONTROL��û��ʲô���ݡ�ֻ�ǵ��ã�Ҫ���ϲ㡣	
*/
CUDRVE_API int WINDLL CUSchJmpLinear(ushort DA16_X_DATA, ushort DA16_Y_DATA, ushort mode);
/*1
��������:	��ֱ����ת�������⣩
�������:	ushort DA16_X_DATA			x������
ushort DA16_Y_DATA			y������
ushort mode					ָ��ģʽ,��ָ��ģʽ�б�

�������:	��
����ֵ:		����������ֵ�б�
˵��:
����ʾ����
CH��LASERCONTROL��û��ʲô���ݡ�ֻ�ǵ��ã�Ҫ���ϲ㡣	Ӧ�����ڹ̼���ʵ�ֵģ�����������ʵ�֣����е���˼�ˡ�
*/

CUDRVE_API int WINDLL CUSchOutLinear(ushort DA16_X_DATA, ushort DA16_Y_DATA, ushort mode/*,int hidnum=0*/);
/*1
	��������:	��ֱ�߲岹
	�������:	ushort DA16_X_DATA			x������
				ushort DA16_Y_DATA			y������
				ushort mode					ָ��ģʽ,��ָ��ģʽ�б�
				
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
CH��LASERCONTROL��û��ʲô���ݡ�ֻ�ǵ��ã�Ҫ���ϲ㡣	Ӧ�����ڹ̼���ʵ�ֵģ�����������ʵ�֣����е���˼�ˡ�
*/



CUDRVE_API int WINDLL CUIOOut(byte IOMask, byte IOstatus, ushort mode/*,int hidnum=0*/);
/*2
	��������:	IO���
	�������:	byte IOMask							IO����,��8λIOһһ��Ӧ,1Ϊ����ı��IO״̬,0Ϊ��ֹ�ı��IO״̬
				byte IOstatus						IOֵ,8λֵ,��8λIOһһ��Ӧ,1��Ӧ����ߵ�ƽ,0��Ӧ����͵�ƽ
				ushort mode							ָ��ģʽ,��ָ��ģʽ�б�
				
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
CH�����Ҳֻ�ǵ��ã����ҵ���Ӧ���д�0��ʱ������������е�û�б�Ҫ�ˣ�Ӧ���Ƕ�����ɡ�
*/

CUDRVE_API int WINDLL CULaserOut(byte LaserCtrl,byte LaserPower, ushort mode/*,int hidnum=0*/);
/*4
	��������:	�����������
	�������:	byte LaserCtrl						IO����,��8λIOһһ��Ӧ,1Ϊ����ı��IO״̬,0Ϊ��ֹ�ı��IO״̬
				byte LaserPower						IOֵ,8λֵ,��8λIOһһ��Ӧ,1��Ӧ����ߵ�ƽ,0��Ӧ����͵�ƽ
				ushort mode							ָ��ģʽ,��ָ��ģʽ�б�
				
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
CH���Ĵ���ͬһ�����е��ã��иɻ���LaserCtrl�Ľ����ǲ���ȷ�ġ�Ӧ���ǲ�ͬ��ָ���LATCH�ȡ�
*/

CUDRVE_API int WINDLL CUSetRedLight(byte rol, ushort mode);

CUDRVE_API int WINDLL CURedLightStart();
/*1 PathPlan
	��������:	ͨ������ָ���������߿�ɨ��
	�������:	��
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/

CUDRVE_API int WINDLL CURedLightEnd();
/*1 PaghPlan
	��������:	ͨ������ָ��ֹͣ���߿�ɨ��
	�������:	��
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/


CUDRVE_API int WINDLL CUMotorOutXY(uint x, uint y, uint MotorSpeedCorner, uint MotorSpeedMax, uint DecPoint, byte MotorMode, ushort mode);
/*1
	��������:	��������������
	�������:	���в������ܼ�����ͬCUMotorOutXYZ
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/

CUDRVE_API int WINDLL CUMotorOutXYZ(uint x, uint y, uint z, uint MotorSpeedCorner,uint MotorSpeedMax,uint DecPoint, byte MotorMode, ushort mode);
/*1
	��������:	��������������
	�������:	uint x								X������ֵ,ʵ����Чλ��Ϊ24λ
				uint y								Y������ֵ,ʵ����Чλ��Ϊ24λ
				uint z								Y������ֵ,ʵ����Чλ��Ϊ24λ
				uint MotorSpeed						����ģʽ�£�ÿ���ڵ���ٶ�
				uint MotorSpeedMax					����ģʽ�£���ǰ�߶ε�����ٶ�
				uint DecPoint						����ģʽ�£���ǰ�߶δ���㿪ʼ�߸þ���󣬿�ʼ����
				byte MotorMode						0��3bit������ģʽ�£��˶�ģʽ�������ĸ��������ڻ�ԭ��͵����˶�ʱ��ֱ����Ϊ0���ɣ�
													4��6bit������ģʽ���� 1Ϊ����ģʽ��x/y/zΪ����˶��ľ��룬0Ϊ����ģʽ��x/y/zΪ���������
				ushort mode							ָ��ģʽ,��ָ��ģʽ�б�
				
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		�ھ���ģʽ�£����е����궼Ϊ���ԭ�����ֵ��������Ϊ��ֵ��
				������ģʽ�£���������Ϊ��ֵ�����ľ��뼴�����˶���������ļ��㷽��Ϊ��x/y/z=0xffffff-Ҫ�˶��ľ���ľ���ֵ
	����ʾ����  Ҫ�����˶�10000���壬����ԭ�㷽���˶�10000��0x2710�������壬��x/y/z = 0xffffff - 0x2710 = 0xffd8ef
				CUMotorOutXYZ(	0xffd8ef,0xffd8ef,0xffd8ef,
								0,0,0,
								0x70,
								DTA_BUF_MODE
							);
*/

CUDRVE_API int WINDLL CUMotorOutZ(uint z,ushort ZDir,ushort mode);
/*1
	��������:	Z�Ჽ��������
	�������:	uint z								Z�Ჽ��
				ushort ZDir							Z�᷽��1˳ʱ�룬0��ʱ��
				ushort RunMode						�������������ģʽ��
				ushort mode							ָ��ģʽ,��ָ��ģʽ�б�
				
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/

CUDRVE_API int WINDLL CUMotorGoHome(	ushort	xyz, 
							ushort	home_stop_dist,
							uint	home_max_dist,
							ushort	mode);
/*1
	��������:	���������ԭ��
	�������:	uint	xyz								ָ����ԭ�����,0x01ΪX��,0x02ΪY��,0x04ΪZ�ᣬ0x07Ϊ����ͬʱ��ԭ��
				ushort	home_stop_dist					�ڻ�ͣģʽ�£��趨�������ԭ�㴫�������������е�������
				uint	home_max_dist					��ԭ��ʱָ���������е����������
				ushort	mode							ָ��ģʽ,��ָ��ģʽ�б�
				
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/


CUDRVE_API int WINDLL CUMotorGoHomeLogic(ushort xyz,ushort mode);
/*1
	��������:	��������ڲ��߼���ԭ�㣬��е���ֲ���
	�������:	uint xyz							ָ����ԭ�����,0x01ΪX��,0x02ΪY��,0x04ΪZ�ᣬ0x07Ϊ����ͬʱ��ԭ�㣨DTA_BUF_MODEģʽʱ��
				ushort mode							ָ��ģʽ,��ָ��ģʽ�б�
				
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		���øú�������������ǰ����Ϊԭ�㣬ʵ�ʵ�����޶���
	            ��mode == CMD_IMM_MODEʱ��������Ҫ�ֱ���ã�������ȷ��ԭ��
				��mode == DTA_BUF_MODEʱ���������ͬʱ��ԭ��
	����ʾ����
*/

CUDRVE_API int WINDLL CUMotorStop(ushort xyz);//1
CUDRVE_API int WINDLL CUMotorSetSpeed(uint SSPEED, 
							uint ESPEED, 
							uint ACC, 
							uint ESPEED_Idle,
							uint ACC_IDLE,
							ushort mode);
/*1
	��������:	��������ٶ�����
	�������:	uint SSPEED							��ʼ�ٶ�(��С�ٶ�)
				uint ESPEED							��ֹ�ٶ�(����ٶ�)
				uint ACC							���ٶ�
				uint ESPEED_Idle					�ճ���ֹ�ٶ�(����ٶ�)
				uint ACC_IDLE						�ճ̼��ٶ�
				ushort mode							ָ��ģʽ,��ָ��ģʽ�б�
				
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/

CUDRVE_API int WINDLL CUMotorRunMode(ushort Motor_Mode, ushort mode);
/*1
	��������:	��������ٶ�ģʽѡ��
	�������:	ushort Motor_Mode					�ٶ�ģʽ,MOTOR_SPEEDΪ��������ģʽ,IDLE_SPEEDΪ�ճ�ģʽ
				ushort mode							ָ��ģʽ,��ָ��ģʽ�б�
				
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/

CUDRVE_API int WINDLL CUWriteBuf(/*int hidnum=0*/);
/*1
	��������:	��DTA_BUF_MODE(��λ������ģʽ)��,����λ���������ݴ��䵽������
	�������:	��
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/

CUDRVE_API int WINDLL CUBufEnd(/*int hidnum=0*/);
/*1
	��������:	��ֹ��ǰ���񻺳�
	�������:	��
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/

CUDRVE_API int WINDLL CUSetPWM(ushort PWMWay,uint Freq, byte duty,ushort mode,BOOL Reverse = false/*,int hidnum=0*/);
/*1
	��������:	����PWM
	�������:	ushort PWMWay					PWMͨ��,��ЧֵΪPWM0/PWM1/PWM2
				uint Freq						Ƶ��ֵ,��λΪHZ
				byte duty						ռ�ձ�,Ϊ0~100,��ʶռ�ձ�Ϊ0%~100%
				ushort mode						ָ��ģʽ,��ָ��ģʽ�б�
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/


CUDRVE_API int WINDLL CUSetPWMUs(ushort PWMWay, uint Freq, uint HighPulseTimeUs, ushort mode, BOOL Reverse = false/*,int hidnum=0*/);
/*9
	��������:	����PWM
	�������:	ushort PWMWay					PWMͨ��,��ЧֵΪPWM0/PWM1/PWM2
				uint Freq						Ƶ��ֵ,��λΪHZ
				ushort HighPulseTimeUs			�ߵ�ƽʱ�䣬��λus
				ushort mode						ָ��ģʽ,��ָ��ģʽ�б�
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
��ʼ������:CUSetPWMUs(PWM2, 5000, 1, CMD_IMM_MODE)
�رտ���:ͬ������
�����ڹع������:ͬ������
һ��ר�ŵ�������:��ԭ������,��Ҫ�����߲�

*/

CUDRVE_API int WINDLL CUGetStatus(CUStatusdef **CUStatus/*,int hidnum=0*/);
/*7
	��������:	��ȡ״̬
	�������:	CUStatusdef **CUStatus		����״̬������ָ��
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		��ָ��Ϊ����ָ��
	����ʾ����
	CUStatusdef *CUStatus = null;
	CUGetStatus(&CUStatus);

*/

CUDRVE_API int WINDLL CUSetup(uint SetupData, ushort SetupCmd, ushort mode/*,int hidnum=0*/);
/*2
	��������:	ϵͳ����
	�������:	uint SetupData��		���ò�����Ĭ��ֵ0x0000��
				BIT0��					0-�����񾵣�1-ģ����	ȱʡΪ1
				BIT1:					0-PWM0��ֹ��1-PWM0����	ȱʡΪ0
				BIT2��					0-PWM1��ֹ��1-PWM1����	ȱʡΪ0
				BIT3��					0-PWM2��ֹ��1-PWM2����	ȱʡΪ1
				BIT4:					0-��ֹ��ʱ�ӣ�1-������ʱ��
				BIT5��					0-�ɶ��½��ش��� 1-�����ش���
				BIT6:					0-������ʧ��������1-����ʧ������
				BIT7:					0-��ֹ���縴λ�� 1-�������縴λ
				
				BIT8					�������X�᷽������
				BIT9					�������Y�᷽������
				BIT10					�������Z�᷽������
				BIT13��BIT11			000		����ģʽ
										001		��ԭ��
										010		XY������������Z����
										011		XYZ��������
				BIT14					0       X�����λ
										1		X�����λ
				BIT15					0		Y�����λ
										1		Y�����λ
				BIT16					0		Z�����λ
										1		Z�����λ
				BIT21					0		��ֹ�����Զ���ʱ�ر�
										1		�������Զ���ʱ�ر�

				BBIT17~IT31��			��δ����
				ushort SetupCmd			0 - SetupData��Ӧλд1ʱ���������и�λ������
										1-	SetupData��Ӧλд1ʱ���������и�λ����λ

				ushort mode				ָ��ģʽ,��ָ��ģʽ�б�
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/

CUDRVE_API int WINDLL CUPausePara(CUSavedDataStruct lCUSavedDataStruct,ushort mode/*,int hidnum=0*/);
/*2
	��������:	��ͣ�񾵲岹����
	�������:	CUSavedDataStruct lCUSavedDataStruct	���CUSavedDataStruct�Ķ���
	�������:	
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/

CUDRVE_API int WINDLL CUPause(/*int hidnum=0*/);
/*1
	��������:	��ͣ�񾵲岹����
	�������:	
	�������:	
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/

CUDRVE_API int WINDLL CUReset(/*int hidnum=0*/);
/*1
	��������:	ϵͳ��λ
	�������:	��
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/

CUDRVE_API int WINDLL CUCancel();
/*2
	��������:	ȡ����ǰ�˶�����
	�������:	��
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		
	����ʾ����
*/
CUDRVE_API uint WINDLL CUGetBufferLength(/*int hidnum=0*/);
/*1
	��������:	��ȡ���ػ��������ó���
	�������:	��
	�������:	��
	����ֵ:		���������ó��ȣ���λWORDS
	˵��:		
	����ʾ����
*/
CUDRVE_API BOOL WINDLL CUBufferIsNotFull(/*int hidnum=0*/);
/*1
	��������:	���ر��ػ�����ʹ��״̬��
	�������:	��
	�������:	��
	����ֵ:		true ������δ�� false ����������
	˵��:		
	����ʾ����
*/

CUDRVE_API int WINDLL CUBufStart(void);
/*1
	��������:	��ǻ�����ָ��Ŀ�ʼ
	�������:	��
	�������:	��
	����ֵ:		
	˵��:		
	����ʾ����
*/


CUDRVE_API int WINDLL CUWaitHome(uint interval,
					   uint uiTimeout,
					   BOOL XHomeEn,
					   byte XHomeLevel,
					   BOOL YHomeEn,
					   byte YHomeLevel,
					   BOOL ZHomeEn,
					   byte ZHomeLevel);
/*1
	��������:	�ȴ������ɻ�ԭ��Ķ���
	�������:	uint interval	ѭ�������һ�����Ϊ20��ms��,���ڲ���ѯ״̬������
				uint uiTimeout	�ȴ���ʱʱ�䣬����10��s�����ò�����С������ǰ�淢�͵����ݵľ������ݣ�
				BOOL XHomeEn	����X�� true������ false:��ֹ
				byte XHomeLevel X��ԭ���ⷽʽ��1���ߵ�ƽ��Ч 0���͵�ƽ��Ч
				BOOL YHomeEn	����Y�� true������ false:��ֹ
				byte YHomeLevel Y��ԭ���ⷽʽ��1���ߵ�ƽ��Ч 0���͵�ƽ��Ч
				BOOL ZHomeEn	����Z�� true������ false:��ֹ
				byte ZHomeLevel Z��ԭ���ⷽʽ��1���ߵ�ƽ��Ч 0���͵�ƽ��Ч
	һ���ֵ������ܴ�
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		�ú������°�̼��в���ʹ�ã��°�̼��У���������ԭ����������ָ�������м䣬������ȴ���
				���Ϊ������һ��ָ�����У��������Ļ�ԭ�㶯���������ֱ�ӵ���CUWaitJobEnd
	����ʾ����
*/

CUDRVE_API void WINDLL CUWriteBufEnable(BOOL Enable/*,int hidnum=0*/);
/*1
	��������:	���øú����󣬶�̬���Զ��ж�д�����Ƿ���������������忨����
	�������:	BOOL Enable  true  �Զ��жϻ�����������
							 false �����жϻ�����������������CUWriteBuf��������ָ��
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		��ָ��������κεط����ã����ú�������Ч
	����ʾ����
*/

CUDRVE_API int WINDLL CUBufFill(/*int hidnum=0*/);
/*1
	��������:	���øú����󣬽�ǿ�����忨��������ʹ�忨�е�����ָ������ִ��
	�������:	��
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:       ĳЩ����£�����ָ�����������С��ֱ�ӷ��͵��忨�Ϻ󣬰忨�����ҳ��û�������������ȴ���ҳ��������Ż�ִ�и�ҳ���е�ָ�
	            Ϊ�������������ú������ֱ���������ҳ�棬���¸�ҳ���ָ������ִ��
				���øú���֮�飬ȷ��������Ҫִ�е�ָ���Ѿ����͵��忨�����ָ���޷�����һ��д������Զ����ͣ���ֱ�ӵ���CUWriteBuf����
	����ʾ����
*/

CUDRVE_API int WINDLL CUCorrectTableInit(ushort line, ushort column, ushort x, ushort y);
/*1
	��������:	У�����ʼ��
	�������:	ushort line			���� 0��64 ����32Ϊ���ĵ�
				ushort column		���� 0��64 ����32Ϊ���ĵ�
				ushort x			ÿ���ڵ��X������
				ushort y			ÿ���ڵ��Y������
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		������65��65�У�����0��31��Ӧ���Ჿ�֣�33��64��Ӧ���Ჿ�֣�32Ϊ������
	����ʾ����
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
	��������:	д������
	�������:	ushort mode				ָ��ģʽ
				uint data_length		���ݳ���
				byte* data				���ݱ���
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		����mode��ͬ�򻺳�����д�����ݻ�ֱ�ӷ���ָ�
				�����������С����֧�ֱ���д���򽫻���������
				д�봮�ڲ�����������պ󽫱��ε�����д�뻺����
	����ʾ��:
		byte *data = new byte[20];
		... PUT DATA INTO data
		WriteDataToWithMode(CMD_BUF_MODE, 20, data);
*/

extern int WriteDataToBufer(uint data_length, byte* data/*,int hidnum=0*/);
/*
	��������:	д������
	�������:	uint data_length		���ݳ���
				byte* data				���ݱ���
	�������:	��
	����ֵ:		����������ֵ�б�
	˵��:		�򻺳�����д�����ݣ������������С����֧�ֱ���д���򽫻���������
				д�봮�ڲ�����������պ󽫱��ε�����д�뻺����
	����ʾ��:
		byte *data = new byte[20];
		... PUT DATA INTO data 
		WriteDataToBuffer(20, data);
*/

extern void UnsignedShortTobyte(ushort origin, byte* data, int data_index);

extern void UnsignedIntTobyte(uint origin, byte* data, int data_index);

extern void IntTobyte(int origin, byte* data, int data_index);