#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"game.h"
#pragma comment(lib,"Winmm.lib")

///////////////////////////////////////////////////////////////////////////////////////////
NOMMONSTER monster2_1[13],monster2_3[10];
ANIMONSTER_2_2 monster2_2[2];
ANIMONSTER_2_4 monster2_4[4];
extern BOSS2 boss2;
LIGHT1 light;
LIGHT2 dmglight[5];

extern int Sec,Cir,Pro,Pic,Pic1,Getdatanum;
extern bool w3;
extern IMAGE bkimgani[21];	

extern DATA data[DATANUM];
extern DATAWORM dataworm;
////////////////////////////////////////////////////////////////////////////////////////////
void EnterGmLv2()
{
	mciSendString("open 背景音乐及音效\\音效1.mp3 alias mymusic", NULL, 0, NULL);
	mciSendString("open 背景音乐及音效\\音效2.mp3 alias mymusic", NULL, 0, NULL);
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
					mciSendString("open 背景音乐及音效\\BGM03.mp3 alias mymusic", NULL, 0, NULL);
					mciSendString("play 背景音乐及音效\\BGM03.mp3 repeat", NULL, 0, NULL);
				}
				if(Sec>5)
				{
					mciSendString("stop 背景音乐及音效\\BGM03.mp3", NULL, 0, NULL);
					mciSendString("close 背景音乐及音效\\BGM03.mp3", NULL, 0, NULL);
					mciSendString("close 背景音乐及音效\\音效1.mp3", NULL, 0, NULL);
					mciSendString("close 背景音乐及音效\\音效2.mp3", NULL, 0, NULL);
					mciSendString("open 背景音乐及音效\\BGM00.mp3 alias mymusic", NULL, 0, NULL);
					mciSendString("play 背景音乐及音效\\BGM00.mp3 repeat", NULL, 0, NULL);
					w3=true;
					return;
				}
				else	goto Lv1_1;
			}
		}
		FlushBatchDraw();
		if(Sec!=5)	Sleep(35);
		else		Sleep(25);
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
				mciSendString("close 背景音乐及音效\\音效1.mp3", NULL, 0, NULL);
				mciSendString("close 背景音乐及音效\\音效2.mp3", NULL, 0, NULL);
			}
			else
			{
				mciSendString("stop 背景音乐及音效\\BGM03.mp3", NULL, 0, NULL);
				mciSendString("close 背景音乐及音效\\BGM03.mp3", NULL, 0, NULL);
				mciSendString("close 背景音乐及音效\\音效1.mp3", NULL, 0, NULL);
				mciSendString("close 背景音乐及音效\\音效2.mp3", NULL, 0, NULL);
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
						for(int i=0;i<6;i++)
							loadimage(&monster2_1[i].img,_T("正式图\\第二关\\数据守卫1(翻转).jpg"));
						loadimage(&monster2_1[6].img,_T("正式图\\第二关\\数据守卫1(大).jpg"));
						for(int i=7;i<13;i++)
							loadimage(&monster2_1[i].img,_T("正式图\\第二关\\数据守卫1.jpg"));
					}break;
				case 1:
					{
						for(int i=0;i<6;i++)
							loadimage(&monster2_1[i].img,_T("正式图\\第二关\\数据守卫1.jpg"));
						loadimage(&monster2_1[6].img,_T("正式图\\第二关\\数据守卫1(大翻转).jpg"));
						for(int i=7;i<13;i++)
							loadimage(&monster2_1[i].img,_T("正式图\\第二关\\数据守卫1(翻转).jpg"));
					}
			}break;
		case 2:
			{
			
				for(int i=0;i<3;i++)
					loadimage(&monster2_1[i].img,_T("正式图\\第二关\\数据守卫1(翻转).jpg"));
				for(int i=3;i<6;i++)
					loadimage(&monster2_1[i].img,_T("正式图\\第二关\\数据守卫1.jpg"));
				for(int i=0;i<2;i++)
				{
					loadimage(&monster2_2[i].img[0],_T("正式图\\第二关\\数据守卫2动画_01.jpg"));
					loadimage(&monster2_2[i].img[1],_T("正式图\\第二关\\数据守卫2动画_02.jpg"));
					loadimage(&monster2_2[i].img[2],_T("正式图\\第二关\\数据守卫2动画_03.jpg"));
					loadimage(&monster2_2[i].img[3],_T("正式图\\第二关\\数据守卫2动画_04.jpg"));
					loadimage(&monster2_2[i].img[4],_T("正式图\\第二关\\数据守卫2动画_05.jpg"));
					loadimage(&monster2_2[i].img[5],_T("正式图\\第二关\\数据守卫2动画_06.jpg"));
				}
			}break;
		case 3:
			{
				for(int i=0;i<10;i++)
					loadimage(&monster2_3[i].img,_T("正式图\\第二关\\数据守卫3.jpg"));
			}break;
		case 4:
			{
				for(int i=0;i<4;i++)
				{
					loadimage(&monster2_4[i].img[0],_T("正式图\\第二关\\数据守卫4动画_01.jpg"));
					loadimage(&monster2_4[i].img[1],_T("正式图\\第二关\\数据守卫4动画_02.jpg"));
					loadimage(&monster2_4[i].img[2],_T("正式图\\第二关\\数据守卫4动画_03.jpg"));
					loadimage(&monster2_4[i].img[3],_T("正式图\\第二关\\数据守卫4动画_04.jpg"));
					loadimage(&monster2_4[i].img[4],_T("正式图\\第二关\\数据守卫4动画_05.jpg"));
					loadimage(&monster2_4[i].img[5],_T("正式图\\第二关\\数据守卫4动画_06.jpg"));
					loadimage(&monster2_4[i].img[6],_T("正式图\\第二关\\数据守卫4动画_07.jpg"));
					loadimage(&monster2_4[i].img[7],_T("正式图\\第二关\\数据守卫4动画_08.jpg"));
				}
			}break;
		case 5:
			{
				loadimage(&boss2.img[0],_T("正式图\\第二关\\BOSS2.jpg"));
				loadimage(&boss2.img[1],_T("正式图\\第二关\\BOSS2(破坏光线1).jpg"));
				loadimage(&boss2.img[2],_T("正式图\\第二关\\BOSS2(破坏光线2).jpg"));
				loadimage(&boss2.img[3],_T("正式图\\第二关\\BOSS2(破坏光线3).jpg"));
				loadimage(&light.img[0],_T("正式图\\第二关\\聚光束动画_01.jpg"));
				loadimage(&light.img[1],_T("正式图\\第二关\\聚光束动画_02.jpg"));
				loadimage(&light.img[2],_T("正式图\\第二关\\聚光束动画_03.jpg"));
				loadimage(&light.img[3],_T("正式图\\第二关\\聚光束动画_04.jpg"));
				loadimage(&light.img[4],_T("正式图\\第二关\\聚光束动画_03.jpg"));
				loadimage(&light.img[5],_T("正式图\\第二关\\聚光束动画_02.jpg"));
				loadimage(&light.img[6],_T("正式图\\第二关\\聚光束动画_01.jpg"));
				for(int i=0;i<5;i++)
				{
					loadimage(&dmglight[i].img[0],_T("正式图\\第二关\\破坏光线动画_01.jpg"));
					loadimage(&dmglight[i].img[1],_T("正式图\\第二关\\破坏光线动画_02.jpg"));
					loadimage(&dmglight[i].img[2],_T("正式图\\第二关\\破坏光线动画_03.jpg"));
					loadimage(&dmglight[i].img[3],_T("正式图\\第二关\\破坏光线动画_04.jpg"));
					loadimage(&dmglight[i].img[4],_T("正式图\\第二关\\破坏光线动画_03.jpg"));
					loadimage(&dmglight[i].img[5],_T("正式图\\第二关\\破坏光线动画_04.jpg"));
					loadimage(&dmglight[i].img[6],_T("正式图\\第二关\\破坏光线动画_03.jpg"));
					loadimage(&dmglight[i].img[7],_T("正式图\\第二关\\破坏光线动画_02.jpg"));
					loadimage(&dmglight[i].img[8],_T("正式图\\第二关\\破坏光线动画_01.jpg"));
				}
			}break;
		default:;
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
						monster2_1[0].crd.x=-monster2_1[0].size.w,										monster2_1[0].crd.y=HEIGHT/7;
						for(int i=1;i<6;i++)
						{
							if(i!=3)	monster2_1[i].crd.x=monster2_1[i-1].crd.x-monster2_1[i].size.w-WIDTH/14;
							else		monster2_1[i].crd.x=monster2_1[i-1].crd.x-monster2_1[i].size.w-5*WIDTH/14;
							monster2_1[i].crd.y=monster2_1[i-1].crd.y;
						}
						monster2_1[6].crd.x=WIDTH,														monster2_1[6].crd.y=(HEIGHT-monster2_1[6].size.h)/2;
						for(int i=7;i<13;i++)
						{
							if(i!=10)	monster2_1[i].crd.x=monster2_1[i-1].crd.x+monster2_1[i].size.w+WIDTH/14;
							else		monster2_1[i].crd.x=monster2_1[i-1].crd.x+monster2_1[i].size.w+5*WIDTH/14;
							monster2_1[i].crd.y=6*HEIGHT/7-monster2_1[i].size.h;
						}
					}break;
				case 1:
					{
						monster2_1[0].crd.x=WIDTH,														monster2_1[0].crd.y=HEIGHT/7;
						for(int i=1;i<6;i++)
						{
							if(i!=3) monster2_1[i].crd.x=monster2_1[i-1].crd.x+monster2_1[i].size.w+WIDTH/14;
							else	 monster2_1[i].crd.x=monster2_1[i-1].crd.x+monster2_1[i].size.w+5*WIDTH/14;
							monster2_1[i].crd.y=monster2_1[i-1].crd.y;
						}
						monster2_1[6].crd.x=-monster2_1[6].size.w,										monster2_1[6].crd.y=(HEIGHT-monster2_1[6].size.h)/2;
						for(int i=7;i<13;i++)
						{
							if(i!=10)	monster2_1[i].crd.x=monster2_1[i-1].crd.x-monster2_1[i].size.w-WIDTH/14;
							else		monster2_1[i].crd.x=monster2_1[i-1].crd.x-monster2_1[i].size.w-5*WIDTH/14;
							monster2_1[i].crd.y=6*HEIGHT/7-monster2_1[i].size.h;
						}
					}
			}break;
		case 2:
			switch(Pro)
			{
				case 0:
					{
						monster2_1[0].crd.x=-WIDTH/7,monster2_1[0].crd.y=0;
						for(int i=1;i<3;i++)
						{
							monster2_1[i].crd.x=monster2_1[i-1].crd.x-WIDTH/7;
							monster2_1[i].crd.y=monster2_1[i-1].crd.y-HEIGHT/7;
						}
						monster2_1[3].crd.x=8*WIDTH/7-monster2_1[3].size.w,								monster2_1[3].crd.y=6*HEIGHT/7;
						for(int i=4;i<6;i++)
						{
							monster2_1[i].crd.x=monster2_1[i-1].crd.x+WIDTH/7;
							monster2_1[i].crd.y=monster2_1[i-1].crd.y+HEIGHT/7;
						}
						monster2_2[0].crd.x=9*WIDTH/14+R2*cos(Cir*2*PI/CIR3)+0.5,						monster2_2[0].crd.y=3*HEIGHT/14+R2*sin(Cir*2*PI/CIR3)+0.5;
						monster2_2[1].crd.x=3*WIDTH/14+R2*cos(Cir*2*PI/CIR3)+0.5,						monster2_2[1].crd.y=9*WIDTH/14-R2*sin(Cir*2*PI/CIR3)+0.5;
					}break;
				case 1:
					{
						monster2_1[0].crd.x=0,															monster2_1[0].crd.y=-HEIGHT/7;
						for(int i=1;i<3;i++)
						{
							monster2_1[i].crd.x=monster2_1[i-1].crd.x-WIDTH/7;
							monster2_1[i].crd.y=monster2_1[i-1].crd.y-HEIGHT/7;
						}
						monster2_1[3].crd.x=6*WIDTH/7-monster2_1[3].size.w,								monster2_1[3].crd.y=6*HEIGHT/7;
						for(int i=4;i<6;i++)
						{
							monster2_1[i].crd.x=monster2_1[i-1].crd.x+WIDTH/7;
							monster2_1[i].crd.y=monster2_1[i-1].crd.y+HEIGHT/7;
						}
					}
			}break;
		case 3:
			{
						monster2_3[0].crd.x=11*WIDTH/250;
						for(int i=1;i<10;i++)
							monster2_3[i].crd.x=monster2_3[i-1].crd.x+11*WIDTH/100;
						monster2_3[2].crd.y=-monster2_3[2].size.h;
						monster2_3[6].crd.y=monster2_3[2].crd.y-HEIGHT/5;
						monster2_3[3].crd.y=monster2_3[8].crd.y=monster2_3[6].crd.y-HEIGHT/5;
						monster2_3[1].crd.y=monster2_3[7].crd.y=monster2_3[3].crd.y-HEIGHT/5;
						monster2_3[0].crd.y=monster2_3[5].crd.y=monster2_3[9].crd.y=monster2_3[1].crd.y-HEIGHT/5;
						monster2_3[4].crd.y=monster2_3[0].crd.y-HEIGHT/5;
			}break;
		case 4:
			{
				monster2_4[0].crd.x=3*WIDTH/14+R1*cos(Cir*2*PI/CIR2)+0.5,					monster2_4[0].crd.y=3*HEIGHT/14-R1*sin(Cir*2*PI/CIR2)+0.5;
				monster2_4[1].crd.x=9*WIDTH/14+R1*cos(Cir*2*PI/CIR2)+0.5,					monster2_4[1].crd.y=3*HEIGHT/14+R1*sin(Cir*2*PI/CIR2)+0.5;
				monster2_4[2].crd.x=3*WIDTH/14+R1*cos(Cir*2*PI/CIR2)+0.5,					monster2_4[2].crd.y=9*HEIGHT/14+R1*sin(Cir*2*PI/CIR2)+0.5;
				monster2_4[3].crd.x=9*WIDTH/14+R1*cos(Cir*2*PI/CIR2)+0.5,					monster2_4[3].crd.y=9*HEIGHT/14-R1*sin(Cir*2*PI/CIR2)+0.5;
			}break;
		case 5:
			{
				switch(boss2.state)
				{
					case 0:
						{
							boss2.crd.x=(WIDTH-boss2.size.w)/2;
							boss2.crd.y=-boss2.size.h;
						}break;
					case 2:
						{
							light.crd.x=boss2.crd.x+2*boss2.size.w/5;
							light.crd.y=270;
						}break;
					case 4:
						{
							for(int i=0;i<5;i++)
							{
								dmglight[i].crd.x=0;
								dmglight[i].crd.y=rand()%39+260+i*88;
							}
						}break;
					default:;
				}
			}break;
		default:;
	}
}


