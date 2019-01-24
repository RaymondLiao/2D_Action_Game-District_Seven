#include<graphics.h>
/////////////////////////////////////////////////////////////////
//定义符号常量
#define BUTTONWIDTH		90				//主界面按钮的宽度与高度
#define BUTTONHEIGHT	90
#define WIDTH		700					//屏幕宽度为700像素
#define HEIGHT		700					//屏幕高度为700像素
#define DATANUM		2					//最多出现的破碎数据数量
#define DATAWORMLEN	10					//数据蠕虫最大长度为15节(每一节像素为10*15）
#define PI			3.1415926
#define NUM 300

#define CMD_UP			1				//控制蠕虫向上移动的操作
#define CMD_DOWN		2				//控制蠕虫向下移动的操作
#define CMD_LEFT		4				//控制蠕虫向左移动的操作
#define CMD_RIGHT		8				//控制蠕虫向右移动的操作
#define CMD_LEFTUP		16				//控制蠕虫向左上移动的操作
#define	CMD_RIGHTUP		32				//控制蠕虫向右上移动的操作
#define	CMD_LEFTDOWN	64				//控制蠕虫向左下移动的操作
#define CMD_RIGHTDOWN	128				//控制蠕虫向左下移动的操作

#define HP_A		500					//数据蠕虫A等血量下限
#define HP_B		400					//数据蠕虫B等血量下限
#define HP_C		300					//数据蠕虫C等血量下限
#define HP_D		200					//数据蠕虫D等血量下限
#define HP_E		100					//数据蠕虫E等血量下限

#define HPINCREASE	30					//每收集到一个破碎数据恢复的血量
#define HPDECREASE	50					//数据蠕虫每撞到自己的身体时减少的血量

#define COLOR1_A		GREEN				//第一关数据蠕虫血量为A等时的颜色
#define COLOR1_B		LIGHTGREEN
#define COLOR1_C		YELLOW
#define COLOR1_D		RGB(251,167,28)
#define COLOR1_E		RGB(253,74,15)
#define COLOR1_F		RGB(133,34,1)

#define COLOR2_A		LIGHTBLUE			//第二关数据蠕虫血量为A等时的颜色
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

#define SPEED1		3				//(怪物)移动速度
#define SPEED2		5
#define SPEED3		10
#define	SPEED4		15
#define SPEED5		18

#define R1			92				//(怪物)旋转半径
#define R2			150
#define R3			250

#define CIR1		40				//(怪物)旋转周期
#define CIR2		80
#define CIR3		100

#define DMG1		80				//(怪物)伤害值
#define DMG2		120
#define DMG3		240
#define DMG4		360
#define DMG5		480

#define DMGTIME		2000			//(怪物)伤害冷却时间
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//枚举类型、结构体

typedef enum
{
	up,down,left,right,leftup,rightup,leftdown,rightdown
}DIR;

typedef struct						//坐标结构体
{
	int x;
	int y;
}COOR;

typedef	struct						//(怪物)大小结构体(w:宽度像素	h:高度像素)
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

struct DATA							//存储破碎数据信息的结构体数组（坐标、数据类型（0、1）、是否已被收集）
{
	COOR crd;
	bool type;
	bool flag;
	TIM settime;
};

struct DATAWORM						//存储数据蠕虫信息的结构体（每一节的坐标和数据类型（0、1）、节数、HP、数据蠕虫的移动方向）
{
	COOR crd[DATAWORMLEN+1];
	bool type[DATAWORMLEN+1];
	int node;
	int hp;
	DIR dir;
};

struct NOMMONSTER					//存储无多图怪物的信息的结构体
{
	IMAGE img;
	COOR crd;
	SIZ	size;
	int speed;
	int dmg;
	TIM time;
};

struct ANIMONSTER_1_3				//存储第一关数据守卫3的信息的结构体
{
	IMAGE img[15];
	COOR crd;
	SIZ	size;
	int speed;
	int dmg;
	TIM time;
};

struct ANIMONSTER_2_2				//存储第二关数据守卫2的信息的结构体
{
	IMAGE img[6];
	COOR crd;
	SIZ	size;
	int dmg;
	TIM time;
};

