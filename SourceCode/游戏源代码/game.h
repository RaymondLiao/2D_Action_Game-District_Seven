#include<graphics.h>
/////////////////////////////////////////////////////////////////
//������ų���
#define BUTTONWIDTH		90				//�����水ť�Ŀ����߶�
#define BUTTONHEIGHT	90
#define WIDTH		700					//��Ļ���Ϊ700����
#define HEIGHT		700					//��Ļ�߶�Ϊ700����
#define DATANUM		2					//�����ֵ�������������
#define DATAWORMLEN	10					//���������󳤶�Ϊ15��(ÿһ������Ϊ10*15��
#define PI			3.1415926
#define NUM 300

#define CMD_UP			1				//������������ƶ��Ĳ���
#define CMD_DOWN		2				//������������ƶ��Ĳ���
#define CMD_LEFT		4				//������������ƶ��Ĳ���
#define CMD_RIGHT		8				//������������ƶ��Ĳ���
#define CMD_LEFTUP		16				//��������������ƶ��Ĳ���
#define	CMD_RIGHTUP		32				//��������������ƶ��Ĳ���
#define	CMD_LEFTDOWN	64				//��������������ƶ��Ĳ���
#define CMD_RIGHTDOWN	128				//��������������ƶ��Ĳ���

#define HP_A		500					//�������A��Ѫ������
#define HP_B		400					//�������B��Ѫ������
#define HP_C		300					//�������C��Ѫ������
#define HP_D		200					//�������D��Ѫ������
#define HP_E		100					//�������E��Ѫ������

#define HPINCREASE	30					//ÿ�ռ���һ���������ݻָ���Ѫ��
#define HPDECREASE	50					//�������ÿײ���Լ�������ʱ���ٵ�Ѫ��

#define COLOR1_A		GREEN				//��һ���������Ѫ��ΪA��ʱ����ɫ
#define COLOR1_B		LIGHTGREEN
#define COLOR1_C		YELLOW
#define COLOR1_D		RGB(251,167,28)
#define COLOR1_E		RGB(253,74,15)
#define COLOR1_F		RGB(133,34,1)

#define COLOR2_A		LIGHTBLUE			//�ڶ����������Ѫ��ΪA��ʱ����ɫ
#define COLOR2_B		RGB(142,153,244)
#define COLOR2_C		RGB(207,139,248)
#define COLOR2_D		RGB(244,139,248)
#define COLOR2_E		RGB(172,4,58)
#define COLOR2_F		RGB(133,34,1)

#define COLOR3_A		RGB(111,68,236)
#define COLOR3_B		RGB(180,153,242)
#define COLOR3_C		RGB(231,169,250)
#define COLOR3_D		RGB(217,115,247)
#define COLOR3_E		RGB(193,37,226)
#define COLOR3_F		RGB(148,3,115)

#define SPEED1		3				//(����)�ƶ��ٶ�
#define SPEED2		5
#define SPEED3		10
#define	SPEED4		15
#define SPEED5		18

#define R1			92				//(����)��ת�뾶
#define R2			150
#define R3			250

#define CIR1		40				//(����)��ת����
#define CIR2		80
#define CIR3		100

#define DMG1		80				//(����)�˺�ֵ
#define DMG2		120
#define DMG3		240
#define DMG4		360
#define DMG5		480

#define DMGTIME		2000			//(����)�˺���ȴʱ��
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//ö�����͡��ṹ��

typedef enum
{
	up,down,left,right,leftup,rightup,leftdown,rightdown
}DIR;

typedef struct						//����ṹ��
{
	int x;
	int y;
}COOR;

typedef	struct						//(����)��С�ṹ��(w:�������	h:�߶�����)
{
	int w;
	int h;
}SIZ;

typedef struct
{
	unsigned int oldtime;
	unsigned int newtime;
}TIM;

typedef struct SnowPOINT
{
	int x;
	int y;
	char * style;
}SP,*pSP;


struct BUTTON
{
	IMAGE img[5];
	COOR crd;
};

struct DATA							//�洢����������Ϣ�Ľṹ�����飨���ꡢ�������ͣ�0��1�����Ƿ��ѱ��ռ���
{
	COOR crd;
	bool type;
	bool flag;
	TIM settime;
};

struct DATAWORM						//�洢���������Ϣ�Ľṹ�壨ÿһ�ڵ�������������ͣ�0��1����������HP�����������ƶ�����
{
	COOR crd[DATAWORMLEN+1];
	bool type[DATAWORMLEN+1];
	int node;
	int hp;
	DIR dir;
};

struct NOMMONSTER					//�洢�޶�ͼ�������Ϣ�Ľṹ��
{
	IMAGE img;
	COOR crd;
	SIZ	size;
	int speed;
	int dmg;
	TIM time;
};

struct ANIMONSTER_1_3				//�洢��һ����������3����Ϣ�Ľṹ��
{
	IMAGE img[15];
	COOR crd;
	SIZ	size;
	int speed;
	int dmg;
	TIM time;
};