static void InitMonsterSpeed()
{
	switch(Sec)
	{
		case 1:
			{
				for(int i=0;i<6;i++)
					monster2_1[i].speed=SPEED3;
				monster2_1[6].speed=SPEED2;
				for(int i=7;i<13;i++)
					monster2_1[i].speed=SPEED3;
			}break;
		case 2:
			{
				for(int i=0;i<6;i++)
					monster2_1[i].speed=SPEED2;
			}break;
		case 3:
			{
				for(int i=0;i<10;i++)
					monster2_3[i].speed=SPEED5;
			}break;
		default:;
	}
}

static void InitMonsterSize()
{
	switch(Sec)
	{
		case 1:
			{
				for(int i=0;i<13;i++)
				{
					if(i!=6)	monster2_1[i].size.w=50,	monster2_1[i].size.h=55;
					else		monster2_1[i].size.w=100,	monster2_1[i].size.h=116;
				}
			}break;
		case 2:
			{
				for(int i=0;i<6;i++)
					monster2_1[i].size.w=50,	monster2_1[i].size.h=55;
				for(int i=0;i<2;i++)
					monster2_2[i].size.w=100,	monster2_2[i].size.h=100;
			}break;
		case 3:
			{
				for(int i=0;i<10;i++)
					monster2_3[i].size.w=25,	monster2_3[i].size.h=157;
			}break;
		case 4:
			{
				for(int i=0;i<4;i++)
					monster2_4[i].size.w=100,	monster2_4[i].size.h=120;
			}break;
		case 5:
			{
				boss2.size.w=250,				boss2.size.h=260;
				light.size.w=38,				light.size.h=500;
				for(int i=0;i<5;i++)
				{
					dmglight[i].size.w=700;
					dmglight[i].size.h=50;
				}
			}break;
		default:;
	}
}

