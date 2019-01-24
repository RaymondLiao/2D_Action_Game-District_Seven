#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"game.h"
#pragma comment(lib,"Winmm.lib")

///////////////////////////////////////////////////////////////////////////////////////////
NOMMONSTER monster3_1[24],reaper[16],dataeroder[24];
ANIMONSTER_3_2 monster3_2[5];
ANIMONSTER_3_3 monster3_3[39];
ANIMONSTER_3_4 monster3_4[17];
extern BOSS3 boss3;

extern int Sec,Cir,Pro,Pic,Pic1,Getdatanum;
extern IMAGE bkimgani[21];	
static double tat;

extern DATA data[DATANUM];
extern DATAWORM dataworm;

static int c=300;			//第四小节怪物的初始旋转周期
static double r1=sqrt((long double)2)*WIDTH/10,
			  r2=WIDTH/5,
			  r3=sqrt((long double)2)*WIDTH/5,
			  r4=sqrt((long double)((3*WIDTH/10)*(3*WIDTH/10)+(HEIGHT/10)*(HEIGHT/10))),
			  r5=2*WIDTH/5;
////////////////////////////////////////////////////////////////////////////////////////////
void EnterGmLv3()
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
		MoveMonster();
		ShowMonster();
		for(int i=0;i<DATANUM;i++)
			if(data[i].flag==1)		ShowData(data[i].crd.x,data[i].crd.y,data[i].type);
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
					mciSendString("open 背景音乐及音效\\BGM05.mp3 alias mymusic", NULL, 0, NULL);
					mciSendString("play 背景音乐及音效\\BGM05.mp3 repeat", NULL, 0, NULL);
				}
				if(Sec>5)
				{
					mciSendString("stop 背景音乐及音效\\BGM05.mp3", NULL, 0, NULL);
					mciSendString("close 背景音乐及音效\\BGM05.mp3", NULL, 0, NULL);
					mciSendString("open 背景音乐及音效\\BGM00.mp3 alias mymusic", NULL, 0, NULL);
					mciSendString("play 背景音乐及音效\\BGM00.mp3 repeat", NULL, 0, NULL);
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
			}
			else
			{
				mciSendString("stop 背景音乐及音效\\BGM05.mp3", NULL, 0, NULL);
				mciSendString("close 背景音乐及音效\\BGM05.mp3", NULL, 0, NULL);
			}
			mciSendString("open 背景音乐及音效\\BGM00.mp3 alias mymusic", NULL, 0, NULL);
			mciSendString("play 背景音乐及音效\\BGM00.mp3 repeat", NULL, 0, NULL);
			c=300;
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
						for(int i=0;i<8;i++)
							loadimage(&monster3_1[i].img,_T("正式图\\第三关\\数据守卫.jpg"));
						for(int i=8;i<24;i++)
							loadimage(&monster3_1[i].img,_T("正式图\\第三关\\数据守卫(翻转).jpg"));
					}break;
				case 1:
					{
						for(int i=0;i<16;i++)
							loadimage(&monster3_1[i].img,_T("正式图\\第三关\\数据守卫.jpg"));
						for(int i=16;i<24;i++)
							loadimage(&monster3_1[i].img,_T("正式图\\第三关\\数据守卫(翻转).jpg"));
					}
			}break;
		case 2:
			{
				loadimage(&monster3_2[0].img[0],_T("正式图\\第三关\\矩阵锯轮(大)动画_01.jpg"));
				loadimage(&monster3_2[0].img[1],_T("正式图\\第三关\\矩阵锯轮(大)动画_02.jpg"));
				loadimage(&monster3_2[0].img[2],_T("正式图\\第三关\\矩阵锯轮(大)动画_03.jpg"));
				for(int i=1;i<5;i++)
				{
					loadimage(&monster3_2[i].img[0],_T("正式图\\第三关\\矩阵锯轮动画_01.jpg"));
					loadimage(&monster3_2[i].img[1],_T("正式图\\第三关\\矩阵锯轮动画_02.jpg"));
					loadimage(&monster3_2[i].img[2],_T("正式图\\第三关\\矩阵锯轮动画_03.jpg"));
				}
			}break;
		case 3:
			{
				for(int i=0;i<39;i++)
				{
					loadimage(&monster3_3[i].img[0],_T("正式图\\第三关\\结点陷阱动画_01.jpg"));
					loadimage(&monster3_3[i].img[1],_T("正式图\\第三关\\结点陷阱动画_02.jpg"));
					loadimage(&monster3_3[i].img[2],_T("正式图\\第三关\\结点陷阱动画_03.jpg"));
					loadimage(&monster3_3[i].img[3],_T("正式图\\第三关\\结点陷阱动画_03.jpg"));
					loadimage(&monster3_3[i].img[4],_T("正式图\\第三关\\结点陷阱动画_03.jpg"));
					loadimage(&monster3_3[i].img[5],_T("正式图\\第三关\\结点陷阱动画_03.jpg"));
					loadimage(&monster3_3[i].img[6],_T("正式图\\第三关\\结点陷阱动画_02.jpg"));
				}
			}break;
		case 4:
			{
				for(int i=0;i<17;i++)
				{
					if((i!=0)&&(i!=8)&&(i!=16))
					{
						loadimage(&monster3_4[i].img[0],_T("正式图\\第三关\\能量团动画_01.jpg"));
						loadimage(&monster3_4[i].img[1],_T("正式图\\第三关\\能量团动画_02.jpg"));
						loadimage(&monster3_4[i].img[2],_T("正式图\\第三关\\能量团动画_03.jpg"));
					}
					else
					{
						loadimage(&monster3_4[i].img[0],_T("正式图\\第三关\\能量团(强)动画_01.jpg"));
						loadimage(&monster3_4[i].img[1],_T("正式图\\第三关\\能量团(强)动画_02.jpg"));
						loadimage(&monster3_4[i].img[2],_T("正式图\\第三关\\能量团(强)动画_03.jpg"));
					}
				}
			}break;
		case 5:
			{
				loadimage(&boss3.img0[0],_T("正式图\\第三关\\BOSS3(隐身5).jpg"));
				loadimage(&boss3.img0[1],_T("正式图\\第三关\\BOSS3(隐身4).jpg"));
				loadimage(&boss3.img0[2],_T("正式图\\第三关\\BOSS3(隐身3).jpg"));
				loadimage(&boss3.img0[3],_T("正式图\\第三关\\BOSS3(隐身2).jpg"));
				loadimage(&boss3.img0[4],_T("正式图\\第三关\\BOSS3(隐身1).jpg"));
				
				loadimage(&boss3.img1,_T("正式图\\第三关\\BOSS3(隐身1).jpg"));
				
				loadimage(&boss3.img2[0],_T("正式图\\第三关\\BOSS3(收割1).jpg"));
				loadimage(&boss3.img2[1],_T("正式图\\第三关\\BOSS3(收割2).jpg"));
				loadimage(&boss3.img2[2],_T("正式图\\第三关\\BOSS3(收割3).jpg"));
				loadimage(&boss3.img2[3],_T("正式图\\第三关\\BOSS3(收割4).jpg"));
				loadimage(&boss3.img2[4],_T("正式图\\第三关\\BOSS3(收割5).jpg"));
				loadimage(&boss3.img2[5],_T("正式图\\第三关\\BOSS3(收割6).jpg"));
				loadimage(&boss3.img2[6],_T("正式图\\第三关\\BOSS3(收割7).jpg"));

				loadimage(&boss3.img3[0],_T("正式图\\第三关\\BOSS3(数据侵蚀1).jpg"));
				loadimage(&boss3.img3[1],_T("正式图\\第三关\\BOSS3(数据侵蚀2).jpg"));
				loadimage(&boss3.img3[2],_T("正式图\\第三关\\BOSS3(数据侵蚀3).jpg"));
				loadimage(&boss3.img3[3],_T("正式图\\第三关\\BOSS3(数据侵蚀4).jpg"));
				loadimage(&boss3.img3[4],_T("正式图\\第三关\\BOSS3(数据侵蚀5).jpg"));
				loadimage(&boss3.img3[5],_T("正式图\\第三关\\BOSS3(数据侵蚀4).jpg"));
				loadimage(&boss3.img3[6],_T("正式图\\第三关\\BOSS3(数据侵蚀3).jpg"));
				loadimage(&boss3.img3[7],_T("正式图\\第三关\\BOSS3(数据侵蚀2).jpg"));
				loadimage(&boss3.img3[8],_T("正式图\\第三关\\BOSS3(数据侵蚀1).jpg"));

				loadimage(&boss3.img4[0],_T("正式图\\第三关\\BOSS3(隐身1).jpg"));
				loadimage(&boss3.img4[1],_T("正式图\\第三关\\BOSS3(隐身2).jpg"));
				loadimage(&boss3.img4[2],_T("正式图\\第三关\\BOSS3(隐身3).jpg"));
				loadimage(&boss3.img4[3],_T("正式图\\第三关\\BOSS3(隐身4).jpg"));
				loadimage(&boss3.img4[4],_T("正式图\\第三关\\BOSS3(隐身5).jpg"));

				loadimage(&boss3.img5[0],_T("正式图\\第三关\\BOSS3(现形1).jpg"));
				loadimage(&boss3.img5[1],_T("正式图\\第三关\\BOSS3(现形2).jpg"));
				loadimage(&boss3.img5[2],_T("正式图\\第三关\\BOSS3(现形3).jpg"));
				loadimage(&boss3.img5[3],_T("正式图\\第三关\\BOSS3(现形4).jpg"));
				loadimage(&boss3.img5[4],_T("正式图\\第三关\\BOSS3(现形5).jpg"));

				loadimage(&reaper[0].img,_T("正式图\\第三关\\收割1.jpg"));
				loadimage(&reaper[1].img,_T("正式图\\第三关\\收割2.jpg"));
				loadimage(&reaper[2].img,_T("正式图\\第三关\\收割3.jpg"));
				loadimage(&reaper[3].img,_T("正式图\\第三关\\收割4.jpg"));
				loadimage(&reaper[4].img,_T("正式图\\第三关\\收割5.jpg"));
				loadimage(&reaper[5].img,_T("正式图\\第三关\\收割6.jpg"));
				loadimage(&reaper[6].img,_T("正式图\\第三关\\收割7.jpg"));
				loadimage(&reaper[7].img,_T("正式图\\第三关\\收割8.jpg"));
				loadimage(&reaper[8].img,_T("正式图\\第三关\\收割9.jpg"));
				loadimage(&reaper[9].img,_T("正式图\\第三关\\收割10.jpg"));
				loadimage(&reaper[10].img,_T("正式图\\第三关\\收割11.jpg"));
				loadimage(&reaper[11].img,_T("正式图\\第三关\\收割12.jpg"));
				loadimage(&reaper[12].img,_T("正式图\\第三关\\收割13.jpg"));
				loadimage(&reaper[13].img,_T("正式图\\第三关\\收割14.jpg"));
				loadimage(&reaper[14].img,_T("正式图\\第三关\\收割15.jpg"));
				loadimage(&reaper[15].img,_T("正式图\\第三关\\收割16.jpg"));

				for(int i=0;i<12;i++)
					loadimage(&dataeroder[i].img,_T("正式图\\第三关\\数据侵蚀1.jpg"));
				for(int i=12;i<24;i++)
					loadimage(&dataeroder[i].img,_T("正式图\\第三关\\数据侵蚀2.jpg"));
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
						monster3_1[0].crd.x=WIDTH,														monster3_1[0].crd.y=HEIGHT/5;
						for(int i=1;i<8;i++)
						{
							if(i!=4)	monster3_1[i].crd.x=monster3_1[i-1].crd.x+WIDTH/10;
							else		monster3_1[i].crd.x=monster3_1[i-1].crd.x+WIDTH/5;
							monster3_1[i].crd.y=monster3_1[0].crd.y;
						}
						monster3_1[8].crd.x=-monster3_1[8].size.w,										monster3_1[8].crd.y=HEIGHT/2+120*sin((long double)(5*monster3_1[8].crd.x));
						for(int i=9;i<16;i++)
						{
							if(i!=12)   monster3_1[i].crd.x=monster3_1[i-1].crd.x-WIDTH/10;
							else        monster3_1[i].crd.x=monster3_1[i-1].crd.x-WIDTH/5;
							monster3_1[i].crd.y=HEIGHT/2-monster3_1[i].size.h+100*sin((long double)(5*monster3_1[i].crd.x));
						}
						monster3_1[16].crd.x=-monster3_1[16].size.w,									monster3_1[16].crd.y=4*HEIGHT/5;
						for(int i=17;i<24;i++)
						{
							if(i!=20)   monster3_1[i].crd.x=monster3_1[i-1].crd.x-WIDTH/10;
							else		monster3_1[i].crd.x=monster3_1[i-1].crd.x-WIDTH/5;
							monster3_1[i].crd.y=monster3_1[16].crd.y;
						}
					}break;
				case 1:
					{
						monster3_1[0].crd.x=WIDTH,														monster3_1[0].crd.y=HEIGHT/5-monster3_1[0].size.h+100*sin((long double)(5*monster3_1[0].crd.x));
						for(int i=1;i<8;i++)
						{
							if(i!=4)	monster3_1[i].crd.x=monster3_1[i-1].crd.x+WIDTH/10;
							else		monster3_1[i].crd.x=monster3_1[i-1].crd.x+WIDTH/5;
							monster3_1[i].crd.y=HEIGHT/5-monster3_1[i].size.h+100*sin((long double)(5*monster3_1[i].crd.x));
						}
						monster3_1[8].crd.x=WIDTH,														monster3_1[8].crd.y=HEIGHT/2;
						for(int i=9;i<16;i++)
						{
							if(i!=12)	monster3_1[i].crd.x=monster3_1[i-1].crd.x+WIDTH/10;
							else		monster3_1[i].crd.x=monster3_1[i-1].crd.x+WIDTH/5;
							monster3_1[i].crd.y=monster3_1[8].crd.y;
						}
						monster3_1[16].crd.x=-monster3_1[16].size.w,									monster3_1[16].crd.y=4*HEIGHT/5+100*sin((long double)(5*monster3_1[16].crd.x));
						for(int i=17;i<24;i++)
						{
							if(i!=20)	monster3_1[i].crd.x=monster3_1[i-1].crd.x-WIDTH/10;
							else		monster3_1[i].crd.x=monster3_1[i-1].crd.x-WIDTH/5;
							monster3_1[i].crd.y=4*HEIGHT/5+100*sin((long double)(5*monster3_1[i].crd.x));
						}
					}
			}break;
		case 2:																		
			{
				monster3_2[0].crd.x=WIDTH/2-2*monster3_2[0].size.w/3-R3*sin(Cir*2*PI/CIR3)+0.5,							monster3_2[0].crd.y=HEIGHT/2-2*monster3_2[0].size.h/3;
				monster3_2[1].crd.x=WIDTH/5-monster3_2[1].size.w/2+R1*sin(Cir*2*PI/CIR2)+0.5,							monster3_2[1].crd.y=HEIGHT/5-monster3_2[1].size.h/2;
				monster3_2[2].crd.x=4*WIDTH/5-monster3_2[2].size.w/2,													monster3_2[2].crd.y=HEIGHT/5-monster3_2[2].size.h/2-R1*sin(Cir*2*PI/CIR2)+0.5;
				monster3_2[3].crd.x=WIDTH/5-monster3_2[3].size.w/2,														monster3_2[3].crd.y=4*HEIGHT/5-monster3_2[4].size.h/2+R1*sin(Cir*2*PI/CIR2)+0.5;
				monster3_2[4].crd.x=4*WIDTH/5-monster3_2[4].size.w/2-R1*sin(Cir*2*PI/CIR2)+0.5,							monster3_2[4].crd.y=4*HEIGHT/5-monster3_2[4].size.h/2;
			}break;
		case 3:
			{
				switch(Pro)
				{
					case 0:
						{
							monster3_3[4].crd.x=monster3_3[32].crd.x=WIDTH/70;
							monster3_3[1].crd.x=monster3_3[10].crd.x=monster3_3[33].crd.x=WIDTH/10+WIDTH/70;
							monster3_3[2].crd.x=monster3_3[11].crd.x=monster3_3[18].crd.x=monster3_3[24].crd.x=monster3_3[26].crd.x=monster3_3[34].crd.x=WIDTH/5+WIDTH/70;
							monster3_3[3].crd.x=monster3_3[8].crd.x=monster3_3[12].crd.x=monster3_3[19].crd.x=3*WIDTH/10+WIDTH/70;
							monster3_3[20].crd.x=monster3_3[27].crd.x=monster3_3[35].crd.x=monster3_3[36].crd.x=2*WIDTH/5+WIDTH/70;
							monster3_3[0].crd.x=monster3_3[4].crd.x=monster3_3[13].crd.x=monster3_3[37].crd.x=WIDTH/2+WIDTH/70;
							monster3_3[5].crd.x=monster3_3[14].crd.x=monster3_3[21].crd.x=monster3_3[25].crd.x=monster3_3[28].crd.x=monster3_3[38].crd.x=3*WIDTH/5+WIDTH/70;
							monster3_3[6].crd.x=monster3_3[15].crd.x=monster3_3[29].crd.x=7*WIDTH/10+WIDTH/70;
							monster3_3[7].crd.x=monster3_3[16].crd.x=monster3_3[17].crd.x=monster3_3[22].crd.x=monster3_3[30].crd.x=4*WIDTH/5+WIDTH/70;
							monster3_3[23].crd.x=monster3_3[31].crd.x=9*WIDTH/10+WIDTH/70;

							monster3_3[0].crd.y=HEIGHT/70;
							for(int i=1;i<8;i++)	monster3_3[i].crd.y=HEIGHT/10+HEIGHT/70;
							monster3_3[8].crd.y=HEIGHT/5+HEIGHT/70;
							for(int i=9;i<17;i++)	monster3_3[i].crd.y=3*HEIGHT/10+HEIGHT/70;
							monster3_3[17].crd.y=2*HEIGHT/5+HEIGHT/70;
							for(int i=18;i<24;i++)  monster3_3[i].crd.y=HEIGHT/2+HEIGHT/70;
							for(int i=24;i<26;i++)	monster3_3[i].crd.y=3*HEIGHT/5+HEIGHT/70;
							for(int i=26;i<32;i++)	monster3_3[i].crd.y=7*HEIGHT/10+HEIGHT/70;
							for(int i=32;i<36;i++)	monster3_3[i].crd.y=4*HEIGHT/5+HEIGHT/70;
							for(int i=36;i<39;i++)	monster3_3[i].crd.y=9*HEIGHT/10+HEIGHT/70;
						}break;
					case 1:
						{
							monster3_3[0].crd.x=monster3_3[3].crd.x=monster3_3[5].crd.x=monster3_3[29].crd.x=WIDTH/70;
							monster3_3[6].crd.x=monster3_3[14].crd.x=monster3_3[20].crd.x=monster3_3[23].crd.x=monster3_3[30].crd.x=WIDTH/10+WIDTH/70;
							monster3_3[7].crd.x=monster3_3[15].crd.x=WIDTH/5+WIDTH/70;
							monster3_3[16].crd.x=monster3_3[24].crd.x=monster3_3[31].crd.x=monster3_3[32].crd.x=monster3_3[37].crd.x=3*WIDTH/10+WIDTH/70;
							monster3_3[4].crd.x=monster3_3[8].crd.x=monster3_3[12].crd.x=monster3_3[17].crd.x=monster3_3[25].crd.x=2*WIDTH/5+WIDTH/70;
							monster3_3[9].crd.x=monster3_3[21].crd.x=monster3_3[26].crd.x=WIDTH/2+WIDTH/70;
							monster3_3[10].crd.x=monster3_3[33].crd.x=3*WIDTH/5+WIDTH/70;
							monster3_3[1].crd.x=monster3_3[11].crd.x=monster3_3[18].crd.x=monster3_3[22].crd.x=monster3_3[34].crd.x=7*WIDTH/10+WIDTH/70;
							monster3_3[2].crd.x=monster3_3[27].crd.x=monster3_3[35].crd.x=4*WIDTH/5+WIDTH/70;
							monster3_3[13].crd.x=monster3_3[19].crd.x=monster3_3[28].crd.x=monster3_3[36].crd.x=monster3_3[38].crd.x=9*WIDTH/10+WIDTH/70;

							for(int i=0;i<3;i++)	monster3_3[i].crd.y=HEIGHT/70;
							for(int i=3;i<5;i++)    monster3_3[i].crd.y=HEIGHT/10+HEIGHT/70;
							for(int i=5;i<12;i++)	monster3_3[i].crd.y=HEIGHT/5+HEIGHT/70;
							for(int i=12;i<14;i++)  monster3_3[i].crd.y=3*HEIGHT/10+HEIGHT/70;
							for(int i=14;i<20;i++)	monster3_3[i].crd.y=2*HEIGHT/5+HEIGHT/70;
							for(int i=20;i<23;i++)	monster3_3[i].crd.y=HEIGHT/2+HEIGHT/70;
							for(int i=23;i<29;i++)	monster3_3[i].crd.y=3*HEIGHT/5+HEIGHT/70;
							for(int i=29;i<32;i++)	monster3_3[i].crd.y=7*HEIGHT/10+HEIGHT/70;
							for(int i=32;i<37;i++)	monster3_3[i].crd.y=4*HEIGHT/5+HEIGHT/70;
							for(int i=37;i<39;i++)	monster3_3[i].crd.y=9*HEIGHT/10+HEIGHT/70;
						}
				}
			}break;
		case 4:
			{
				monster3_4[0].crd.x=(WIDTH-monster3_4[0].size.w)/2+r5*cos(2*PI*(Cir+c/4)/c)+0.5,											monster3_4[0].crd.y=(HEIGHT-monster3_4[0].size.h)/2+r5*sin(2*PI*(Cir+c/4)/c)+0.5;
				monster3_4[1].crd.x=(WIDTH-monster3_4[1].size.w)/2+r3*cos(2*PI*(Cir+3*c/8)/c)+0.5,											monster3_4[1].crd.y=(HEIGHT-monster3_4[1].size.h)/2+r3*sin(2*PI*(Cir+3*c/8)/c)+0.5;
				monster3_4[2].crd.x=(WIDTH-monster3_4[2].size.w)/2+r2*cos(2*PI*(Cir+c/4)/c)+0.5,											monster3_4[2].crd.y=(HEIGHT-monster3_4[2].size.h)/2+r2*sin(2*PI*(Cir+c/4)/c)+0.5;
				monster3_4[3].crd.x=(WIDTH-monster3_4[3].size.w)/2+r3*cos(2*PI*(Cir+c/8)/c)+0.5,											monster3_4[3].crd.y=(HEIGHT-monster3_4[3].size.h)/2+r3*sin(2*PI*(Cir+c/8)/c)+0.5;
				monster3_4[4].crd.x=(WIDTH-monster3_4[4].size.w)/2+r4*cos(2*PI*(Cir-c/4+asin(3/sqrt((long double)10))*c/(2*PI))/c)+0.5,		monster3_4[4].crd.y=(HEIGHT-monster3_4[4].size.h)/2+r4*sin(2*PI*(Cir-c/4+asin(3/sqrt((long double)10))*c/(2*PI))/c)+0.5;
				monster3_4[5].crd.x=(WIDTH-monster3_4[5].size.w)/2+r1*cos(2*PI*(Cir+c/8)/c)+0.5,											monster3_4[5].crd.y=(HEIGHT-monster3_4[5].size.h)/2+r1*sin(2*PI*(Cir+c/8)/c)+0.5;
				monster3_4[6].crd.x=(WIDTH-monster3_4[6].size.w)/2+r4*cos(2*PI*(Cir+c/4+asin(1/sqrt((long double)10))*c/(2*PI))/c)+0.5,		monster3_4[6].crd.y=(HEIGHT-monster3_4[6].size.h)/2+r4*sin(2*PI*(Cir+c/4+asin(1/sqrt((long double)10))*c/(2*PI))/c)+0.5;
				monster3_4[7].crd.x=(WIDTH-monster3_4[7].size.w)/2+r5*cos(2*PI*(Cir+c/2)/c)+0.5,											monster3_4[7].crd.y=(HEIGHT-monster3_4[7].size.h)/2+r5*sin(2*PI*(Cir+c/2)/c)+0.5;
				monster3_4[8].crd.x=(WIDTH-monster3_4[8].size.w)/2,																			monster3_4[8].crd.y=(HEIGHT-monster3_4[8].size.h)/2;
				monster3_4[9].crd.x=(WIDTH-monster3_4[9].size.w)/2+r5*cos(2*PI*Cir/c)+0.5,													monster3_4[9].crd.y=(HEIGHT-monster3_4[9].size.h)/2+r5*sin(2*PI*Cir/c)+0.5;
				monster3_4[10].crd.x=(WIDTH-monster3_4[10].size.w)/2+r4*cos(2*PI*(Cir+c/2+asin(1/sqrt((long double)10))*c/(2*PI))/c)+0.5,	monster3_4[10].crd.y=(HEIGHT-monster3_4[10].size.h)/2+r4*sin(2*PI*(Cir+c/2+asin(1/sqrt((long double)10))*c/(2*PI))/c)+0.5;
				monster3_4[11].crd.x=(WIDTH-monster3_4[11].size.w)/2+r1*cos(2*PI*(Cir+5*c/8)/c)+0.5,										monster3_4[11].crd.y=(HEIGHT-monster3_4[11].size.h)/2+r1*sin(2*PI*(Cir+5*c/8)/c)+0.5;
				monster3_4[12].crd.x=(WIDTH-monster3_4[12].size.w)/2+r4*cos(2*PI*(Cir+asin(1/sqrt((long double)10))*c/(2*PI))/c)+0.5,		monster3_4[12].crd.y=(HEIGHT-monster3_4[12].size.h)/2+r4*sin(2*PI*(Cir+asin(1/sqrt((long double)10))*c/(2*PI))/c)+0.5;
				monster3_4[13].crd.x=(WIDTH-monster3_4[13].size.w)/2+r3*cos(2*PI*(Cir+5*c/8)/c)+0.5,										monster3_4[13].crd.y=(HEIGHT-monster3_4[13].size.h)/2+r3*sin(2*PI*(Cir+5*c/8)/c)+0.5;
				monster3_4[14].crd.x=(WIDTH-monster3_4[14].size.w)/2+r2*cos(2*PI*(Cir+3*c/4)/c)+0.5,										monster3_4[14].crd.y=(HEIGHT-monster3_4[14].size.h)/2+r2*sin(2*PI*(Cir+3*c/4)/c)+0.5;
				monster3_4[15].crd.x=(WIDTH-monster3_4[15].size.w)/2+r3*cos(2*PI*(Cir-c/8)/c)+0.5,											monster3_4[15].crd.y=(HEIGHT-monster3_4[15].size.h)/2+r3*sin(2*PI*(Cir-c/8)/c)+0.5;
				monster3_4[16].crd.x=(WIDTH-monster3_4[16].size.w)/2+r5*cos(2*PI*(Cir+3*c/4)/c)+0.5,										monster3_4[16].crd.y=(HEIGHT-monster3_4[16].size.h)/2+r5*sin(2*PI*(Cir+3*c/4)/c)+0.5;
			}break;
		case 5:
			{
				switch(boss3.state)
				{
					case 0:
						{
							boss3.crd.x=boss3.crd.y=0;break;
							for(int i=0;i<16;i++)
								reaper[i].crd.x=reaper[i].crd.y=0;
							for(int i=0;i<24;i++)
								dataeroder[i].crd.x=dataeroder[i].crd.y=0;
						}break;
					case 2:
						{
							reaper[0].crd.x=167*WIDTH/350,		reaper[0].crd.y=6*HEIGHT/35;
							reaper[1].crd.x=407*WIDTH/700,		reaper[1].crd.y=137*HEIGHT/700;
							reaper[2].crd.x=47*WIDTH/70,		reaper[2].crd.y=191*HEIGHT/700;
							reaper[3].crd.x=508*WIDTH/700,		reaper[3].crd.y=264*HEIGHT/700;
							reaper[4].crd.x=512*WIDTH/700,		reaper[4].crd.y=333*HEIGHT/700;
							reaper[5].crd.x=508*WIDTH/700,		reaper[5].crd.y=414*HEIGHT/700;
							reaper[6].crd.x=470*WIDTH/700,		reaper[6].crd.y=468*HEIGHT/700;
							reaper[7].crd.x=411*WIDTH/700,		reaper[7].crd.y=510*HEIGHT/700;
							reaper[8].crd.x=341*WIDTH/700,		reaper[8].crd.y=522*HEIGHT/700;
							reaper[9].crd.x=257*WIDTH/700,		reaper[9].crd.y=512*HEIGHT/700;
							reaper[10].crd.x=194*WIDTH/700,		reaper[10].crd.y=464*HEIGHT/700;
							reaper[11].crd.x=150*WIDTH/700,		reaper[11].crd.y=408*HEIGHT/700;
							reaper[12].crd.x=128*WIDTH/700,		reaper[12].crd.y=334*HEIGHT/700;
							reaper[13].crd.x=140*WIDTH/700,		reaper[13].crd.y=225*HEIGHT/700;
							reaper[14].crd.x=187*WIDTH/700,		reaper[14].crd.y=190*HEIGHT/700;
							reaper[15].crd.x=251*WIDTH/700,		reaper[15].crd.y=136*HEIGHT/700;
						}break;
					case 3:
						{
							int a=rand()%2;
							if(a==0)
							{
								for(int i=0;i<12;i++)
								{
									dataeroder[i].crd.y=3*HEIGHT/280+2*i*HEIGHT/24;
									dataeroder[i].crd.x=-dataeroder[i].size.w;
								}
								for(int i=12;i<24;i++)
								{
									dataeroder[i].crd.y=3*HEIGHT/280+(2*i-23)*HEIGHT/24;
									dataeroder[i].crd.x=WIDTH;
								}
							}
							else
							{
								for(int i=0;i<12;i++)
								{
									dataeroder[i].crd.y=3*HEIGHT/280+(2*i+1)*HEIGHT/24;
									dataeroder[i].crd.x=-dataeroder[i].size.w;
								}
								for(int i=12;i<24;i++)
								{
									dataeroder[i].crd.y=3*HEIGHT/280+(2*i-24)*HEIGHT/24;
									dataeroder[i].crd.x=WIDTH;
								}
							}
						}break;
					case 5:
						{
								boss3.crd.x=dataworm.crd[0].x-boss3.size.w/2;
								boss3.crd.y=dataworm.crd[0].y-boss3.size.h/2;
								tat=fabs((long double)(boss3.crd.y-19*HEIGHT/70))/fabs((long double)(boss3.crd.x-47*WIDTH/140));
						}break;
					default:;
				}
			}break;
		default:;
		}
}


