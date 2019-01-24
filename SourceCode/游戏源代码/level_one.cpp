#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"game.h"
#pragma comment(lib,"Winmm.lib")

///////////////////////////////////////////////////////////////////////////////////////////
NOMMONSTER	monster1_1[7],monster1_2;
ANIMONSTER_1_3  monster1_3[3];
extern	BOSS1	boss1;

extern int Sec,Cir,Pro,Pic,Pic1,Getdatanum;
extern bool w2;
extern IMAGE bkimgani[21];	

extern DATA data[DATANUM];
extern DATAWORM dataworm;
////////////////////////////////////////////////////////////////////////////////////////////
void EnterGmLv1()
{
	mciSendString("open 背景音乐及音效\\BGM01.mp3 alias mymusic", NULL, 0, NULL);
	mciSendString("play 背景音乐及音效\\BGM01.mp3 repeat", NULL, 0, NULL);
	BeginBatchDraw();
	Lv1_1:InitSection();
	Lv1_2:InitMonster();
	ClearScreen();
	ShowMonster();
	while(1)
	{
		SetData();
		for(int i=0;i<DATANUM;i++)
			if(data[i].flag==1)		ShowData(data[i].crd.x,data[i].crd.y,data[i].type);
		MoveMonster();
		ShowMonster();
		ShowDataworm();
		JudgeCrashMonster();
		if(kbhit())
		{
			int c;
			c=GetCommand();
			DispatchCommand(c);
			JudgeCrash();
			JudgeGetData();
			if(Getdatanum==10)
			{
				SecAni();
				Sec++;
				if(Sec==5)
				{
					mciSendString("stop 背景音乐及音效\\BGM01.mp3", NULL, 0, NULL);
					mciSendString("close 背景音乐及音效\\BGM01.mp3", NULL, 0, NULL);
					mciSendString("open 背景音乐及音效\\BGM04.mp3 alias mymusic", NULL, 0, NULL);
					mciSendString("play 背景音乐及音效\\BGM04.mp3 repeat", NULL, 0, NULL);
				}
				if(Sec>5)
				{
					mciSendString("stop 背景音乐及音效\\BGM04.mp3", NULL, 0, NULL);
					mciSendString("close 背景音乐及音效\\BGM04.mp3", NULL, 0, NULL);
					mciSendString("open 背景音乐及音效\\BGM00.mp3 alias mymusic", NULL, 0, NULL);
					mciSendString("play 背景音乐及音效\\BGM00.mp3 repeat", NULL, 0, NULL);
					w2=true;
					return;
				}
				else	goto Lv1_1;
			}
		}
		FlushBatchDraw();
		Sleep(35);
		Cir++;
		if(JudgeChange_Pro_or_Pic())
			goto Lv1_2;
		else	ClearScreen();

		if(dataworm.hp<0)
		{
			DieAni();
			if(Sec!=5)
			{
				mciSendString("stop 背景音乐及音效\\BGM01.mp3", NULL, 0, NULL);
				mciSendString("close 背景音乐及音效\\BGM01.mp3", NULL, 0, NULL);
			}
			else
			{
				mciSendString("stop 背景音乐及音效\\BGM04.mp3", NULL, 0, NULL);
				mciSendString("close 背景音乐及音效\\BGM04.mp3", NULL, 0, NULL);
			}
			mciSendString("open 背景音乐及音效\\BGM00.mp3 alias mymusic", NULL, 0, NULL);
			mciSendString("play 背景音乐及音效\\BGM00.mp3 repeat", NULL, 0, NULL);
			return;
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////
//函数定义

static void InitMonster()						//初始化怪物
{
	LoadMonsterImg();	
	InitMonsterSize();	
	InitMonsterCrd();				
	InitMonsterSpeed();						
	InitMonsterDmg();				
	InitMonsterDmgTime();
}

static void LoadMonsterImg()
{
	switch(Sec)
	{
		case 1:
			switch(Pro)
			{
				case 0:
					{
						loadimage(&monster1_1[0].img,_T("正式图\\第一关\\数据守卫1(翻转).jpg"));
						loadimage(&monster1_1[1].img,_T("正式图\\第一关\\数据守卫1.jpg"));
						loadimage(&monster1_1[2].img,_T("正式图\\第一关\\数据守卫1(翻转).jpg"));
					}break;
				case 1:
					{
						loadimage(&monster1_1[0].img,_T("正式图\\第一关\\数据守卫1.jpg"));
						loadimage(&monster1_1[1].img,_T("正式图\\第一关\\数据守卫1(翻转).jpg"));
						loadimage(&monster1_1[2].img,_T("正式图\\第一关\\数据守卫1.jpg"));
					}
			}break;
		case 2:
			switch(Pro)
			{
				case 0:
					{
						loadimage(&monster1_1[0].img,_T("正式图\\第一关\\数据守卫1(翻转).jpg"));
						loadimage(&monster1_1[1].img,_T("正式图\\第一关\\数据守卫1(翻转).jpg"));
						loadimage(&monster1_1[2].img,_T("正式图\\第一关\\数据守卫1(翻转).jpg"));
						loadimage(&monster1_1[3].img,_T("正式图\\第一关\\数据守卫1.jpg"));
						loadimage(&monster1_1[4].img,_T("正式图\\第一关\\数据守卫1.jpg"));
						loadimage(&monster1_1[5].img,_T("正式图\\第一关\\数据守卫1.jpg"));
						loadimage(&monster1_1[6].img,_T("正式图\\第一关\\数据守卫1.jpg"));
					}break;
				case 1:
					{
						loadimage(&monster1_1[0].img,_T("正式图\\第一关\\数据守卫1.jpg"));
						loadimage(&monster1_1[1].img,_T("正式图\\第一关\\数据守卫1.jpg"));
						loadimage(&monster1_1[2].img,_T("正式图\\第一关\\数据守卫1.jpg"));
						loadimage(&monster1_1[3].img,_T("正式图\\第一关\\数据守卫1(翻转).jpg"));
						loadimage(&monster1_1[4].img,_T("正式图\\第一关\\数据守卫1(翻转).jpg"));
						loadimage(&monster1_1[5].img,_T("正式图\\第一关\\数据守卫1(翻转).jpg"));
						loadimage(&monster1_1[6].img,_T("正式图\\第一关\\数据守卫1(翻转).jpg"));
					}
			}break;
		case 3:
			switch(Pro)
			{
				case 0:
					{
						loadimage(&monster1_1[0].img,_T("正式图\\第一关\\数据守卫1(翻转).jpg"));
						loadimage(&monster1_1[1].img,_T("正式图\\第一关\\数据守卫1.jpg"));
						loadimage(&monster1_2.img,_T("正式图\\第一关\\数据守卫2.jpg"));
					}break;
				case 1:
					{
						loadimage(&monster1_1[0].img,_T("正式图\\第一关\\数据守卫1.jpg"));
						loadimage(&monster1_1[1].img,_T("正式图\\第一关\\数据守卫1(翻转).jpg"));
					}
			}break;
		case 4:
			{
				for(int i=0;i<3;i++)
				{
					loadimage(&monster1_3[i].img[0],_T("正式图\\第一关\\数据守卫3动画_01.jpg"));
					loadimage(&monster1_3[i].img[1],_T("正式图\\第一关\\数据守卫3动画_02.jpg"));
					loadimage(&monster1_3[i].img[2],_T("正式图\\第一关\\数据守卫3动画_03.jpg"));
					loadimage(&monster1_3[i].img[3],_T("正式图\\第一关\\数据守卫3动画_04.jpg"));
					loadimage(&monster1_3[i].img[4],_T("正式图\\第一关\\数据守卫3动画_05.jpg"));
					loadimage(&monster1_3[i].img[5],_T("正式图\\第一关\\数据守卫3动画_06.jpg"));
					loadimage(&monster1_3[i].img[6],_T("正式图\\第一关\\数据守卫3动画_07.jpg"));
					loadimage(&monster1_3[i].img[7],_T("正式图\\第一关\\数据守卫3动画_08.jpg"));
					loadimage(&monster1_3[i].img[8],_T("正式图\\第一关\\数据守卫3动画_09.jpg"));
					loadimage(&monster1_3[i].img[9],_T("正式图\\第一关\\数据守卫3动画_10.jpg"));
					loadimage(&monster1_3[i].img[10],_T("正式图\\第一关\\数据守卫3动画_11.jpg"));
					loadimage(&monster1_3[i].img[11],_T("正式图\\第一关\\数据守卫3动画_12.jpg"));
					loadimage(&monster1_3[i].img[12],_T("正式图\\第一关\\数据守卫3动画_13.jpg"));
					loadimage(&monster1_3[i].img[13],_T("正式图\\第一关\\数据守卫3动画_14.jpg"));
					loadimage(&monster1_3[i].img[14],_T("正式图\\第一关\\数据守卫3动画_15.jpg"));
				}
			}break;
		case 5:
			{
				loadimage(&boss1.img[0],_T("正式图\\第一关\\BOSS1(冲撞1左).jpg"));
				loadimage(&boss1.img[1],_T("正式图\\第一关\\BOSS1(冲撞2左).jpg"));
				loadimage(&boss1.img[2],_T("正式图\\第一关\\BOSS1(冲撞3左).jpg"));
				loadimage(&boss1.img[3],_T("正式图\\第一关\\BOSS1(冲撞4左).jpg"));
				loadimage(&boss1.img[4],_T("正式图\\第一关\\BOSS1(左).jpg"));
				loadimage(&boss1.img[5],_T("正式图\\第一关\\BOSS1(冲撞1右).jpg"));
				loadimage(&boss1.img[6],_T("正式图\\第一关\\BOSS1(冲撞2右).jpg"));
				loadimage(&boss1.img[7],_T("正式图\\第一关\\BOSS1(冲撞3右).jpg"));
				loadimage(&boss1.img[8],_T("正式图\\第一关\\BOSS1(冲撞4右).jpg"));
				loadimage(&boss1.img[9],_T("正式图\\第一关\\BOSS1(右).jpg"));
			}
	}
}


static void InitMonsterCrd()
{
	switch(Sec)
	{
		case 1:
			switch(Pro)
			{
				case 0:
					{
						monster1_1[0].crd.x=-monster1_1[0].size.w,		monster1_1[0].crd.y=HEIGHT/14;
						monster1_1[1].crd.x=WIDTH,						monster1_1[1].crd.y=(HEIGHT-2.5*monster1_1[1].size.h)/2+100*sin(5*(long double)monster1_1[1].crd.x);
						monster1_1[2].crd.x=-monster1_1[2].size.w,		monster1_1[2].crd.y=13*HEIGHT/14-monster1_1[2].size.h;
					}break;
				case 1:
					{
						monster1_1[0].crd.x=WIDTH,						monster1_1[0].crd.y=HEIGHT/14;
						monster1_1[1].crd.x=-monster1_1[1].size.w,		monster1_1[1].crd.y=(HEIGHT-2.5*monster1_1[1].size.h)/2+100*cos(5*(long double)monster1_1[1].crd.x);
						monster1_1[2].crd.x=WIDTH,						monster1_1[2].crd.y=13*HEIGHT/14-monster1_1[2].size.h;
					}
			}break;
		case 2:
			switch(Pro)
			{
				case 0:
					{
						monster1_1[0].crd.x=-monster1_1[0].size.w,										monster1_1[0].crd.y=3*HEIGHT/14+100*cos(5*(long double)monster1_1[0].crd.x);
						monster1_1[1].crd.x=monster1_1[0].crd.x-11*WIDTH/28-monster1_1[1].size.w,		monster1_1[1].crd.y=3*HEIGHT/14+100*cos(5*(long double)monster1_1[1].crd.x);
						monster1_1[2].crd.x=monster1_1[0].crd.x-11*WIDTH/14-2*monster1_1[0].size.w,		monster1_1[2].crd.y=3*HEIGHT/14+100*cos(5*(long double)monster1_1[2].crd.x);
						monster1_1[3].crd.x=WIDTH,														monster1_1[3].crd.y=(HEIGHT-monster1_1[3].size.h)/2;
						monster1_1[4].crd.x=WIDTH,														monster1_1[4].crd.y=11*HEIGHT/14-monster1_1[4].size.h+100*sin(5*(long double)monster1_1[0].crd.x);
						monster1_1[5].crd.x=monster1_1[4].crd.x+11*WIDTH/28+monster1_1[5].size.w,		monster1_1[5].crd.y=11*HEIGHT/14-monster1_1[4].size.h+100*sin(5*(long double)monster1_1[1].crd.x);
						monster1_1[6].crd.x=monster1_1[4].crd.x+11*WIDTH/14+2*monster1_1[6].size.w,		monster1_1[6].crd.y=11*HEIGHT/14-monster1_1[4].size.h+100*sin(5*(long double)monster1_1[2].crd.x);
					}break;
				case 1:
					{
						monster1_1[0].crd.x=WIDTH,														monster1_1[0].crd.y=3*HEIGHT/14+100*sin(5*(long double)monster1_1[0].crd.x);
						monster1_1[1].crd.x=monster1_1[0].crd.x+11*WIDTH/28+monster1_1[1].size.w,		monster1_1[1].crd.y=3*HEIGHT/14+100*sin(5*(long double)monster1_1[1].crd.x);
						monster1_1[2].crd.x=monster1_1[0].crd.x+11*WIDTH/14+2*monster1_1[2].size.w,		monster1_1[2].crd.y=3*HEIGHT/14+100*sin(5*(long double)monster1_1[2].crd.x);
						monster1_1[3].crd.x=-monster1_1[3].size.w,										monster1_1[3].crd.y=(HEIGHT-monster1_1[3].size.h)/2;
						monster1_1[4].crd.x=-monster1_1[4].size.w,										monster1_1[4].crd.y=11*HEIGHT/14-monster1_1[4].size.h+100*cos(5*(long double)monster1_1[0].crd.x);
						monster1_1[5].crd.x=monster1_1[4].crd.x-11*WIDTH/28-monster1_1[5].size.w,		monster1_1[5].crd.y=11*HEIGHT/14-monster1_1[4].size.h+100*cos(5*(long double)monster1_1[1].crd.x);
						monster1_1[6].crd.x=monster1_1[4].crd.x-11*WIDTH/14-2*monster1_1[6].size.w,		monster1_1[6].crd.y=11*HEIGHT/14-monster1_1[4].size.h+100*cos(5*(long double)monster1_1[2].crd.x);
					}
			}break;
		case 3:
			switch(Pro)
			{
				case 0:
					{
						monster1_1[0].crd.x=-monster1_1[0].size.w,										monster1_1[0].crd.y=2*HEIGHT/14+100*cos(5*(long double)monster1_1[0].crd.x);
						monster1_1[1].crd.x=WIDTH,														monster1_1[1].crd.y=11*HEIGHT/14+100*sin(5*(long double)monster1_1[1].crd.x);
						monster1_2.crd.x=3*WIDTH/7+R2*cos(Cir*2*PI/CIR2)+0.5,							monster1_2.crd.y=3*HEIGHT/7+R2*sin(Cir*2*PI/CIR2)+0.5;
					}break;
				case 1:
					{
						monster1_1[0].crd.x=11*WIDTH/14+100*cos(5*(long double)monster1_1[0].crd.y),					monster1_1[0].crd.y=-monster1_1[0].size.h;
						monster1_1[1].crd.x=WIDTH/14+monster1_1[1].size.w+100*sin(5*(long double)monster1_1[1].crd.y),	monster1_1[1].crd.y=HEIGHT;
					}
			}break;
		case 4:
			switch(Pro)
			{
				case 0:
					{
						monster1_3[0].crd.x=-monster1_3[0].size.w,										monster1_3[0].crd.y=HEIGHT/14;
						monster1_3[1].crd.x=monster1_3[0].crd.x,										monster1_3[1].crd.y=(HEIGHT-monster1_3[1].size.h)/2;
						monster1_3[2].crd.x=monster1_3[0].crd.x,										monster1_3[2].crd.y=10*HEIGHT/14;
					}break;
				case 1:
					{
						monster1_3[0].crd.x=WIDTH,														monster1_3[0].crd.y=HEIGHT/3-monster1_3[0].size.h;
						monster1_3[1].crd.x=monster1_3[0].crd.x,										monster1_3[1].crd.y=2*HEIGHT/3;
					}
			}break;
		case 5:
			{
				boss1.dir=rand()%2;
				if(boss1.dir==0)	boss1.crd.x=-boss1.size.w;
				else			boss1.crd.x=WIDTH;
				boss1.crd.y=dataworm.crd[0].y-boss1.size.h/2;
				if(boss1.crd.y<0)	boss1.crd.y=0;
				if(boss1.crd.y>HEIGHT-boss1.size.h)	boss1.crd.y=HEIGHT-boss1.size.h;
			}
	}
}


static void InitMonsterSpeed()
{
	switch(Sec)
	{
		case 1:
			{
				for(int i=0;i<3;i++)
					monster1_1[i].speed=SPEED2;
			}break;
		case 2:
			{
				for(int i=0;i<7;i++)
				{
					if(i==3)	monster1_1[i].speed=SPEED1;
					else		monster1_1[i].speed=SPEED2;
				}
			}break;
		case 3:
			{
				for(int i=0;i<2;i++)
					monster1_1[i].speed=SPEED2;
			}break;
		case 4:
			{
				for(int i=0;i<3;i++)
					monster1_3[i].speed=SPEED4;
			}break;
		case 5:
			{
				boss1.state=rand()%2;
				if(boss1.state==0)	boss1.speed=SPEED3;
				else				boss1.speed=2.1*SPEED3;
			}
	}
}

static void InitMonsterSize()
{
	switch(Sec)
	{
		case 1:
			{
				for(int i=0;i<3;i++)
					monster1_1[i].size.w=50,	monster1_1[i].size.h=50;
			}break;
		case 2:
			{
				for(int i=0;i<7;i++)
					monster1_1[i].size.w=50,	monster1_1[i].size.h=50;
			}break;
		case 3:
			{
				for(int i=0;i<2;i++)
					monster1_1[i].size.w=50,	monster1_1[i].size.h=50;
				monster1_2.size.w=100,			monster1_2.size.h=100;
			}break;
		case 4:
			{
				for(int i=0;i<3;i++)
					monster1_3[i].size.w=120,	monster1_3[i].size.h=150;
			}break;
		case 5:
			{
				boss1.size.w=250;
				boss1.size.h=262;
			}
	}
}

static void InitMonsterDmg()
{
	switch(Sec)
	{
		case 1:
			{
				for(int i=0;i<3;i++)
					monster1_1[i].dmg=DMG1;
			}break;
		case 2:
			{
				for(int i=0;i<7;i++)
					monster1_1[i].dmg=DMG1;
			}break;
		case 3:
			{
				for(int i=0;i<2;i++)
					monster1_1[i].dmg=DMG1;
				monster1_2.dmg=DMG2;
			}break;
		case 4:
			{
				for(int i=0;i<3;i++)
				{
					monster1_3[i].dmg=DMG2;
				}
			}break;
		case 5:
			{
				if(boss1.state==0)	boss1.dmg=DMG3;
				else				boss1.dmg=DMG4;
			}
	}
}

static void InitMonsterDmgTime()
{
	switch(Sec)
	{
		case 1:
			{
				for(int i=0;i<3;i++)
					monster1_1[i].time.oldtime=0;
			}break;
		case 2:
			{
				for(int i=0;i<7;i++)
					monster1_1[i].time.oldtime=0;
			}break;
		case 3:
			{
				for(int i=0;i<2;i++)
					monster1_1[i].time.oldtime=0;
				monster1_2.time.oldtime=0;
			}break;
		case 4:
			{
				for(int i=0;i<3;i++)
					monster1_3[i].time.oldtime=0;
			}break;
		case 5:
			{
				boss1.time.oldtime=0;
			}
	}
}

static void MoveMonster()
{
	switch(Sec)
	{
		case 1:
			switch(Pro)
			{
				case 0:
					{
						monster1_1[0].crd.x+=monster1_1[0].speed;
						monster1_1[1].crd.x-=monster1_1[1].speed;
						monster1_1[2].crd.x+=monster1_1[2].speed;
						monster1_1[1].crd.y=(HEIGHT-2.5*monster1_1[1].size.h)/2+100*sin(5*(long double)monster1_1[1].crd.x);
					}break;
				case 1:
					{
						monster1_1[0].crd.x-=monster1_1[0].speed;
						monster1_1[1].crd.x+=monster1_1[1].speed;
						monster1_1[2].crd.x-=monster1_1[2].speed;
						monster1_1[1].crd.y=(HEIGHT-2.5*monster1_1[1].size.h)/2+100*cos(5*(long double)monster1_1[1].crd.x);
					}
			}break;
		case 2:
			switch(Pro)
			{
				case 0:
					{
						for(int i=0;i<3;i++)
						{
							monster1_1[i].crd.x+=monster1_1[i].speed;
							monster1_1[i].crd.y=3*HEIGHT/14+100*cos(5*(long double)monster1_1[i].crd.x);
						}
						for(int i=3;i<7;i++)
						{
							monster1_1[i].crd.x-=monster1_1[i].speed;
							if(i!=3)	monster1_1[i].crd.y=11*HEIGHT/14-monster1_1[4].size.h+100*sin(5*(long double)monster1_1[i].crd.x);
						}
					}break;
				case 1:
					{
						for(int i=0;i<3;i++)
						{
							monster1_1[i].crd.x-=monster1_1[i].speed;
							monster1_1[i].crd.y=3*HEIGHT/14+100*sin(5*(long double)monster1_1[i].crd.x);
						}
						for(int i=3;i<7;i++)
						{
							monster1_1[i].crd.x+=monster1_1[i].speed;
							if(i!=3)	monster1_1[i].crd.y=11*HEIGHT/14-monster1_1[4].size.h+100*cos(5*(long double)monster1_1[i].crd.x);
						}
					}
			}break;
		case 3:
			switch(Pro)
			{
				case 0:
					{
						monster1_1[0].crd.x+=monster1_1[0].speed;
						monster1_1[0].crd.y=2*HEIGHT/14+100*cos(5*(long double)monster1_1[0].crd.x);
						monster1_1[1].crd.x-=monster1_1[1].speed;
						monster1_1[1].crd.y=11*HEIGHT/14+100*sin(5*(long double)monster1_1[1].crd.x);
						monster1_2.crd.x=3*WIDTH/7+R2*cos(Cir*2*PI/CIR2)+0.5;
						monster1_2.crd.y=3*HEIGHT/7+R2*sin(Cir*2*PI/CIR2)+0.5;
					}break;
				case 1:
					{
						monster1_1[0].crd.x=11*WIDTH/14+100*cos(5*(long double)monster1_1[0].crd.y);
						monster1_1[0].crd.y+=monster1_1[0].speed;
						monster1_1[1].crd.x=WIDTH/14+monster1_1[1].size.w+100*sin(5*(long double)monster1_1[1].crd.y);
						monster1_1[1].crd.y-=monster1_1[1].speed;
						monster1_2.crd.x=3*WIDTH/7+R2*cos(Cir*2*PI/CIR2)+0.5;
						monster1_2.crd.y=3*HEIGHT/7+R2*sin(Cir*2*PI/CIR2)+0.5;
					}
			}break;
		case 4:
			switch(Pro)
			{
				case 0:
					{
						for(int i=0;i<3;i++)
							monster1_3[i].crd.x+=monster1_3[i].speed;
					}break;
				case 1:
					{
						for(int i=0;i<2;i++)
							monster1_3[i].crd.x-=monster1_3[i].speed;
					}
			}break;
		case 5:
			{
				if(boss1.dir==0)	boss1.crd.x+=boss1.speed;
				else			boss1.crd.x-=boss1.speed;
			}
	}
}

static void ShowMonster()
{
	switch(Sec)
	{
		case 1:
			{
				for(int i=0;i<3;i++)
					putimage(monster1_1[i].crd.x,monster1_1[i].crd.y,&monster1_1[i].img);
			}break;
		case 2:
			{
				for(int i=0;i<7;i++)
					putimage(monster1_1[i].crd.x,monster1_1[i].crd.y,&monster1_1[i].img);
			}break;
		case 3:
			{
				for(int i=0;i<2;i++)
					putimage(monster1_1[i].crd.x,monster1_1[i].crd.y,&monster1_1[i].img);
				putimage(monster1_2.crd.x,monster1_2.crd.y,&monster1_2.img);
			}break;
		case 4:
			switch(Pro)
			{
				case 0:
					{
						for(int i=0;i<3;i++)
							putimage(monster1_3[i].crd.x,monster1_3[i].crd.y,&monster1_3[i].img[Pic]);
					}break;
				case 1:
					{
						for(int i=0;i<2;i++)
							putimage(monster1_3[i].crd.x,monster1_3[i].crd.y,&monster1_3[i].img[Pic]);
					}
			}break;
		case 5:
			{
				putimage(boss1.crd.x,boss1.crd.y,&boss1.img[Pic]);
			}
	}
}

static bool JudgeChange_Pro_or_Pic()
{
	switch(Sec)
	{
		case 1:
			{
				if(Cir%((WIDTH+monster1_1[0].size.w)/monster1_1[0].speed)==0)
				{
					Pro++;
					if(Pro>1) Pro=0;
					return 1;
				}
				return 0;
			}break;
		case 2:
			{
				if(Cir%((WIDTH+monster1_1[3].size.w)/monster1_1[3].speed+monster1_1[3].size.w)==0)
				{
					Pro++;
					if(Pro>1) Pro=0;
					return 1;
				}
				return 0;
			}break;
		case 3:
			{
				if(Cir%((WIDTH+monster1_1[0].size.w)/monster1_1[0].speed)==0)
				{
					Pro++;
					if(Pro>1) Pro=0;
					return 1;
				}
				return 0;
			}break;
		case 4:
			{
				if(Cir%1==0)	Pic++;
				if(Pic>14)		Pic=0;
				if(Cir%((WIDTH+2*monster1_3[0].size.w)/monster1_3[0].speed)==0)
				{
					Pro++;
					if(Pro>1) Pro=0;
					return 1;
				}
				return 0;
			}break;
		case 5:
			{
				if(boss1.state==0)
				{
					if(boss1.dir==0)	
					{
						Pic=4;
						if(boss1.crd.x>WIDTH)	
						{
							Cir=0;
							return 1;
						}
					}
					else
					{
						Pic=9;
						if(boss1.crd.x<-boss1.size.w)	
						{
							Cir=0;
							return 1;
						}
					}
				}
				else
				{
					if(boss1.dir==0)
					{
						if(Cir<=WIDTH/(8*boss1.speed))	Pic=0;
						else
						{
							if(Cir%5==0)	Pic++;
							if(Pic>3)		Pic=4,boss1.speed=SPEED2;
						}
						if(boss1.crd.x>WIDTH)	
						{
							Cir=0;
							return 1;
						}
					}
					else
					{
						if(Cir<WIDTH/(8*boss1.speed))	Pic=5;
						else
						{
							if(Cir%5==0)	Pic++;
							if(Pic>8)		Pic=9,boss1.speed=SPEED2;
						}
						if(boss1.crd.x<-boss1.size.w)	
						{
							Cir=0;
							return 1;
						}
					}
				}
				return 0;
			}
		default:return 0;
	}
}

void JudgeCrashMonster()
{
	switch(Sec)
	{
		case 1:
			{
				for(int i=0;i<3;i++)
				{
					for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>monster1_1[i].crd.x)&&(dataworm.crd[j].x+10<monster1_1[i].crd.x+monster1_1[i].size.w)&&(dataworm.crd[j].y>monster1_1[i].crd.y)&&(dataworm.crd[j].y+15<monster1_1[i].crd.y+monster1_1[i].size.h))
						{
							monster1_1[i].time.newtime=GetTickCount();
							if(monster1_1[i].time.newtime-monster1_1[i].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster1_1[i].dmg;
								DmgAni();
								monster1_1[i].time.oldtime=monster1_1[i].time.newtime;
							}
						}
					}
				}
			}break;

		case 2:
			{
				for(int i=0;i<7;i++)
				{
					for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>monster1_1[i].crd.x)&&(dataworm.crd[j].x+10<monster1_1[i].crd.x+monster1_1[i].size.w)&&(dataworm.crd[j].y>monster1_1[i].crd.y)&&(dataworm.crd[j].y+15<monster1_1[i].crd.y+monster1_1[i].size.h))
						{
							monster1_1[i].time.newtime=GetTickCount();
							if(monster1_1[i].time.newtime-monster1_1[i].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster1_1[i].dmg;
								DmgAni();
								monster1_1[i].time.oldtime=monster1_1[i].time.newtime;
							}
						}
					}
				}
			}break;
		case 3:
			{
				
			   for(int j=0;j<dataworm.node;j++)
			   {
					if((dataworm.crd[j].x>monster1_2.crd.x)&&(dataworm.crd[j].x+10<monster1_2.crd.x+monster1_2.size.w)&&(dataworm.crd[j].y>monster1_2.crd.y)&&(dataworm.crd[j].y+15<monster1_2.crd.y+monster1_2.size.h))
						{
							monster1_2.time.newtime=GetTickCount();
							if(monster1_2.time.newtime-monster1_2.time.oldtime>DMGTIME)
							{
								dataworm.hp-=monster1_2.dmg;
								DmgAni();
								monster1_2.time.oldtime=monster1_2.time.newtime;
							}
						}
				  for(int i=0;i<2;i++)
					{
						if((dataworm.crd[j].x>monster1_1[i].crd.x)&&(dataworm.crd[j].x+10<monster1_1[i].crd.x+monster1_1[i].size.w)&&(dataworm.crd[j].y>monster1_1[i].crd.y)&&(dataworm.crd[j].y+15<monster1_1[i].crd.y+monster1_1[i].size.h))
						{
							monster1_1[i].time.newtime=GetTickCount();
							if(monster1_1[i].time.newtime-monster1_1[i].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster1_1[i].dmg;
								DmgAni();
								monster1_1[i].time.oldtime=monster1_1[i].time.newtime;
							}
						}

					}
				}
			}break;
		case 4:
			{
				switch(Pro)
				{
				case 0:
			    {
 			    for(int i=0;i<3;i++)
				{
					for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>monster1_3[i].crd.x)&&(dataworm.crd[j].x+10<monster1_3[i].crd.x+monster1_3[i].size.w)&&(dataworm.crd[j].y>monster1_3[i].crd.y)&&(dataworm.crd[j].y+15<monster1_3[i].crd.y+monster1_3[i].size.h))
						{
							monster1_3[i].time.newtime=GetTickCount();
							if(monster1_3[i].time.newtime-monster1_3[i].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster1_3[i].dmg;
								DmgAni();
								monster1_3[i].time.oldtime=monster1_3[i].time.newtime;
							}
						}
					}
				}
				}break;
				case 1:
					{
						for(int i=0;i<2;i++)
							{
								for(int j=0;j<dataworm.node;j++)
								{
									if((dataworm.crd[j].x>monster1_3[i].crd.x)&&(dataworm.crd[j].x+10<monster1_3[i].crd.x+monster1_3[i].size.w)&&(dataworm.crd[j].y>monster1_3[i].crd.y)&&(dataworm.crd[j].y+15<monster1_3[i].crd.y+monster1_3[i].size.h))
									{
										monster1_3[i].time.newtime=GetTickCount();
										if(monster1_3[i].time.newtime-monster1_3[i].time.oldtime>DMGTIME)
										{
											dataworm.hp-=monster1_3[i].dmg;
											DmgAni();
											monster1_3[i].time.oldtime=monster1_3[i].time.newtime;
										}
									}
								}
							}
					}break;
				}
			}break;
		case 5:
			{
				for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>boss1.crd.x)&&(dataworm.crd[j].x+10<boss1.crd.x+boss1.size.w)&&(dataworm.crd[j].y>boss1.crd.y)&&(dataworm.crd[j].y+15<boss1.crd.y+boss1.size.h))
						{
							boss1.time.newtime=GetTickCount();
							if(boss1.time.newtime-boss1.time.oldtime>DMGTIME)
							{
							    dataworm.hp-=boss1.dmg;
								DmgAni();
								boss1.time.oldtime=boss1.time.newtime;
							}
						}
					}
			}
	}
}

static void SecAni()
{
	Pic1=0;
	while(1)
	{
		
		Cir++;
		ClearScreen();
		MoveMonster();
		ShowMonster();
		putimage(0,0,&bkimgani[Pic1]);
		if(Cir%2==0)	Pic1++;
		if(Pic1>20)
		{
			Cir=Pic1=0;
			return;
		}
		if(kbhit())
		{
			int c;
			c=GetCommand();
			DispatchCommand(c);
		}
		ShowDataworm();
		Sleep(35);
		FlushBatchDraw();
	}
}