static void InitMonsterDmg()
{
	switch(Sec)
	{
		case 1:
			{
				for(int i=0;i<13;i++)
				{
					if(i!=6)	monster2_1[i].dmg=DMG1;
					else		monster2_1[i].dmg=DMG2;
				}
			}break;
		case 2:
			{
				for(int i=0;i<6;i++)
					monster2_1[i].dmg=DMG1;
				for(int i=0;i<2;i++)
					monster2_2[i].dmg=DMG2;
			}break;
		case 3:
			{
				for(int i=0;i<10;i++)
					monster2_3[i].dmg=DMG1;
			}break;
		case 4:
			{
				for(int i=0;i<4;i++)
				{
					monster2_4[i].dmg=DMG2;
				}
			}break;
		case 5:
			{
				boss2.dmg=DMG4;
				light.dmg=DMG1;
				for(int i=0;i<5;i++)
					dmglight[i].dmg=DMG3;
			}break;
		default:;
	}
}

static void InitMonsterDmgTime()
{
	switch(Sec)
	{
		case 1:
			{
				for(int i=0;i<13;i++)
					monster2_1[i].time.oldtime=0;
			}break;
		case 2:
			{
				for(int i=0;i<6;i++)
					monster2_1[i].time.oldtime=0;
				for(int i=0;i<2;i++)
					monster2_2[i].time.oldtime=0;
			}break;
		case 3:
			{
				for(int i=0;i<10;i++)
					monster2_3[i].time.oldtime=0;
			}break;
		case 4:
			{
				for(int i=0;i<4;i++)
					monster2_4[i].time.oldtime=0;
			}break;
		case 5:
			{
				boss2.dmgtime.oldtime=0;
				light.time.oldtime=0;
				for(int i=0;i<5;i++)
					dmglight[i].time.oldtime=0;
			}break;
		default:;
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
						for(int i=0;i<6;i++)
							monster2_1[i].crd.x+=monster2_1[i].speed;
						for(int i=6;i<13;i++)
							monster2_1[i].crd.x-=monster2_1[i].speed;
						if(((monster2_1[6].crd.x>-monster2_1[6].size.w)&&(monster2_1[6].crd.x<WIDTH/4))||((monster2_1[6].crd.x>3*WIDTH/4)&&(monster2_1[6].crd.x<WIDTH)))
							monster2_1[6].crd.y+=HEIGHT/350;
						else	monster2_1[6].crd.y-=HEIGHT/350;
					}break;
				case 1:
					{
						for(int i=0;i<6;i++)
							monster2_1[i].crd.x-=monster2_1[i].speed;
						for(int i=6;i<13;i++)
							monster2_1[i].crd.x+=monster2_1[i].speed;
						if(((monster2_1[6].crd.x>0)&&(monster2_1[6].crd.x<WIDTH/4+monster2_1[6].size.w))||((monster2_1[6].crd.x>3*WIDTH/4+monster2_1[6].size.w)&&(monster2_1[6].crd.x<WIDTH+monster2_1[6].size.w)))
							monster2_1[6].crd.y+=HEIGHT/350;
						else	monster2_1[6].crd.y-=HEIGHT/350;
					}
			}break;
		case 2:
			{
				for(int i=0;i<3;i++)
				{
					monster2_1[i].crd.x+=monster2_1[i].speed;
					monster2_1[i].crd.y+=monster2_1[i].speed;
				}
				for(int i=3;i<6;i++)
				{
					monster2_1[i].crd.x-=monster2_1[i].speed;
					monster2_1[i].crd.y-=monster2_1[i].speed;
				}
					monster2_2[0].crd.x=9*WIDTH/14+R2*cos(Cir*2*PI/CIR3)+0.5,				monster2_2[0].crd.y=3*HEIGHT/14+R2*sin(Cir*2*PI/CIR3)+0.5;
					monster2_2[1].crd.x=3*WIDTH/14+R2*cos(Cir*2*PI/CIR3)+0.5,				monster2_2[1].crd.y=9*WIDTH/14-R2*sin(Cir*2*PI/CIR3)+0.5;
			}break;
		case 3:
			{
					for(int i=0;i<10;i++)
					{
						monster2_3[i].crd.y+=monster2_3[i].speed;
						if(monster2_3[i].crd.y>HEIGHT)	monster2_3[i].crd.y=-monster2_3[i].size.h;
					}
			}break;
		case 4:
			switch(Pro)
			{
				case 0:
					{
							monster2_4[0].crd.x=3*WIDTH/14+R1*cos(Cir*2*PI/CIR1)+0.5,					monster2_4[0].crd.y=3*HEIGHT/14-R1*sin(Cir*2*PI/CIR2)+0.5;
							monster2_4[1].crd.x=9*WIDTH/14+R1*cos(Cir*2*PI/CIR1)+0.5,					monster2_4[1].crd.y=3*HEIGHT/14+R1*sin(Cir*2*PI/CIR2)+0.5;
							monster2_4[2].crd.x=3*WIDTH/14+R1*cos(Cir*2*PI/CIR1)+0.5,					monster2_4[2].crd.y=9*HEIGHT/14+R1*sin(Cir*2*PI/CIR2)+0.5;
							monster2_4[3].crd.x=9*WIDTH/14+R1*cos(Cir*2*PI/CIR1)+0.5,					monster2_4[3].crd.y=9*HEIGHT/14-R1*sin(Cir*2*PI/CIR2)+0.5;
					}break;
				case 1:
					{
							monster2_4[0].crd.x=3*WIDTH/14+R1*cos(Cir*2*PI/CIR2)+0.5,					monster2_4[0].crd.y=3*HEIGHT/14+R1*sin(Cir*2*PI/CIR2)+0.5;
							monster2_4[1].crd.x=9*WIDTH/14+R1*cos(Cir*2*PI/CIR2)+0.5,					monster2_4[1].crd.y=3*HEIGHT/14-R1*sin(Cir*2*PI/CIR2)+0.5;
							monster2_4[2].crd.x=3*WIDTH/14+R1*cos(Cir*2*PI/CIR2)+0.5,					monster2_4[2].crd.y=9*HEIGHT/14-R1*sin(Cir*2*PI/CIR2)+0.5;
							monster2_4[3].crd.x=9*WIDTH/14+R1*cos(Cir*2*PI/CIR2)+0.5,					monster2_4[3].crd.y=9*HEIGHT/14+R1*sin(Cir*2*PI/CIR2)+0.5;
					}
			}break;
		case 5:
			{
				if(boss2.state==0)
				{
					if(boss2.crd.y<0)  boss2.crd.y+=5;
					else						boss2.state=1;
				}
				else if(boss2.state==1)
				{
					if(dataworm.crd[0].y>=0&&dataworm.crd[0].y<=boss2.size.h)
					{
						if(boss2.crd.x+boss2.size.w/2-dataworm.crd[0].x>10)
						{
							boss2.crd.x-=10;
							if(boss2.crd.x<0)	boss2.crd.x=0;
						}
						else if(dataworm.crd[0].x-(boss2.crd.x+boss2.size.w/2)>10)
						{
							boss2.crd.x+=10;
							if(boss2.crd.x>WIDTH-boss2.size.w)	boss2.crd.x=WIDTH-boss2.size.w;
						}
						else;
					}
					else
					{
						if(boss2.crd.x+boss2.size.w/2-dataworm.crd[0].x>10)
						{
							boss2.crd.x-=5;
							if(boss2.crd.x<0)	boss2.crd.x=0;
						}
						else if(dataworm.crd[0].x-(boss2.crd.x+boss2.size.w/2)>10)
						{
							boss2.crd.x+=5;
							if(boss2.crd.x>WIDTH-boss2.size.w)	boss2.crd.x=WIDTH-boss2.size.w;
						}
						else if(boss2.time.newtime-boss2.time.oldtime>2000)
						{
							boss2.state=2;
							mciSendString("play 背景音乐及音效\\音效2.mp3", NULL, 0, NULL);
							InitMonsterCrd();
						}
					}
				}
			}break;
		default:;
	}
}