static void InitMonsterSpeed()
{
	if(Sec==1)
		for(int i=0;i<24;i++)
			monster3_1[i].speed=SPEED2;
	if(Sec==2)
		for(int i=0;i<5;i++)
			monster3_2[i].speed=SPEED3;
	if(Sec==5)
			{
				for(int i=0;i<16;i++)
					reaper[i].speed=SPEED5;
				for(int i=0;i<24;i++)
					dataeroder[i].speed=SPEED3;
			}
}

static void InitMonsterSize()
{
	switch(Sec)
	{
		case 1:
			{
				for(int i=0;i<24;i++)
				{
					monster3_1[i].size.w=50;
					monster3_1[i].size.h=40;
				}
			}break;
		case 2:
			{
				monster3_2[0].size.w=monster3_2[0].size.h=150;
				for(int i=0;i<5;i++)
					monster3_2[i].size.w=monster3_2[i].size.h=100;
			}break;
		case 3:
			{
				for(int i=0;i<39;i++)
					monster3_3[i].size.w=monster3_3[i].size.h=48;
			}break;
		case 4:
			{
				for(int i=0;i<17;i++)
					monster3_4[i].size.w=monster3_4[i].size.h=80;
			}break;
		case 5:
			{
				boss3.size.w=230,		boss3.size.h=331;
				reaper[0].size.w=32,	reaper[0].size.h=56;
				reaper[1].size.w=48,	reaper[1].size.h=50;
				reaper[2].size.w=53,	reaper[2].size.h=41;
				reaper[3].size.w=63,	reaper[3].size.h=35;
				reaper[4].size.w=62,	reaper[4].size.h=37;
				reaper[5].size.w=50,	reaper[5].size.h=44;
				reaper[6].size.w=42,	reaper[6].size.h=49;
				reaper[7].size.w=40,	reaper[7].size.h=55;
				reaper[8].size.w=37,	reaper[8].size.h=59;
				reaper[9].size.w=38,	reaper[9].size.h=57;
				reaper[10].size.w=42,	reaper[10].size.h=53;
				reaper[11].size.w=45,	reaper[11].size.h=48;
				reaper[12].size.w=58,	reaper[12].size.h=35;
				reaper[13].size.w=58,	reaper[13].size.h=33;
				reaper[14].size.w=53,	reaper[14].size.h=39;
				reaper[15].size.w=40,	reaper[15].size.h=52;
				for(int i=0;i<12;i++)
					dataeroder[i].size.w=187,	dataeroder[i].size.h=14;
				for(int i=12;i<24;i++)
					dataeroder[i].size.w=185,	dataeroder[i].size.h=12;
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
				for(int i=0;i<16;i++)
					monster3_1[i].dmg=DMG1;
			}break;
		case 2:
			{
				monster3_2[0].dmg=DMG3;
				for(int i=1;i<5;i++)
					monster3_2[i].dmg=DMG2;
			}break;
		case 3:
			{
				for(int i=0;i<39;i++)
					monster3_3[i].dmg=DMG2;
			}break;
		case 4:
			{
				for(int i=0;i<17;i++)
				{
					if((i!=0)&&(i!=8)&&(i!=16))		monster3_4[i].dmg=DMG2;
					else							monster3_4[i].dmg=DMG3;
				}
			}break;
		case 5:
			{
				for(int i=0;i<16;i++)
					reaper[i].dmg=DMG2;
				for(int i=0;i<24;i++)
					dataeroder[i].dmg=DMG2;
				if(boss3.state!=5)	boss3.dmg=DMG5;
				else				boss3.dmg=DMG3;
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
				for(int i=0;i<24;i++)
					monster3_1[i].time.oldtime=0;
			}break;
		case 2:
			{
				for(int i=0;i<5;i++)
					monster3_2[i].time.oldtime=0;
			}break;
		case 3:
			{
				for(int i=0;i<39;i++)
					monster3_3[i].time.oldtime=0;
			}break;
		case 4:
			{
				for(int i=0;i<17;i++)
					monster3_4[i].time.oldtime=0;
			}break;
		case 5:
			{
				for(int i=0;i<16;i++)
					reaper[i].time.oldtime=0;
				for(int i=0;i<24;i++)
					dataeroder[i].time.oldtime=0;
				boss3.dmgtime.oldtime=0;
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
						for(int i=0;i<8;i++)
							monster3_1[i].crd.x-=monster3_1[i].speed;
						for(int i=8;i<16;i++)
						{
							monster3_1[i].crd.x+=monster3_1[i].speed;
							monster3_1[i].crd.y=HEIGHT/2+120*sin((long double)(5*monster3_1[i].crd.x));
						}
						for(int i=16;i<24;i++)
							monster3_1[i].crd.x+=monster3_1[i].speed;
					}break;
				case 1:
					{
						for(int i=0;i<8;i++)
						{
							monster3_1[i].crd.x-=monster3_1[i].speed;
							monster3_1[i].crd.y=HEIGHT/5-monster3_1[i].size.h/2+120*sin((long double)(5*monster3_1[i].crd.x));
						}
						for(int i=8;i<16;i++)
							monster3_1[i].crd.x-=monster3_1[i].speed;
						for(int i=16;i<24;i++)
						{
							monster3_1[i].crd.x+=monster3_1[i].speed;
							monster3_1[i].crd.y=4*HEIGHT/5-monster3_1[i].size.h/2+120*sin((long double)(5*monster3_1[i].crd.x));
						}
					}
			}break;
		case 2:
			{
				switch(Pro)
				{
					case 0:
						{
							monster3_2[0].crd.x=WIDTH/2-2*monster3_2[0].size.w/3-R3*sin(Cir*2*PI/CIR3)+0.5,							monster3_2[0].crd.y=HEIGHT/2-2*monster3_2[0].size.h/3;
							monster3_2[1].crd.x=WIDTH/5-monster3_2[1].size.w/2+R1*sin(Cir*2*PI/CIR1)+0.5,							monster3_2[1].crd.y=HEIGHT/5-monster3_2[1].size.h/2;
							monster3_2[2].crd.x=4*WIDTH/5-monster3_2[2].size.w/2,													monster3_2[2].crd.y=HEIGHT/5-monster3_2[2].size.h/2-R1*sin(Cir*2*PI/CIR1)+0.5;
							monster3_2[3].crd.x=WIDTH/5-monster3_2[3].size.w/2,														monster3_2[3].crd.y=4*HEIGHT/5-monster3_2[4].size.h/2+R1*sin(Cir*2*PI/CIR1)+0.5;
							monster3_2[4].crd.x=4*WIDTH/5-monster3_2[4].size.w/2-R1*sin(Cir*2*PI/CIR1)+0.5,							monster3_2[4].crd.y=4*HEIGHT/5-monster3_2[4].size.h/2;
						}break;
					case 1:
						{
							monster3_2[1].crd.y+=monster3_2[1].speed;
							monster3_2[2].crd.x-=monster3_2[2].speed;
							monster3_2[3].crd.x+=monster3_2[3].speed;
							monster3_2[4].crd.y-=monster3_2[4].speed;
						}break;
					case 2:
						{
							monster3_2[0].crd.x=WIDTH/2-2*monster3_2[0].size.w/3,													monster3_2[0].crd.y=HEIGHT/2-2*monster3_2[0].size.h/3+R3*sin(Cir*2*PI/CIR3)+0.5;
							monster3_2[1].crd.x=WIDTH/5-monster3_2[1].size.w/2+R1*sin(Cir*2*PI/CIR1)+0.5,							monster3_2[1].crd.y=HEIGHT/5-monster3_2[1].size.h/2;
							monster3_2[2].crd.x=4*WIDTH/5-monster3_2[2].size.w/2,													monster3_2[2].crd.y=HEIGHT/5-monster3_2[2].size.h/2-R1*sin(Cir*2*PI/CIR1)+0.5;
							monster3_2[3].crd.x=WIDTH/5-monster3_2[3].size.w/2,														monster3_2[3].crd.y=4*HEIGHT/5-monster3_2[4].size.h/2+R1*sin(Cir*2*PI/CIR1)+0.5;
							monster3_2[4].crd.x=4*WIDTH/5-monster3_2[4].size.w/2-R1*sin(Cir*2*PI/CIR1)+0.5,							monster3_2[4].crd.y=4*HEIGHT/5-monster3_2[4].size.h/2;
						}break;
					case 3:
						{
							monster3_2[1].crd.x+=monster3_2[1].speed;
							monster3_2[2].crd.y+=monster3_2[2].speed;
							monster3_2[3].crd.y-=monster3_2[3].speed;
							monster3_2[4].crd.x-=monster3_2[4].speed;
						}
				}
			}break;
		case 4:
			{
				monster3_4[0].crd.x=(WIDTH-monster3_4[0].size.w)/2+r5*cos(2*PI*(Cir+c/4)/c)+0.5,											monster3_4[0].crd.y=(HEIGHT-monster3_4[0].size.h)/2+r5*sin(2*PI*(Cir+c/4)/c)+0.5;
				monster3_4[1].crd.x=(WIDTH-monster3_4[1].size.w)/2+r3*cos(2*PI*(Cir+3*c/8)/c)+0.5,											monster3_4[1].crd.y=(HEIGHT-monster3_4[1].size.h)/2+r3*sin(2*PI*(Cir+3*c/8)/c)+0.5;
				monster3_4[2].crd.x=(WIDTH-monster3_4[2].size.w)/2+r2*cos(2*PI*(Cir+c/4)/c)+0.5,											monster3_4[2].crd.y=(HEIGHT-monster3_4[2].size.h)/2+r2*sin(2*PI*(Cir+c/4)/c)+0.5;
				monster3_4[3].crd.x=(WIDTH-monster3_4[3].size.w)/2+r3*cos(2*PI*(Cir+c/8)/c)+0.5,											monster3_4[3].crd.y=(HEIGHT-monster3_4[3].size.h)/2+r3*sin(2*PI*(Cir+c/8)/c)+0.5;
				monster3_4[4].crd.x=(WIDTH-monster3_4[4].size.w)/2+r4*cos(2*PI*(Cir-c/4+asin(3/sqrt((long double)10))*c/(2*PI))/c)+0.5,		monster3_4[4].crd.y=(HEIGHT-monster3_4[4].size.h)/2+r4*sin(2*PI*(Cir-c/4+asin(3/sqrt((long double)10))*c/(2*PI))/c)+0.5;
				monster3_4[5].crd.x=(WIDTH-monster3_4[5].size.w)/2+r1*cos(2*PI*(Cir+c/8)/c)+0.5,											monster3_4[5].crd.y=(HEIGHT-monster3_4[5].size.h)/2+r1*sin(2*PI*(Cir+c/8)/c)+0.5;
				monster3_4[6].crd.x=(WIDTH-monster3_4[6].size.w)/2+r4*cos(2*PI*(Cir+c/4+asin(1/sqrt((long double)10))*c/(2*PI))/c)+0.5,		monster3_4[6].crd.y=(HEIGHT-monster3_4[6].size.h)/2+r4*sin(2*PI*(Cir+c/4+asin(1/sqrt((long double)10))*c/(2*PI))/c)+0.5;
				monster3_4[7].crd.x=(WIDTH-monster3_4[7].size.w)/2+r5*cos(2*PI*(Cir+c/2)/c)+0.5,											monster3_4[7].crd.y=(HEIGHT-monster3_4[7].size.h)/2+r5*sin(2*PI*(Cir+c/2)/c)+0.5;
				monster3_4[8].crd.x=(WIDTH-monster3_4[8].size.w)/2,																			monster3_4[8].crd.y=(HEIGHT-monster3_4[8].size.h)/2;
				monster3_4[9].crd.x=(WIDTH-monster3_4[9].size.w)/2+r5*cos(2*PI*Cir/c)+0.5,													monster3_4[9].crd.y=(HEIGHT-monster3_4[9].size.h)/2+r5*sin(2*PI*Cir/c)+0.5;
				monster3_4[10].crd.x=(WIDTH-monster3_4[10].size.w)/2+r4*cos(2*PI*(Cir+c/2+asin(1/sqrt((long double)10))*c/(2*PI))/c)+0.5,	monster3_4[10].crd.y=(HEIGHT-monster3_4[10].size.h)/2+r4*sin(2*PI*(Cir+c/2+asin(1/sqrt((long double)10))*c/(2*PI))/c)+0.5;
				monster3_4[11].crd.x=(WIDTH-monster3_4[11].size.w)/2+r1*cos(2*PI*(Cir+5*c/8)/c)+0.5,										monster3_4[11].crd.y=(HEIGHT-monster3_4[11].size.h)/2+r1*sin(2*PI*(Cir+5*c/8)/c)+0.5;
				monster3_4[12].crd.x=(WIDTH-monster3_4[12].size.w)/2+r4*cos(2*PI*(Cir+asin(1/sqrt((long double)10))*c/(2*PI))/c)+0.5,		monster3_4[12].crd.y=(HEIGHT-monster3_4[12].size.h)/2+r4*sin(2*PI*(Cir+asin(1/sqrt((long double)10))*c/(2*PI))/c)+0.5;
				monster3_4[13].crd.x=(WIDTH-monster3_4[13].size.w)/2+r3*cos(2*PI*(Cir+5*c/8)/c)+0.5,										monster3_4[13].crd.y=(HEIGHT-monster3_4[13].size.h)/2+r3*sin(2*PI*(Cir+5*c/8)/c)+0.5;
				monster3_4[14].crd.x=(WIDTH-monster3_4[14].size.w)/2+r2*cos(2*PI*(Cir+3*c/4)/c)+0.5,										monster3_4[14].crd.y=(HEIGHT-monster3_4[14].size.h)/2+r2*sin(2*PI*(Cir+3*c/4)/c)+0.5;
				monster3_4[15].crd.x=(WIDTH-monster3_4[15].size.w)/2+r3*cos(2*PI*(Cir-c/8)/c)+0.5,											monster3_4[15].crd.y=(HEIGHT-monster3_4[15].size.h)/2+r3*sin(2*PI*(Cir-c/8)/c)+0.5;
				monster3_4[16].crd.x=(WIDTH-monster3_4[16].size.w)/2+r5*cos(2*PI*(Cir+3*c/4)/c)+0.5,										monster3_4[16].crd.y=(HEIGHT-monster3_4[16].size.h)/2+r5*sin(2*PI*(Cir+3*c/4)/c)+0.5;
			}break;
		case 5:
			{
				switch(boss3.state)
				{
					case 2:
						{
							if(((reaper[2].crd.x<=WIDTH)||(reaper[2].crd.y>=-reaper[2].size.h))&&(Pic==4))
							{
								reaper[0].crd.y-=reaper[0].speed;
								reaper[1].crd.x+=reaper[1].speed*sin(PI/8)+0.5,		reaper[1].crd.y-=reaper[1].speed*cos(PI/8)+0.5;
								reaper[2].crd.x+=reaper[2].speed*sin(PI/4)+0.5,		reaper[2].crd.y-=reaper[2].speed*cos(PI/4)+0.5;
								reaper[3].crd.x+=reaper[3].speed*cos(PI/8)+0.5,		reaper[3].crd.y-=reaper[3].speed*sin(PI/8)+0.5;
								reaper[4].crd.x+=reaper[4].speed;
								reaper[5].crd.x+=reaper[5].speed*cos(PI/8)+0.5,		reaper[5].crd.y+=reaper[5].speed*sin(PI/8)+0.5;
								reaper[6].crd.x+=reaper[6].speed*cos(PI/4)+0.5,		reaper[6].crd.y+=reaper[6].speed*sin(PI/4)+0.5;
								reaper[7].crd.x+=reaper[7].speed*sin(PI/8)+0.5,		reaper[7].crd.y+=reaper[7].speed*cos(PI/8)+0.5;
								reaper[8].crd.y+=reaper[8].speed;
								reaper[9].crd.x-=reaper[9].speed*sin(PI/8)+0.5,		reaper[9].crd.y+=reaper[9].speed*cos(PI/8)+0.5;
								reaper[10].crd.x-=reaper[10].speed*cos(PI/4)+0.5,	reaper[10].crd.y+=reaper[10].speed*sin(PI/4)+0.5;
								reaper[11].crd.x-=reaper[11].speed*cos(PI/8)+0.5,	reaper[11].crd.y+=reaper[11].speed*sin(PI/8)+0.5;
								reaper[12].crd.x-=reaper[12].speed;
								reaper[13].crd.x-=reaper[13].speed*cos(PI/8)+0.5,	reaper[13].crd.y-=reaper[13].speed*sin(PI/8)+0.5;
								reaper[14].crd.x-=reaper[14].speed*cos(PI/4)+0.5,	reaper[14].crd.y-=reaper[14].speed*sin(PI/4)+0.5;
								reaper[15].crd.x-=reaper[15].speed*sin(PI/8)+0.5,	reaper[15].crd.y-=reaper[15].speed*cos(PI/8)+0.5;
							}
						}break;
					case 3:
						{
							if((dataeroder[0].crd.x<=WIDTH)&&(Pic==4))
							{
								for(int i=0;i<12;i++)
									dataeroder[i].crd.x+=dataeroder[i].speed;
								for(int i=12;i<24;i++)
									dataeroder[i].crd.x-=dataeroder[i].speed;
							}
						}break;
					case 5:
						{
							if(((abs(boss3.crd.x-47*WIDTH/140)>=3*SPEED3)||(abs(boss3.crd.y-19*HEIGHT/70)>=3*SPEED3))&&(Pic==4))
							{
								if((boss3.crd.x-47*WIDTH/140>=0)&&(boss3.crd.y-19*HEIGHT/70<=0))
								{
									boss3.crd.x-=SPEED3*cos(atan(tat))+0.5;
									boss3.crd.y+=SPEED3*sin(atan(tat))+0.5;
								}
								else if((boss3.crd.x-47*WIDTH/140>=0)&&(boss3.crd.y-19*HEIGHT/70>=0))
								{
									boss3.crd.x-=SPEED3*cos(atan(tat))+0.5;
									boss3.crd.y-=SPEED3*sin(atan(tat))+0.5;
								}
								else if((boss3.crd.x-47*WIDTH/140<=0)&&(boss3.crd.y-19*HEIGHT/70>=0))
								{
									boss3.crd.x+=SPEED3*cos(atan(tat))+0.5;
									boss3.crd.y-=SPEED3*sin(atan(tat))+0.5;
								}
								else
								{
									boss3.crd.x+=SPEED3*cos(atan(tat))+0.5;
									boss3.crd.y+=SPEED3*sin(atan(tat))+0.5;
								}
							}
						}break;
					default:;
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
				for(int i=0;i<24;i++)
					putimage(monster3_1[i].crd.x,monster3_1[i].crd.y,&monster3_1[i].img);
			}break;
		case 2:
			{
				for(int i=0;i<5;i++)
					putimage(monster3_2[i].crd.x,monster3_2[i].crd.y,&monster3_2[i].img[Pic]);
			}break;
		case 3:
			{
				for(int i=0;i<39;i++)
					putimage(monster3_3[i].crd.x,monster3_3[i].crd.y,&monster3_3[i].img[Pic]);
			}break;
		case 4:
			{
				for(int i=0;i<17;i++)
					putimage(monster3_4[i].crd.x,monster3_4[i].crd.y,&monster3_4[i].img[Pic]);
			}break;
		case 5:
			{
				switch(boss3.state)
				{
					case 0: putimage(0,0,&boss3.img0[Pic]);break;
					case 1:	putimage(0,0,&boss3.img1);break;
					case 2:
						{
							putimage(0,0,&boss3.img2[Pic]);
							if(Pic==4)
								for(int i=0;i<16;i++)	putimage(reaper[i].crd.x,reaper[i].crd.y,&reaper[i].img);
						}break;
					case 3:
						{
							putimage(0,0,&boss3.img3[Pic]);
							if(Pic==4)
								for(int i=0;i<24;i++)	putimage(dataeroder[i].crd.x,dataeroder[i].crd.y,&dataeroder[i].img);
						}break;
					case 4:
						{
							putimage(0,0,&boss3.img4[Pic]);
						}break;
					case 5:
						{
							putimage(boss3.crd.x,boss3.crd.y,&boss3.img5[Pic]);
						}break;
					default:;
				}
			}
	}
}