struct ANIMONSTER_2_2				//�洢�ڶ�����������2����Ϣ�Ľṹ��
{
	IMAGE img[6];
	COOR crd;
	SIZ	size;
	int dmg;
	TIM time;
};

struct ANIMONSTER_2_4				//�洢�ڶ�����������4����Ϣ�Ľṹ��
{
	IMAGE img[8];
	COOR crd;
	SIZ	size;
	int dmg;
	TIM time;
};

struct ANIMONSTER_3_2				//�洢�����ؾ�����ֵ���Ϣ�Ľṹ��
{
	IMAGE img[3];
	COOR crd;
	SIZ	size;
	int speed;
	int dmg;
	TIM time;
};

struct ANIMONSTER_3_3				//�洢�����ؽ���������Ϣ�Ľṹ��
{
	IMAGE img[7];
	COOR crd;
	SIZ	size;
	int dmg;
	TIM time;
};

struct ANIMONSTER_3_4				//�洢�����������ŵ���Ϣ�Ľṹ��
{
	IMAGE img[3];
	COOR crd;
	SIZ	size;
	int dmg;
	TIM time;
};

struct BOSS1						//�洢��һ��BOSS����Ϣ�Ľṹ��(����dir��ʾ�ƶ�����state��ʾBOSS�Ƿ��ڷ���״̬)
{
	IMAGE img[10];
	COOR crd;
	SIZ size;
	int speed;
	int dmg;
	TIM time;
	int dir;
	bool state;
};

struct BOSS2						//�洢�ڶ���BOSS����Ϣ�Ľṹ��(state��ʾBOSS����״̬)
{
	IMAGE img[4];
	COOR crd;
	SIZ size;
	int dmg;
	TIM time;
	TIM dmgtime;
	char state;
};

struct LIGHT1						//�ڶ���BOSS��ʽ���۹�����
{
	IMAGE img[7];
	COOR crd;
	SIZ size;
	int dmg;
	TIM time;
};

struct LIGHT2						//�ڶ���BOSS��ʽ���ƻ����ߡ�
{
	IMAGE img[9];
	COOR crd;
	SIZ size;
	int dmg;
	TIM time;
};

struct BOSS3						//�洢������BOSS��Ϣ�Ľṹ�壬ͼ���״̬���д洢
{
	IMAGE img0[5];
	IMAGE img1;
	IMAGE img2[7];
	IMAGE img3[9];
	IMAGE img4[5];
	IMAGE img5[5];
	COOR crd;
	SIZ size;
	int dmg;
	TIM time;
	TIM dmgtime;
	char state;
};

///////////////////////////////////////////////////////////////////
//��������
void InitGame();					//��ʼ����Ϸ
void EnterAni();					//���������궯��
void StartGame();					//����ѡ��ؿ�����

void EnterGmLv1();					//������Ϸ�ĵ�һ��						
void EnterGmLv2();					//������Ϸ�ĵڶ���						
void EnterGmLv3();					//������Ϸ�ĵ�����						

void InitGameLevel();				//��ʼ����Ϸ�ؿ�
void InitDataworm();				//��ʼ���������						
void InitSection();					//��ʼ��С��							

void InitMonster();					//��ʼ������								
void LoadMonsterImg();				//(����С�ںͽ���)��ȡ�����ͼ��		
void InitMonsterCrd();				//(����С�ںͽ���)��ʼ����������		
void InitMonsterSpeed();			//(����С�ںͽ���)��ʼ�������ٶ�		
void InitMonsterSize();				//(����С�ںͽ���)��ʼ�������С		
void InitMonsterDmg();				//(����С�ںͽ���)��ʼ�������˺�		
void InitMonsterDmgTime();			//(����С�ںͽ���)��ʼ����������˺���ʱ��	

void ShowMonster();					//(����С�ںͽ���)��������				
void MoveMonster();					//(����С�ںͽ���)�ƶ�����				
void JudgeCrashMonster();			//(����С�ںͽ���)�ж��Ƿ�ײ������		

void SetData();						//��������������ݵ�����				
void ShowData(int x,int y,int t);	//������������							
void JudgeGetData();				//�ж��Ƿ��ռ�������					

int GetCommand();					//������ҵĲ�����Ϣ					
void DispatchCommand(int _cmd);		//������ҵĲ�����Ϣ					

void ClearScreen();					//����									
void DmgAni();						//��������ܵ��˺�ʱ��С����			
void SecAni();						//��С�ڶ���
void DieAni();						//��������

void MoveDataworm();				//������ҵĲ����ƶ��������			
void ShowDataworm();				//�����������							
void JudgeCrash();					//�ж���������Ƿ������Լ�			

bool JudgeChange_Pro_or_Pic();		//(����С�ڽ��̼���ѭ������)�ж��Ƿ�ı�ȫ�ֱ���Pro����Pic	

int hcf(int,int);					//�����������Լ��	
int lcd(int,int,int);				//����������С������	

void Init();
void Blur(DWORD *IBuffer);
void Draw();
void DrawSnowPoint();

void EnterHf();
void EnterCf();
void QuitGm();
///////////////////////////////////////////////////////////////////