static void ShowMonster()
{
	switch(Sec)
	{
		case 1:
			{
				for(int i=0;i<13;i++)
					putimage(monster2_1[i].crd.x,monster2_1[i].crd.y,&monster2_1[i].img);
			}break;
		case 2:
			{
				for(int i=0;i<6;i++)
					putimage(monster2_1[i].crd.x,monster2_1[i].crd.y,&monster2_1[i].img);
				for(int i=0;i<2;i++)
					putimage(monster2_2[i].crd.x,monster2_2[i].crd.y,&monster2_2[i].img[Pic]);
			}break;
		case 3:
			{
				for(int i=0;i<10;i++)
					putimage(monster2_3[i].crd.x,monster2_3[i].crd.y,&monster2_3[i].img);
			}break;
		case 4:
			{
				for(int i=0;i<4;i++)
					putimage(monster2_4[i].crd.x,monster2_4[i].crd.y,&monster2_4[i].img[Pic]);
			}break;
		case 5:
			{
				switch(boss2.state)
				{
					case 0:	
					case 1:	putimage(boss2.crd.x,boss2.crd.y,&boss2.img[0]);break;
					case 2:
						{
							putimage(boss2.crd.x,boss2.crd.y,&boss2.img[0]);
							putimage(light.crd.x,light.crd.y,&light.img[Pic]);
						}break;
					case 3:	putimage(boss2.crd.x,boss2.crd.y,&boss2.img[Pic]);break;
					case 4:
						{
							putimage(boss2.crd.x,boss2.crd.y,&boss2.img[3]);
							for(int i=0;i<5;i++)
								putimage(dmglight[i].crd.x,dmglight[i].crd.y,&dmglight[i].img[Pic]);
						}break;
					default:;
				}
			}break;
		default:;
	}
}