static bool JudgeChange_Pro_or_Pic()
{
	switch(Sec)
	{
		case 1:
			{
				if(Cir%((9*WIDTH/5+monster3_1[0].size.w)/monster3_1[0].speed)==0)
				{
					Pro++;
					if(Pro>1) Pro=0;
					return 1;
				}
				return 0;
			}break;
		case 2:
			{
				int cpro=lcd(CIR1,CIR3,hcf(CIR1,CIR3));
				if(Cir%1==0)	Pic++;
				if(Pic>2)		Pic=0;
				switch(Pro)
				{
					case 0:
					case 2:
						{
							if(Cir%(cpro)==0)
							{
								Pro++;
								Cir=0;
								return 1;
							}
							return 0;
						}break;
					case 1:
					case 3:
						{
							if(Cir%(3*HEIGHT/(5*monster3_2[0].speed))==0)
							{
								Pro++;
								if(Pro>3)	Pro=0;
								Cir=0;
								return 1;
							}
							return 0;
						}
				}
			}break;
		case 3:
			{
				if(Cir%8==0)	Pic++;
				if(Pic>6)		Pic=0;
				if(Cir%(7*8*5)==0)						//七张图|八次循环换一张图|闪烁五次
				{
					Pro++;
					dataworm.hp-=50;
					DmgAni();
					if(Pro>1)	Pro=0;
					return 1;
				}
				return 0;
			}break;
		case 4:
			{
				if(Cir%10==0)	Pic++;
				if(Pic>1)		Pic=0;
				if((Cir%(c)==0)&&c>100)	c-=50,Cir=0;
				return 0;
			}break;
		case 5:
			{
				switch(boss3.state)
				{
					case 0:
						{
							Cir++;
							if(Cir%15==0)	Pic++;
							if(Pic>4)
							{
								Pic=Cir=0;
								boss3.state=1;
								boss3.time.oldtime=GetTickCount();
							}
						}break;
					case 1:
						{
							if(boss3.time.newtime-boss3.time.oldtime>=2000)
							{
								char a=rand()%3;
								switch(a)
								{
									case 0:
									{
										boss3.state=2;
										InitMonsterCrd();
									}break;
									case 1:
									{
										boss3.state=3;
										InitMonsterCrd();
									}break;
									case 2: boss3.state=4;break;
								}
							}
						}break;
					case 2:
						{
							Cir++;
							if((Cir%3==0)&&(Pic<4))	Pic++;
							if(Pic==4)
							{
								Cir=0;
								if((reaper[2].crd.x>WIDTH)&&(reaper[2].crd.y<-reaper[2].size.h))
									Pic++;
							}
							if((Pic>4)&&(Cir%3==0))
							{
								Pic++;
								if(Pic>6)
								{
									Pic=Cir=0;
									boss3.state=1;
									boss3.time.oldtime=boss3.time.newtime;
								}
							}
						}break;
					case 3:
						{
							Cir++;
							if((Cir%3==0)&&(Pic<4))	Pic++;
							if(Pic==4)
							{
								Cir=0;	
								if(dataeroder[0].crd.x>WIDTH)
									Pic++;
							}
							if((Pic>4)&&(Cir%3==0))
							{
								Pic++;
								if(Pic>8)
								{
									Pic=Cir=0;
									boss3.state=1;
									boss3.time.oldtime=boss3.time.newtime;
								}
							}
						}break;
					case 4:
						{
							Cir++;
							if(Cir%3==0) Pic++;
							if(Pic>4)
							{
								Pic=Cir=0;
								boss3.state=5;
								InitMonsterCrd();
								InitMonsterDmg();
							}
						}break;
					case 5:
						{
							Cir++;
							if((Cir%5==0)&&(Pic<4))	Pic++;
							if((abs(boss3.crd.x-47*WIDTH/140)<3*SPEED3)&&(abs(boss3.crd.y-19*HEIGHT/70)<3*SPEED3))
							{
								Pic=Cir=0;
								boss3.state=1;
								boss3.time.oldtime=boss3.time.newtime;
							}
						}break;
					default:;
				}
				boss3.time.newtime=GetTickCount();
				Sleep(1);
			}break;
		default:return 0;
	}
}