struct ANIMONSTER_2_4				//存储第二关数据守卫4的信息的结构体
{
	IMAGE img[8];
	COOR crd;
	SIZ	size;
	int dmg;
	TIM time;
};

struct ANIMONSTER_3_2				//存储第三关矩阵锯轮的信息的结构体
{
	IMAGE img[3];
	COOR crd;
	SIZ	size;
	int speed;
	int dmg;
	TIM time;
};

struct ANIMONSTER_3_3				//存储第三关结点陷阱的信息的结构体
{
	IMAGE img[7];
	COOR crd;
	SIZ	size;
	int dmg;
	TIM time;
};

struct ANIMONSTER_3_4				//存储第三关能量团的信息的结构体
{
	IMAGE img[3];
	COOR crd;
	SIZ	size;
	int dmg;
	TIM time;
};

struct BOSS1						//存储第一关BOSS的信息的结构体(其中dir表示移动方向，state表示BOSS是否处于发招状态)
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

struct BOSS2						//存储第二关BOSS的信息的结构体(state表示BOSS所处状态)
{
	IMAGE img[4];
	COOR crd;
	SIZ size;
	int dmg;
	TIM time;
	TIM dmgtime;
	char state;
};

struct LIGHT1						//第二关BOSS招式“聚光束”
{
	IMAGE img[7];
	COOR crd;
	SIZ size;
	int dmg;
	TIM time;
};

struct LIGHT2						//第二关BOSS招式“破坏光线”
{
	IMAGE img[9];
	COOR crd;
	SIZ size;
	int dmg;
	TIM time;
};

struct BOSS3						//存储第三关BOSS信息的结构体，图像分状态进行存储
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
//函数声明
void InitGame();					//初始化游戏
void EnterAni();					//播放数字雨动画
void StartGame();					//进入选择关卡界面

void EnterGmLv1();					//进入游戏的第一关						
void EnterGmLv2();					//进入游戏的第二关						
void EnterGmLv3();					//进入游戏的第三关						

void InitGameLevel();				//初始化游戏关卡
void InitDataworm();				//初始化数据蠕虫						
void InitSection();					//初始化小节							

void InitMonster();					//初始化怪物								
void LoadMonsterImg();				//(根据小节和进程)读取怪物的图像		
void InitMonsterCrd();				//(根据小节和进程)初始化怪物坐标		
void InitMonsterSpeed();			//(根据小节和进程)初始化怪物速度		
void InitMonsterSize();				//(根据小节和进程)初始化怪物大小		
void InitMonsterDmg();				//(根据小节和进程)初始化怪物伤害		
void InitMonsterDmgTime();			//(根据小节和进程)初始化怪物造成伤害的时刻	

void ShowMonster();					//(根据小节和进程)画出怪物				
void MoveMonster();					//(根据小节和进程)移动怪物				
void JudgeCrashMonster();			//(根据小节和进程)判断是否撞到怪物		

void SetData();						//随机设置破碎数据的坐标				
void ShowData(int x,int y,int t);	//放置破碎数据							
void JudgeGetData();				//判断是否收集到数据					

int GetCommand();					//接收玩家的操作信息					
void DispatchCommand(int _cmd);		//发配玩家的操作信息					

void ClearScreen();					//清屏									
void DmgAni();						//数据蠕虫受到伤害时的小动画			
void SecAni();						//跳小节动画
void DieAni();						//死亡动画

void MoveDataworm();				//根据玩家的操作移动数据蠕虫			
void ShowDataworm();				//画出数据蠕虫							
void JudgeCrash();					//判断数据蠕虫是否触碰到自己			

bool JudgeChange_Pro_or_Pic();		//(根据小节进程及主循环次数)判断是否改变全局变量Pro或者Pic	

int hcf(int,int);					//求两数的最大公约数	
int lcd(int,int,int);				//求两数的最小公倍数	

void Init();
void Blur(DWORD *IBuffer);
void Draw();
void DrawSnowPoint();

void EnterHf();
void EnterCf();
void QuitGm();
///////////////////////////////////////////////////////////////////