static bool JudgeChange_Pro_or_Pic()
{
	switch(Sec)
	{
		case 1:
			{
				if(Cir%((16*WIDTH/7+monster2_1[0].size.w)/monster2_1[0].speed)==0)
				{
					Pro++;
					if(Pro>1) Pro=0;
					return 1;
				}
				return 0;
			}break;
		case 2:
			{
				if(Cir%5==0)	Pic++;
				if(Pic>5)		Pic=0;
				if(Cir%(int)((sqrt((long double)((9*HEIGHT/7)*(9*HEIGHT/7)+(9*WIDTH/7)*(9*WIDTH/7)))/monster2_1[0].speed)+1)==0)
				{
					Pro++;
					if(Pro>1) Pro=0;
					return 1;
				}
				return 0;
			}break;
		case 3:
			{
				return 0;
			}break;
		case 4:
			{
				if(Cir%1==0)	Pic++;
				if(Pic>7)		Pic=0;
				if(Cir%(3*CIR2)==0)
				{
					Pro++;
					if(Pro>1) Pro=0;
					return 1;
				}
				return 0;
			}break;
		case 5:
			{
				switch(boss2.state)
				{
					case 0:boss2.time.oldtime=GetTickCount();break;
					case 2:
						{
							++Cir;
							if(Cir%3==0)
							{
								Pic++;
								if(Pic>6)
								{
									boss2.state=1;
									boss2.time.oldtime=GetTickCount();
									Pic=Cir=0;
								}
							}
						}break;
					case 3:
						{
							++Cir;
							if(Cir%5==0)
							{
								Pic++;		
								if(Pic>3)
								{
									boss2.state=4;
									InitMonsterCrd();
									Pic=Cir=0;
								}			
							}
						}break;
					case 4:
						{
							++Cir;
							if(Cir%3==0)
							{
								Pic++;
								if(Pic>8)
								{
									boss2.state=1;
									boss2.time.oldtime=GetTickCount();
									Pic=Cir=0;
								}
							}
						}break;
					default:;
				}
				boss2.time.newtime=GetTickCount();
				if((boss2.state==1)&&(boss2.time.newtime-boss2.time.oldtime>4000))
				{
					boss2.state=3;
					mciSendString("play 背景音乐及音效\\音效1.mp3", NULL, 0, NULL);
				}
				Sleep(1);
			}
	}
}