static void JudgeCrashMonster()
{
	switch(Sec)
	{
		case 1:
			{
				switch(Pro)
				{
				case 0:
			    {
 			    for(int i=0;i<24;i++)
				{
					for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>monster3_1[i].crd.x)&&(dataworm.crd[j].x+10<monster3_1[i].crd.x+monster3_1[i].size.w)&&(dataworm.crd[j].y>monster3_1[i].crd.y)&&(dataworm.crd[j].y+15<monster3_1[i].crd.y+monster3_1[i].size.h))
						{
							monster3_1[i].time.newtime=GetTickCount();
							if(monster3_1[i].time.newtime-monster3_1[i].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster3_1[i].dmg;
								DmgAni();
								monster3_1[i].time.oldtime=monster3_1[i].time.newtime;
							}
						}
					}
				}
				}break;
				case 1:
					{
						for(int i=0;i<24;i++)
							{
								for(int j=0;j<dataworm.node;j++)
								{
									if((dataworm.crd[j].x>monster3_1[i].crd.x)&&(dataworm.crd[j].x+10<monster3_1[i].crd.x+monster3_1[i].size.w)&&(dataworm.crd[j].y>monster3_1[i].crd.y)&&(dataworm.crd[j].y+15<monster3_1[i].crd.y+monster3_1[i].size.h))
									{
										monster3_1[i].time.newtime=GetTickCount();
										if(monster3_1[i].time.newtime-monster3_1[i].time.oldtime>DMGTIME)
										{
											dataworm.hp-=monster3_1[i].dmg;
											DmgAni();
											monster3_1[i].time.oldtime=monster3_1[i].time.newtime;
										}
									}
								}
							}
					}break;
				}
			}break;


			case 2:
			{
				switch(Pro)
				{
				case 0:
			    {
 			    for(int i=0;i<5;i++)
				{
					for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>monster3_2[i].crd.x)&&(dataworm.crd[j].x+10<monster3_2[i].crd.x+monster3_2[i].size.w)&&(dataworm.crd[j].y>monster3_2[i].crd.y)&&(dataworm.crd[j].y+15<monster3_2[i].crd.y+monster3_2[i].size.h))
						{
							monster3_2[i].time.newtime=GetTickCount();
							if(monster3_2[i].time.newtime-monster3_2[i].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster3_2[i].dmg;
								DmgAni();
								monster3_2[i].time.oldtime=monster3_2[i].time.newtime;
							}
						}
					}
				}
				}break;
				case 1:
					{
						for(int i=0;i<5;i++)
							{
								for(int j=0;j<dataworm.node;j++)
								{
									if((dataworm.crd[j].x>monster3_2[i].crd.x)&&(dataworm.crd[j].x+10<monster3_2[i].crd.x+monster3_2[i].size.w)&&(dataworm.crd[j].y>monster3_2[i].crd.y)&&(dataworm.crd[j].y+15<monster3_2[i].crd.y+monster3_2[i].size.h))
									{
										monster3_2[i].time.newtime=GetTickCount();
										if(monster3_2[i].time.newtime-monster3_2[i].time.oldtime>DMGTIME)
										{
											dataworm.hp-=monster3_2[i].dmg;
											DmgAni();
											monster3_2[i].time.oldtime=monster3_2[i].time.newtime;
										}
									}
								}
							}
					}break;
					case 2:
			    {
 			    for(int i=0;i<5;i++)
				{
					for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>monster3_2[i].crd.x)&&(dataworm.crd[j].x+10<monster3_2[i].crd.x+monster3_2[i].size.w)&&(dataworm.crd[j].y>monster3_2[i].crd.y)&&(dataworm.crd[j].y+15<monster3_2[i].crd.y+monster3_2[i].size.h))
						{
							monster3_2[i].time.newtime=GetTickCount();
							if(monster3_2[i].time.newtime-monster3_2[i].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster3_2[i].dmg;
								DmgAni();
								monster3_2[i].time.oldtime=monster3_2[i].time.newtime;
							}
						}
					}
				}
				}break;
				case 3:
			    {
 			    for(int i=0;i<5;i++)
				{
					for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>monster3_2[i].crd.x)&&(dataworm.crd[j].x+10<monster3_2[i].crd.x+monster3_2[i].size.w)&&(dataworm.crd[j].y>monster3_2[i].crd.y)&&(dataworm.crd[j].y+15<monster3_2[i].crd.y+monster3_2[i].size.h))
						{
							monster3_2[i].time.newtime=GetTickCount();
							if(monster3_2[i].time.newtime-monster3_2[i].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster3_2[i].dmg;
								DmgAni();
								monster3_2[i].time.oldtime=monster3_2[i].time.newtime;
							}
						}
					}
				}
				}break;
				}
			}break;

			case 3:
			{
				switch(Pro)
				{
				case 0:
			    {
 			    for(int i=0;i<39;i++)
				{
					for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>monster3_3[i].crd.x)&&(dataworm.crd[j].x+10<monster3_3[i].crd.x+monster3_3[i].size.w)&&(dataworm.crd[j].y>monster3_3[i].crd.y)&&(dataworm.crd[j].y+15<monster3_3[i].crd.y+monster3_3[i].size.h))
						{
							monster3_3[i].time.newtime=GetTickCount();
							if(monster3_3[i].time.newtime-monster3_3[i].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster3_3[i].dmg;
								DmgAni();
								monster3_3[i].time.oldtime=monster3_3[i].time.newtime;
							}
						}
					}
				}
				}break;
				case 1:
					{
						for(int i=0;i<39;i++)
							{
								for(int j=0;j<dataworm.node;j++)
								{
									if((dataworm.crd[j].x>monster3_3[i].crd.x)&&(dataworm.crd[j].x+10<monster3_3[i].crd.x+monster3_3[i].size.w)&&(dataworm.crd[j].y>monster3_3[i].crd.y)&&(dataworm.crd[j].y+15<monster3_3[i].crd.y+monster3_3[i].size.h))
									{
										monster3_3[i].time.newtime=GetTickCount();
										if(monster3_3[i].time.newtime-monster3_3[i].time.oldtime>DMGTIME)
										{
											dataworm.hp-=monster3_3[i].dmg;
											DmgAni();
											monster3_3[i].time.oldtime=monster3_3[i].time.newtime;
										}
									}
								}
							}
					}break;
				}
			}break;

			case 4:
			{
				for(int i=0;i<17;i++)
				{
					for(int j=0;j<dataworm.node;j++)
					{
						if((dataworm.crd[j].x>monster3_4[i].crd.x)&&(dataworm.crd[j].x+10<monster3_4[i].crd.x+monster3_4[i].size.w)&&(dataworm.crd[j].y>monster3_4[i].crd.y)&&(dataworm.crd[j].y+15<monster3_4[i].crd.y+monster3_4[i].size.h))
						{
							monster3_4[i].time.newtime=GetTickCount();
							if(monster3_4[i].time.newtime-monster3_4[i].time.oldtime>DMGTIME)
							{
							    dataworm.hp-=monster3_4[i].dmg;
								DmgAni();
								monster3_4[i].time.oldtime=monster3_4[i].time.newtime;
							}
						}
					}
				}
			}break;
			case 5:
				{
					switch(boss3.state)
					{
						case 1:
							{
								  for(int j=0;j<dataworm.node;j++)
								{
									if((dataworm.crd[j].x>47*WIDTH/140)&&(dataworm.crd[j].x+10<47*WIDTH/140+boss3.size.w)&&(dataworm.crd[j].y>19*HEIGHT/70)&&(dataworm.crd[j].y+15<19*HEIGHT/70+boss3.size.h))
									{
										boss3.dmgtime.newtime=GetTickCount();
										if(boss3.dmgtime.newtime-boss3.dmgtime.oldtime>DMGTIME)
										{
											dataworm.hp-=boss3.dmg;
											DmgAni();
											boss3.dmgtime.oldtime=boss3.dmgtime.newtime;
										}
									}
								}
							}break;
						case 2:
							{
								for(int j=0;j<dataworm.node;j++)
								{
									if((dataworm.crd[j].x>3*WIDTH/10)&&(dataworm.crd[j].x+10<7*WIDTH/10)&&(dataworm.crd[j].y>HEIGHT/4)&&(dataworm.crd[j].y+15<3*HEIGHT/4))
									{
										boss3.dmgtime.newtime=GetTickCount();
										if(boss3.dmgtime.newtime-boss3.dmgtime.oldtime>DMGTIME)
										{
											dataworm.hp-=boss3.dmg;
											DmgAni();
											boss3.dmgtime.oldtime=boss3.dmgtime.newtime;
										}
									}
									if(Pic==4)
									{
										for(int i=0;i<16;i++)
										{
											if((dataworm.crd[j].x>reaper[i].crd.x)&&(dataworm.crd[j].x+10<reaper[i].crd.x+reaper[i].size.w)&&(dataworm.crd[j].y>reaper[i].crd.y)&&(dataworm.crd[j].y+15<reaper[i].crd.y+reaper[i].size.h))
											{
												reaper[i].time.newtime=GetTickCount();
												if(reaper[i].time.newtime-reaper[i].time.oldtime>DMGTIME)
												{
													dataworm.hp-=reaper[i].dmg;
													DmgAni();
													reaper[i].time.oldtime=reaper[i].time.newtime;
												}
											}
										}
									}
								}
							}break;
						case 3:
							{
								for(int j=0;j<dataworm.node;j++)
								{
									if((dataworm.crd[j].x>3*WIDTH/10)&&(dataworm.crd[j].x+10<7*WIDTH/10)&&(dataworm.crd[j].y>3*HEIGHT/10)&&(dataworm.crd[j].y+15<7*HEIGHT/10))
									{
										boss3.dmgtime.newtime=GetTickCount();
										if(boss3.dmgtime.newtime-boss3.dmgtime.oldtime>DMGTIME)
										{
											dataworm.hp-=boss3.dmg;
											DmgAni();
											boss3.dmgtime.oldtime=boss3.dmgtime.newtime;
										}
									}
									if(Pic==4)
									{
										for(int i=0;i<24;i++)
										{
											if((dataworm.crd[j].x>dataeroder[i].crd.x)&&(dataworm.crd[j].x+10<dataeroder[i].crd.x+dataeroder[i].size.w)&&(dataworm.crd[j].y>dataeroder[i].crd.y)&&(dataworm.crd[j].y+5<dataeroder[i].crd.y+dataeroder[i].size.h))
											{
												dataeroder[i].time.newtime=GetTickCount();
												if(dataeroder[i].time.newtime-dataeroder[i].time.oldtime>DMGTIME)
												{
													dataworm.hp-=reaper[i].dmg;
													DmgAni();
													dataeroder[i].time.oldtime=dataeroder[i].time.newtime;
												}
											}
										}
									}
								}
							}break;
						case 5:
							{
								if(Pic==4)
								{
									for(int j=0;j<dataworm.node;j++)
									{
										if((dataworm.crd[j].x>boss3.crd.x)&&(dataworm.crd[j].x+10<boss3.crd.x+boss3.size.w)&&(dataworm.crd[j].y>boss3.crd.y)&&(dataworm.crd[j].y+15<boss3.crd.y+boss3.size.h))
										{
											boss3.dmgtime.newtime=GetTickCount();
											if(boss3.dmgtime.newtime-boss3.dmgtime.oldtime>DMGTIME)
											{
												dataworm.hp-=boss3.dmg;
												DmgAni();
												boss3.dmgtime.oldtime=boss3.dmgtime.newtime;
											}
										}
									}
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