static void JudgeCrashMonster()
{
	switch(Sec)
	{
		case 1:
			{
				for(int i=0;i<13;i++)
				{
					for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>monster2_1[i].crd.x)&&(dataworm.crd[j].x+10<monster2_1[i].crd.x+monster2_1[i].size.w)&&(dataworm.crd[j].y>monster2_1[i].crd.y)&&(dataworm.crd[j].y+15<monster2_1[i].crd.y+monster2_1[i].size.h))
						{
							monster2_1[i].time.newtime=GetTickCount();
							if(monster2_1[i].time.newtime-monster2_1[i].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster2_1[i].dmg;
								DmgAni();
								monster2_1[i].time.oldtime=monster2_1[i].time.newtime;
							}
						}
					}
				}
			}break;

			case 2:
			{
				for(int i=0;i<6;i++)
				{
					for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>monster2_1[i].crd.x)&&(dataworm.crd[j].x+10<monster2_1[i].crd.x+monster2_1[i].size.w)&&(dataworm.crd[j].y>monster2_1[i].crd.y)&&(dataworm.crd[j].y+15<monster2_1[i].crd.y+monster2_1[i].size.h))
						{
							monster2_1[i].time.newtime=GetTickCount();
							if(monster2_1[i].time.newtime-monster2_1[i].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster2_1[i].dmg;
								DmgAni();
								monster2_1[i].time.oldtime=monster2_1[i].time.newtime;
							}
						}
					}
				}
				for(int k=0;k<2;k++)
				{
					for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>monster2_2[k].crd.x)&&(dataworm.crd[j].x+10<monster2_2[k].crd.x+monster2_2[k].size.w)&&(dataworm.crd[j].y>monster2_2[k].crd.y)&&(dataworm.crd[j].y+15<monster2_2[k].crd.y+monster2_2[k].size.h))
						{
							monster2_2[k].time.newtime=GetTickCount();
							if(monster2_2[k].time.newtime-monster2_2[k].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster2_2[k].dmg;
								DmgAni();
								monster2_2[k].time.oldtime=monster2_2[k].time.newtime;
							}
						}
					}
				}
			}break;


			case 3:
			{
				for(int i=0;i<10;i++)
				{
					for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>monster2_3[i].crd.x)&&(dataworm.crd[j].x+10<monster2_3[i].crd.x+monster2_3[i].size.w)&&(dataworm.crd[j].y>monster2_3[i].crd.y)&&(dataworm.crd[j].y+15<monster2_3[i].crd.y+monster2_3[i].size.h))
						{
							monster2_3[i].time.newtime=GetTickCount();
							if(monster2_3[i].time.newtime-monster2_3[i].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster2_3[i].dmg;
								DmgAni();
								monster2_3[i].time.oldtime=monster2_3[i].time.newtime;
							}
						}
					}
				}
			}break;

			case 4:
			{
				for(int i=0;i<4;i++)
				{
					for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>monster2_4[i].crd.x)&&(dataworm.crd[j].x+10<monster2_4[i].crd.x+monster2_4[i].size.w)&&(dataworm.crd[j].y>monster2_4[i].crd.y)&&(dataworm.crd[j].y+15<monster2_4[i].crd.y+monster2_4[i].size.h))
						{
							monster2_4[i].time.newtime=GetTickCount();
							if(monster2_4[i].time.newtime-monster2_4[i].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster2_4[i].dmg;
								DmgAni();
								monster2_4[i].time.oldtime=monster2_4[i].time.newtime;
							}
						}
					}
				}
			}break;
			case 5:
			{
				switch(boss2.state)
				{
					case 0:
					case 1:
					case 3:
					{
						for(int j=0;j<dataworm.node;j++)
						{
							if((dataworm.crd[j].x>boss2.crd.x)&&(dataworm.crd[j].x+10<boss2.crd.x+boss2.size.w)&&(dataworm.crd[j].y>boss2.crd.y)&&(dataworm.crd[j].y+15<boss2.crd.y+boss2.size.h))
							{
								boss2.dmgtime.newtime=GetTickCount();
								if(boss2.dmgtime.newtime-boss2.dmgtime.oldtime>DMGTIME)
								{
									dataworm.hp-=boss2.dmg;
									DmgAni();
									boss2.dmgtime.oldtime=boss2.dmgtime.newtime;
								}
							}
						}
					}break;
					case 2:
						{
							for(int j=0;j<dataworm.node;j++)
							{
								if((dataworm.crd[j].x>boss2.crd.x)&&(dataworm.crd[j].x+10<boss2.crd.x+boss2.size.w)&&(dataworm.crd[j].y>boss2.crd.y)&&(dataworm.crd[j].y+15<boss2.crd.y+boss2.size.h))
								{
									boss2.dmgtime.newtime=GetTickCount();
									if(boss2.dmgtime.newtime-boss2.dmgtime.oldtime>DMGTIME)
									{
									    dataworm.hp-=boss2.dmg;
										DmgAni();
										boss2.dmgtime.oldtime=boss2.dmgtime.newtime;
									}
								}
								if((dataworm.crd[j].x>light.crd.x)&&(dataworm.crd[j].x+10<light.crd.x+light.size.w)&&(dataworm.crd[j].y>light.crd.y)&&(dataworm.crd[j].y+15<light.crd.y+light.size.h))
								{
									light.time.newtime=GetTickCount();
									if((light.time.newtime-light.time.oldtime>DMGTIME)&&(Pic>=2))
									{
									    dataworm.hp-=light.dmg;
										DmgAni();
										light.time.oldtime=light.time.newtime;
									}
								}
							}
						}break;
					case 4:
						{
							for(int j=0;j<dataworm.node;j++)
							{
								if((dataworm.crd[j].x>boss2.crd.x)&&(dataworm.crd[j].x+10<boss2.crd.x+boss2.size.w)&&(dataworm.crd[j].y>boss2.crd.y)&&(dataworm.crd[j].y+15<boss2.crd.y+boss2.size.h))
								{
									boss2.dmgtime.newtime=GetTickCount();
									if(boss2.dmgtime.newtime-boss2.dmgtime.oldtime>DMGTIME)
									{
									    dataworm.hp-=boss2.dmg;
										DmgAni();
										boss2.dmgtime.oldtime=boss2.dmgtime.newtime;
									}
								}
								for(int i=0;i<5;i++)
									if((dataworm.crd[j].x>dmglight[i].crd.x)&&(dataworm.crd[j].x+10<dmglight[i].crd.x+dmglight[i].size.w)&&(dataworm.crd[j].y>dmglight[i].crd.y)&&(dataworm.crd[j].y+15<dmglight[i].crd.y+dmglight[i].size.h))
									{
										dmglight[i].time.newtime=GetTickCount();
										if((dmglight[i].time.newtime-dmglight[i].time.oldtime>DMGTIME)&&(Pic>=2))
										{
											dataworm.hp-=dmglight[i].dmg;
											DmgAni();
											dmglight[i].time.oldtime=dmglight[i].time.newtime;
										}
									}
							}
						}break;
					default:;
				}
			}break;
			default:;
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