#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include <cstdlib>
#include <ctime>
#include"game.h"
#pragma comment(lib,"Winmm.lib")

//////////////////////////////////////////////////////////////////////////////////////////
//����ȫ�ֱ���
int Lv,Sec,Cir,Pro,Pic,Pic1,Getdatanum,Speed=1;			/*����ȫ�ֱ���:	Lv:��ѡ����
															Sec:��¼��ǰС�ڵ�ȫ�ֱ���
															Cir:��¼��ѭ��������ȫ�ֱ���
															Pro:��¼��ǰС�ڽ��̵�ȫ�ֱ���
															Pic:���ڻ�ͼ��ȫ�ֱ���
															Getdatanum:��¼����ѻ�õ���������ȫ�ֱ���
										*/
bool w2,w3;								//�Ƿ��ܽ���ڶ�������
IMAGE bkimg;							//���ñ���ͼ��ȫ�ֱ���
IMAGE menubkimg[15];					//���������汳��ͼ������
IMAGE bkimgani[21];						//������С�ڶ���ͼ������

BUTTON button[7];						//�洢�����水ť��Ϣ�Ľṹ������

DATA data[DATANUM];						//���������Ϣ�Ľṹ������
DATAWORM dataworm;						//������������Ϣ�Ľṹ�����

BOSS1 boss1;
BOSS2 boss2;
BOSS3 boss3;

SP Poi[NUM];
int SnowPoint_R=2;
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
//��������

void InitGame()							//��ʼ����Ϸ(δ���)
{
	initgraph(WIDTH,HEIGHT);
	
	loadimage(&menubkimg[0],_T("��ʽͼ\\UI\\������1.jpg"));
	loadimage(&menubkimg[1],_T("��ʽͼ\\UI\\������2.jpg"));
	loadimage(&menubkimg[2],_T("��ʽͼ\\UI\\������3.jpg"));
	loadimage(&menubkimg[3],_T("��ʽͼ\\UI\\������4.jpg"));
	loadimage(&menubkimg[4],_T("��ʽͼ\\UI\\������3.jpg"));
	loadimage(&menubkimg[5],_T("��ʽͼ\\UI\\������2.jpg"));
	loadimage(&menubkimg[6],_T("��ʽͼ\\UI\\������1.jpg"));
	loadimage(&menubkimg[7],_T("��ʽͼ\\UI\\������5.jpg"));
	loadimage(&menubkimg[8],_T("��ʽͼ\\UI\\������6.jpg"));
	loadimage(&menubkimg[9],_T("��ʽͼ\\UI\\������7.jpg"));
	loadimage(&menubkimg[10],_T("��ʽͼ\\UI\\������6.jpg"));
	loadimage(&menubkimg[11],_T("��ʽͼ\\UI\\������5.jpg"));
	loadimage(&menubkimg[12],_T("��ʽͼ\\UI\\������1.jpg"));
	loadimage(&menubkimg[13],_T("��ʽͼ\\UI\\��������.jpg"));
	loadimage(&menubkimg[14],_T("��ʽͼ\\UI\\������Ա����.jpg"));
	
	loadimage(&button[0].img[0],_T("��ʽͼ\\UI\\��һ�ذ�ť(�ȴ�).jpg"));
	loadimage(&button[0].img[1],_T("��ʽͼ\\UI\\��һ�ذ�ť(�ȴ�).jpg"));
	loadimage(&button[0].img[2],_T("��ʽͼ\\UI\\��һ�ذ�ť����_01.jpg"));
	loadimage(&button[0].img[3],_T("��ʽͼ\\UI\\��һ�ذ�ť����_02.jpg"));
	loadimage(&button[0].img[4],_T("��ʽͼ\\UI\\��һ�ذ�ť����_03.jpg"));
	loadimage(&button[1].img[0],_T("��ʽͼ\\UI\\�ڶ��ذ�ť(δ����).jpg"));
	loadimage(&button[1].img[1],_T("��ʽͼ\\UI\\�ڶ��ذ�ť(�ȴ�).jpg"));
	loadimage(&button[1].img[2],_T("��ʽͼ\\UI\\�ڶ��ذ�ť����_01.jpg"));
	loadimage(&button[1].img[3],_T("��ʽͼ\\UI\\�ڶ��ذ�ť����_02.jpg"));
	loadimage(&button[1].img[4],_T("��ʽͼ\\UI\\�ڶ��ذ�ť����_03.jpg"));
	loadimage(&button[2].img[0],_T("��ʽͼ\\UI\\�����ذ�ť(δ����).jpg"));
	loadimage(&button[2].img[1],_T("��ʽͼ\\UI\\�����ذ�ť(�ȴ�).jpg"));
	loadimage(&button[2].img[2],_T("��ʽͼ\\UI\\�����ذ�ť����_01.jpg"));
	loadimage(&button[2].img[3],_T("��ʽͼ\\UI\\�����ذ�ť����_02.jpg"));
	loadimage(&button[2].img[4],_T("��ʽͼ\\UI\\�����ذ�ť����_03.jpg"));

	for(int i=0;i<2;i++)
	{
		loadimage(&button[3].img[i],_T("��ʽͼ\\UI\\������ť(�ȴ�).jpg"));
		loadimage(&button[4].img[i],_T("��ʽͼ\\UI\\������Ա��ť(�ȴ�).jpg"));
		loadimage(&button[5].img[i],_T("��ʽͼ\\UI\\�˳���ť(�ȴ�).jpg"));
	}
	for(int i=3;i<7;i++)
	{
		loadimage(&button[i].img[2],_T("��ʽͼ\\UI\\��ť����_01.jpg"));
		loadimage(&button[i].img[3],_T("��ʽͼ\\UI\\��ť����_02.jpg"));
		loadimage(&button[i].img[4],_T("��ʽͼ\\UI\\��ť����_03.jpg"));
	}

	button[0].crd.x=460*WIDTH/700,			button[0].crd.y=18*HEIGHT/700;
	button[1].crd.x=529*WIDTH/700,			button[1].crd.y=140*HEIGHT/700;
	button[2].crd.x=550*WIDTH/700,			button[2].crd.y=290*HEIGHT/700;
	button[3].crd.x=63*WIDTH/700,			button[3].crd.y=176*HEIGHT/700;
	button[4].crd.x=67*WIDTH/700,			button[4].crd.y=300*HEIGHT/700;
	button[5].crd.x=140*WIDTH/700,			button[5].crd.y=410*HEIGHT/700;
	button[6].crd.x=322*WIDTH/700,			button[6].crd.y=610*HEIGHT/700;

	w2=w3=false;
	EnterAni();
}

void Init()
{
	setbkcolor(BLACK);
	setcolor(WHITE);
	cleardevice();
	srand(unsigned int(time(NULL)));
	for(int i=0,j;i<NUM;i++)
	{
		Poi[i].x=20*rand()%700+10;
		Poi[i].y=-(rand()%670);
		j=rand()%2;
		switch(j)
		{
			case 0:Poi[i].style="0";break;
			case 1:Poi[i].style="1";
		}
	}
}
void Blur(DWORD *pMem)
{
	for(int i = 700*2; i < 700 * 698; i++)
	{
		pMem[i] = RGB(
		(GetRValue(pMem[i]) + GetRValue(pMem[i - 700]) + GetRValue(pMem[i - 1]) + GetRValue(pMem[i + 1]) + GetRValue(pMem[i + 700])+GetRValue(pMem[i+700*2])+GetRValue(pMem[i-700*2])) / 7,
		(GetGValue(pMem[i]) + GetGValue(pMem[i - 700]) + GetGValue(pMem[i - 1]) + GetGValue(pMem[i + 1]) + GetGValue(pMem[i + 700])+GetGValue(pMem[i+700*2])+GetGValue(pMem[i-700*2])) / 7,
		(GetBValue(pMem[i]) + GetBValue(pMem[i - 700]) + GetBValue(pMem[i - 1]) + GetBValue(pMem[i + 1]) + GetBValue(pMem[i + 700])+GetBValue(pMem[i+700*2])+GetBValue(pMem[i-700*2])) / 7);
	}
	for(int x=0;x<700;x++)
	{
		pMem[x]=GREEN;
		pMem[700*699+x]=GREEN;
		pMem[700*699+x]=GREEN;
		pMem[700+x]=GREEN;
	}
}
void Draw()
{
	DrawSnowPoint();
	for(int i=0;i<NUM;i++)
	{
		if((Poi[i].y>=700)) 
		{
			Poi[i].y=0;
			Poi[i].x=20*rand()%700+10;
		}
	}
	for(int y=0;y<NUM;y++)
	{
		Poi[y].y+=Speed;
	}
}
void DrawSnowPoint()
{
	for(int i=0;i<NUM;i++)
		outtextxy(Poi[i].x,Poi[i].y,Poi[i].style);
}


void EnterAni()
{
	mciSendString("open �������ּ���Ч\\BGM06.mp3 alias mymusic", NULL, 0, NULL);
	mciSendString("play �������ּ���Ч\\BGM06.mp3 repeat", NULL, 0, NULL);
	MOUSEMSG m; 
	IMAGE img;
	loadimage(&img,_T("��ʽͼ\\UI\\LOGO.jpg"));
	Init();
	DWORD *Buff=GetImageBuffer();
	BeginBatchDraw();
	setcolor(GREEN);
	while(true)
	{
		if(MouseHit())
			{
				m = GetMouseMsg();
				if(m.uMsg==WM_LBUTTONDOWN)
				{
					for(int i=10;i<=200;i++)
					{
						Speed=i/10;
						Draw();
						Blur(Buff);
						FlushBatchDraw();
					}
					for(int i=0;i<300;i++)
					{
						Draw();
						Blur(Buff);
						FlushBatchDraw();
					}
					for(int i=180;i>=0;i--)
					{
						setcolor(RGB(0,i,0));
						Draw();
						Blur(Buff);
						FlushBatchDraw();
					}
					mciSendString("stop �������ּ���Ч\\BGM06.mp3", NULL, 0, NULL);
					mciSendString("close �������ּ���Ч\\BGM06.mp3", NULL, 0, NULL);
					StartGame();
					return;
				}
			}
		Draw();
		Blur(Buff);
		putimage((WIDTH-327)/2,(HEIGHT-163)/2,&img);
		FlushBatchDraw();
	}
}



void StartGame()
{
	mciSendString("open �������ּ���Ч\\BGM00.mp3 alias mymusic", NULL, 0, NULL);
	mciSendString("play �������ּ���Ч\\BGM00.mp3 repeat", NULL, 0, NULL);

	MOUSEMSG m; 
	Cir=Pic=0,Pic1=2;
	BeginBatchDraw();
	while(true)
	{
		Cir++;
		putimage(0,0,&menubkimg[Pic]);
		if(Cir%1000==0)	Pic++;
		if(Pic>12)		Pic=0;

		if(Cir%200==0)	Pic1++;
		if(Pic1>4)		Pic1=2;

		if(MouseHit())	m = GetMouseMsg();

		if((m.x>=button[0].crd.x)&&(m.x<=button[0].crd.x+BUTTONWIDTH)&&(m.y>=button[0].crd.y)&&(m.y<=button[0].crd.y+BUTTONHEIGHT))
		{
			putimage(button[0].crd.x,button[0].crd.y,&button[0].img[Pic1]);
			if(m.uMsg==WM_LBUTTONDOWN)
			{
				Lv=1;
				mciSendString("stop �������ּ���Ч\\BGM00.mp3", NULL, 0, NULL);
				mciSendString("close �������ּ���Ч\\BGM00.mp3", NULL, 0, NULL);
				InitGameLevel();
			}
		}
		else putimage(button[0].crd.x,button[0].crd.y,&button[0].img[1]);

		if(w2==true)
		{
			if((m.x>=button[1].crd.x)&&(m.x<=button[1].crd.x+BUTTONWIDTH)&&(m.y>=button[1].crd.y)&&(m.y<=button[1].crd.y+BUTTONHEIGHT))
			{

				putimage(button[1].crd.x,button[1].crd.y,&button[1].img[Pic1]);

				if(m.uMsg==WM_LBUTTONDOWN)
				{
					Lv=2;
					mciSendString("stop �������ּ���Ч\\BGM00.mp3", NULL, 0, NULL);
					mciSendString("close �������ּ���Ч\\BGM00.mp3", NULL, 0, NULL);
					InitGameLevel();
				}
			}
			else putimage(button[1].crd.x,button[1].crd.y,&button[1].img[1]);
		}
		else putimage(button[1].crd.x,button[1].crd.y,&button[1].img[0]);

		if(w3==true)
		{
			if((m.x>=button[2].crd.x)&&(m.x<=button[2].crd.x+BUTTONWIDTH)&&(m.y>=button[2].crd.y)&&(m.y<=button[2].crd.y+BUTTONHEIGHT))
			{

				putimage(button[2].crd.x,button[2].crd.y,&button[2].img[Pic1]);

				if(m.uMsg==WM_LBUTTONDOWN)
				{
					Lv=3;
					mciSendString("stop �������ּ���Ч\\BGM00.mp3", NULL, 0, NULL);
					mciSendString("close �������ּ���Ч\\BGM00.mp3", NULL, 0, NULL);
					InitGameLevel();
				}
			}
			else putimage(button[2].crd.x,button[2].crd.y,&button[2].img[1]);
		}
		else putimage(button[2].crd.x,button[2].crd.y,&button[2].img[0]);

		for(int i=3;i<6;i++)
			if((m.x>=button[i].crd.x)&&(m.x<=button[i].crd.x+BUTTONWIDTH)&&(m.y>=button[i].crd.y)&&(m.y<=button[i].crd.y+BUTTONHEIGHT))
			{
				putimage(button[i].crd.x,button[i].crd.y,&button[i].img[Pic1]);

				if(m.uMsg==WM_LBUTTONDOWN)
					switch(i)
					{
						case 3:	EnterHf();Sleep(500);break;
						case 4:	EnterCf();Sleep(500);break;
						case 5:	return;
					}
			}
			else putimage(button[i].crd.x,button[i].crd.y,&button[i].img[1]);
	FlushBatchDraw();
	if(Cir>30000)	Cir=0;
	}
}

void EnterHf()
{
	Cir=0,Pic1=2;
	MOUSEMSG m; 
	for(int i=-WIDTH;i<=0;i++)
	{
		putimage(i,0,&menubkimg[13]);
		FlushBatchDraw();
		Sleep(1);
	}
	while(1)
	{
		Cir++;
		if(Cir%200==0)	Pic1++;
		if(Pic1>4)		Pic1=2;

		if(MouseHit())	m = GetMouseMsg();
		if((m.x>=button[6].crd.x)&&(m.x<=button[6].crd.x+BUTTONWIDTH)&&(m.y>=button[6].crd.y)&&(m.y<=button[6].crd.y+BUTTONHEIGHT))
		{
			putimage(button[6].crd.x,button[6].crd.y,&button[6].img[Pic1]);
			if(m.uMsg==WM_LBUTTONDOWN)
			{
				Cir=0,Pic1=2;
				return ;
			}
		}
		FlushBatchDraw();
	}
}

void EnterCf()
{
	
	Cir=0,Pic1=2;
	MOUSEMSG m; 
	for(int i=-WIDTH;i<=0;i++)
	{
		putimage(i,0,&menubkimg[14]);
		FlushBatchDraw();
		Sleep(1);
	}
	while(1)
	{
		Cir++;
		if(Cir%200==0)	Pic1++;
		if(Pic1>4)		Pic1=2;

		if(MouseHit())	m = GetMouseMsg();
		if((m.x>=button[6].crd.x)&&(m.x<=button[6].crd.x+BUTTONWIDTH)&&(m.y>=button[6].crd.y)&&(m.y<=button[6].crd.y+BUTTONHEIGHT))
		{
			putimage(button[6].crd.x,button[6].crd.y,&button[6].img[Pic1]);
			if(m.uMsg==WM_LBUTTONDOWN)
			{
				Cir=0,Pic1=2;
				return ;
			}
		}
		else cleardevice(),putimage(0,0,&menubkimg[14]);
		FlushBatchDraw();
	}
}



void InitGameLevel()				//��ʼ���ؿ�
{
	srand((unsigned int)time(NULL));

	for(int i=0;i<DATANUM;i++)
		data[i].settime.oldtime=0;

	Sec=1;
	InitDataworm();
	switch(Lv)
	{
		case 1:
		{
			loadimage(&bkimg,_T("��ʽͼ\\����1.jpg"));
			putimage(0,0,&bkimg);
			 EnterGmLv1();
		}break;
		case 2:
		{
			loadimage(&bkimg,_T("��ʽͼ\\����2.jpg"));
			putimage(0,0,&bkimg);
			EnterGmLv2();
		}break;
		case 3:
		{
			loadimage(&bkimg,_T("��ʽͼ\\����3.jpg"));
			putimage(0,0,&bkimg);
			EnterGmLv3();
		}break;
	}
}

void InitSection()					
{
	Getdatanum=0;
	Cir=Pro=Pic=0;
	if((Lv==2)&&(Sec==5))	
		boss2.state=0;
	if((Lv==3)&&(Sec==5))
		boss3.state=0;
	for(int i=0;i<DATANUM;i++)			//��ʼ����������
		data[i].flag=0;
	switch(Lv)
	{
		case 1:
			{
				loadimage(&bkimgani[0],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_01.jpg"));
				loadimage(&bkimgani[1],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_02.jpg"));
				loadimage(&bkimgani[2],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_03.jpg"));
				loadimage(&bkimgani[3],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_04.jpg"));
				loadimage(&bkimgani[4],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_05.jpg"));
				loadimage(&bkimgani[5],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_06.jpg"));
				loadimage(&bkimgani[6],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_07.jpg"));
				loadimage(&bkimgani[7],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_08.jpg"));
				loadimage(&bkimgani[8],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_09.jpg"));
				loadimage(&bkimgani[9],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_10.jpg"));
				loadimage(&bkimgani[10],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_11.jpg"));
				loadimage(&bkimgani[11],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_12.jpg"));
				loadimage(&bkimgani[12],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_13.jpg"));
				loadimage(&bkimgani[13],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_14.jpg"));
				loadimage(&bkimgani[14],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_15.jpg"));
				loadimage(&bkimgani[15],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_16.jpg"));
				loadimage(&bkimgani[16],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_17.jpg"));
				loadimage(&bkimgani[17],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_18.jpg"));
				loadimage(&bkimgani[18],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_19.jpg"));
				loadimage(&bkimgani[19],_T("��ʽͼ\\����ͼ\\��һ��ˢ��С�ڶ���_20.jpg"));
				loadimage(&bkimgani[20],_T("��ʽͼ\\����1.jpg"));
			}break;
		case 2:
			{
				loadimage(&bkimgani[0],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_01.jpg"));
				loadimage(&bkimgani[1],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_02.jpg"));
				loadimage(&bkimgani[2],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_03.jpg"));
				loadimage(&bkimgani[3],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_04.jpg"));
				loadimage(&bkimgani[4],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_05.jpg"));
				loadimage(&bkimgani[5],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_06.jpg"));
				loadimage(&bkimgani[6],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_07.jpg"));
				loadimage(&bkimgani[7],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_08.jpg"));
				loadimage(&bkimgani[8],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_09.jpg"));
				loadimage(&bkimgani[9],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_10.jpg"));
				loadimage(&bkimgani[10],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_11.jpg"));
				loadimage(&bkimgani[11],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_12.jpg"));
				loadimage(&bkimgani[12],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_13.jpg"));
				loadimage(&bkimgani[13],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_14.jpg"));
				loadimage(&bkimgani[14],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_15.jpg"));
				loadimage(&bkimgani[15],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_16.jpg"));
				loadimage(&bkimgani[16],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_17.jpg"));
				loadimage(&bkimgani[17],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_18.jpg"));
				loadimage(&bkimgani[18],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_19.jpg"));
				loadimage(&bkimgani[19],_T("��ʽͼ\\����ͼ\\�ڶ���ˢ��С�ڶ���_20.jpg"));
				loadimage(&bkimgani[20],_T("��ʽͼ\\����2.jpg"));
			}break;
		case 3:
			{
				loadimage(&bkimgani[0],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_01.jpg"));
				loadimage(&bkimgani[1],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_02.jpg"));
				loadimage(&bkimgani[2],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_03.jpg"));
				loadimage(&bkimgani[3],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_04.jpg"));
				loadimage(&bkimgani[4],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_05.jpg"));
				loadimage(&bkimgani[5],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_06.jpg"));
				loadimage(&bkimgani[6],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_07.jpg"));
				loadimage(&bkimgani[7],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_08.jpg"));
				loadimage(&bkimgani[8],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_09.jpg"));
				loadimage(&bkimgani[9],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_10.jpg"));
				loadimage(&bkimgani[10],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_11.jpg"));
				loadimage(&bkimgani[11],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_12.jpg"));
				loadimage(&bkimgani[12],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_13.jpg"));
				loadimage(&bkimgani[13],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_14.jpg"));
				loadimage(&bkimgani[14],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_15.jpg"));
				loadimage(&bkimgani[15],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_16.jpg"));
				loadimage(&bkimgani[16],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_17.jpg"));
				loadimage(&bkimgani[17],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_18.jpg"));
				loadimage(&bkimgani[18],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_19.jpg"));
				loadimage(&bkimgani[19],_T("��ʽͼ\\����ͼ\\������ˢ��С�ڶ���_20.jpg"));
				loadimage(&bkimgani[20],_T("��ʽͼ\\����3.jpg"));
			}
	}
}

void InitDataworm()
{
	dataworm.node=2;
	switch(Lv)
	{
		case 1: dataworm.hp=500;break;
		case 2: dataworm.hp=700;break;
		case 3: dataworm.hp=900;break;
		default :;
	}
	
	dataworm.crd[0].x=WIDTH/2,dataworm.crd[0].y=HEIGHT/2,dataworm.type[0]=0;
	dataworm.crd[1].x=WIDTH/2,dataworm.crd[1].y=HEIGHT/2+15;
	dataworm.dir=up;
	ShowDataworm();
}

void ShowDataworm()
{
	if(dataworm.hp>=HP_A)									
		switch(Lv)
		{	
			case 1:	setcolor(COLOR1_A);break;
			case 2: setcolor(COLOR2_A);break;
			case 3: setcolor(COLOR3_A);
		}

	else if(dataworm.hp>=HP_B&&dataworm.hp<HP_A)			
		switch(Lv)
		{	
			case 1:	setcolor(COLOR1_B);break;
			case 2: setcolor(COLOR2_B);break;
			case 3: setcolor(COLOR3_B);
		}
	else if(dataworm.hp>=HP_C&&dataworm.hp<HP_B)			
		switch(Lv)
		{	
			case 1:	setcolor(COLOR1_C);break;
			case 2: setcolor(COLOR2_C);break;
			case 3: setcolor(COLOR3_C);
		}
	else if(dataworm.hp>=HP_D&&dataworm.hp<HP_C)
		switch(Lv)
		{	
			case 1:	setcolor(COLOR1_D);break;
			case 2: setcolor(COLOR2_D);break;
			case 3: setcolor(COLOR3_D);
		}
	else if(dataworm.hp>=HP_E&&dataworm.hp<HP_D)
		switch(Lv)
		{	
			case 1:	setcolor(COLOR1_E);break;
			case 2: setcolor(COLOR2_E);break;
			case 3: setcolor(COLOR3_E);
		}
	else
		switch(Lv)
		{	
			case 1:	setcolor(COLOR1_F);break;
			case 2: setcolor(COLOR2_F);break;
			case 3: setcolor(COLOR3_F);
		}
	
	for(int i=dataworm.node-1;i>1;i--)
	{
		switch(dataworm.type[i])
		{
			case 0:	outtextxy(dataworm.crd[i].x-3,dataworm.crd[i].y-7,_T("0"));break;
			case 1:	outtextxy(dataworm.crd[i].x-3,dataworm.crd[i].y-7,_T("1"));
		}
	}

	dataworm.type[1]=rand()%2;									//��������������ڶ��ڵ��������ͣ�0��1��
	switch(dataworm.type[1])
	{
		case 0:	outtextxy(dataworm.crd[1].x-3,dataworm.crd[1].y-7,_T("0"));break;
		case 1:	outtextxy(dataworm.crd[1].x-3,dataworm.crd[1].y-7,_T("1"));
	}

	setcolor(WHITE);
	outtextxy(dataworm.crd[0].x-3,dataworm.crd[0].y-7,_T("0"));

	//setcolor(BLACK);
	//outtextxy(dataworm.crd[dataworm.node].x-3,dataworm.crd[dataworm.node].y-7,_T("0"));

	if(dataworm.hp>=HP_A)									
		switch(Lv)
		{	
			case 1:	setcolor(COLOR1_A);break;
			case 2: setcolor(COLOR2_A);break;
			case 3: setcolor(COLOR3_A);
		}

	else if(dataworm.hp>=HP_B&&dataworm.hp<HP_A)			
		switch(Lv)
		{	
			case 1:	setcolor(COLOR1_B);break;
			case 2: setcolor(COLOR2_B);break;
			case 3: setcolor(COLOR3_B);
		}
	else if(dataworm.hp>=HP_C&&dataworm.hp<HP_B)			
		switch(Lv)
		{	
			case 1:	setcolor(COLOR1_C);break;
			case 2: setcolor(COLOR2_C);break;
			case 3: setcolor(COLOR3_C);
		}
	else if(dataworm.hp>=HP_D&&dataworm.hp<HP_C)
		switch(Lv)
		{	
			case 1:	setcolor(COLOR1_D);break;
			case 2: setcolor(COLOR2_D);break;
			case 3: setcolor(COLOR3_D);
		}
	else if(dataworm.hp>=HP_E&&dataworm.hp<HP_D)
		switch(Lv)
		{	
			case 1:	setcolor(COLOR1_E);break;
			case 2: setcolor(COLOR2_E);break;
			case 3: setcolor(COLOR3_E);
		}
	else
		switch(Lv)
		{	
			case 1:	setcolor(COLOR1_F);break;
			case 2: setcolor(COLOR2_F);break;
			case 3: setcolor(COLOR3_F);
		}
	outtextxy(dataworm.crd[dataworm.node-1].x-3,dataworm.crd[dataworm.node-1].y-7,_T("0"));
}

void  MoveDataworm()
{
	for(int i=dataworm.node;i>0;i--)
	{
		dataworm.crd[i].x=dataworm.crd[i-1].x;
		dataworm.crd[i].y=dataworm.crd[i-1].y;
		dataworm.type[i]=dataworm.type[i-1];
	}
	switch(dataworm.dir)
	{
		case up:			
		{
			if(dataworm.crd[0].y>=0)	dataworm.crd[0].y-=15;
			else dataworm.crd[0].y=HEIGHT;
		}break;
		case down:			
		{
			if(dataworm.crd[0].y<=HEIGHT)	dataworm.crd[0].y+=15;
			else dataworm.crd[0].y=0;
		}break;
		case left:			
		{
			if(dataworm.crd[0].x>=0)	dataworm.crd[0].x-=10;
			else	dataworm.crd[0].x=WIDTH;
		}break;
		case right:			
		{
			if(dataworm.crd[0].x<=WIDTH)	dataworm.crd[0].x+=10;
			else	dataworm.crd[0].x=0;
		}break;
		case leftup:		
		{
			if(dataworm.crd[0].x>=0)	dataworm.crd[0].x-=10;
			else	dataworm.crd[0].x=WIDTH;
			if(dataworm.crd[0].y>=0)	dataworm.crd[0].y-=15;
			else	dataworm.crd[0].y=HEIGHT;
		}break;
		case rightup:		
		{
			if(dataworm.crd[0].x<=WIDTH)	dataworm.crd[0].x+=10;
			else	dataworm.crd[0].x=0;
			if(dataworm.crd[0].y>=0)		dataworm.crd[0].y-=15;
			else	dataworm.crd[0].y=HEIGHT;
		}break;
		case leftdown:		
		{
			if(dataworm.crd[0].x>=0)	dataworm.crd[0].x-=10;
			else	dataworm.crd[0].x=WIDTH;
			if(dataworm.crd[0].y<=HEIGHT)	dataworm.crd[0].y+=15;
			else	dataworm.crd[0].y=0;
		}break;
		case rightdown:		
		{
			if(dataworm.crd[0].x<=WIDTH)	dataworm.crd[0].x+=10;
			else	dataworm.crd[0].x=0;
			if(dataworm.crd[0].y<=HEIGHT)	dataworm.crd[0].y+=15;
			else	dataworm.crd[0].y=0;
		}
	}
	ShowDataworm();
}


int GetCommand()						//�����ò���ָ��ĺ�����δ��ɣ�
{
	int c=0;
	
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)														c |= CMD_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)													c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)														c |= CMD_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)														c |= CMD_DOWN;
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000)&&(GetAsyncKeyState(VK_UP) & 0x8000))				c |= CMD_LEFTUP;
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)&&(GetAsyncKeyState(VK_UP) & 0x8000))				c |= CMD_RIGHTUP;
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000)&&(GetAsyncKeyState(VK_DOWN) & 0x8000))				c |= CMD_LEFTDOWN;
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)&&(GetAsyncKeyState(VK_DOWN) & 0x8000))			c |= CMD_RIGHTDOWN;

	return c;
}


void DispatchCommand(int _cmd)
{
	if (_cmd & CMD_UP)			if(dataworm.dir!=down)			dataworm.dir=up;		else  _cmd=0;
	if (_cmd & CMD_DOWN)		if(dataworm.dir!=up)			dataworm.dir=down;		else  _cmd=0;
	if (_cmd & CMD_LEFT)		if(dataworm.dir!=right)			dataworm.dir=left;		else  _cmd=0;
	if (_cmd & CMD_RIGHT)		if(dataworm.dir!=left)			dataworm.dir=right;		else  _cmd=0;
	if (_cmd & CMD_LEFTUP)		if(dataworm.dir!=rightdown)		dataworm.dir=leftup;	else  _cmd=0;
	if (_cmd & CMD_RIGHTUP)		if(dataworm.dir!=leftdown)		dataworm.dir=rightup;	else  _cmd=0;
	if (_cmd & CMD_LEFTDOWN)	if(dataworm.dir!=rightup)		dataworm.dir=leftdown;	else  _cmd=0;
	if (_cmd & CMD_RIGHTDOWN)	if(dataworm.dir!=leftup)		dataworm.dir=rightdown;	else  _cmd=0;

	if(_cmd!=0)	MoveDataworm();
}

void SetData()
{
	int cdtime;
	for(int i=0;i<DATANUM;i++)
	{
		if(data[i].flag==0)
		{
			data[i].settime.newtime=GetTickCount();
			if((Sec!=5)||(Lv!=3))	cdtime=4000;
			else					cdtime=6000;
			if(data[i].settime.newtime-data[i].settime.oldtime>=cdtime)
			{
				data[i].type=rand()%2;
				if((Lv!=3)&&(Sec!=4)&&(Sec!=5))
				{
					data[i].crd.x=(rand()%((WIDTH-100)/10)+5)*10;				
					data[i].crd.y=(rand()%((HEIGHT-100)/15)+5)*15;
				}
				else
				{
					if(Sec==4)
						do
						{
							data[i].crd.x=(rand()%((3*WIDTH/5)/10))*10+WIDTH/5;				
							data[i].crd.y=(rand()%((3*HEIGHT/5)/15))*15+HEIGHT/5;
						}while((data[i].crd.x>=WIDTH/2-50)&&(data[i].crd.x<=WIDTH/2+50)&&(data[i].crd.y>=HEIGHT/2-50)&&(data[i].crd.y<=HEIGHT/2+50));
					else
						do
						{
							data[i].crd.x=(rand()%((WIDTH-100)/10)+5)*10;				
							data[i].crd.y=(rand()%((HEIGHT-100)/15)+5)*15;
						}while((data[i].crd.x>47*WIDTH/140)&&(data[i].crd.x<47*WIDTH/140+230*WIDTH/700)&&(data[i].crd.y>19*HEIGHT/70)&&(data[i].crd.y<19*HEIGHT/70+331*HEIGHT/700));
				}
				ShowData(data[i].crd.x,data[i].crd.y,data[i].type);
				data[i].flag=1;
				data[i].settime.oldtime=data[i].settime.newtime;
			}
		}
	}
}

void ShowData(int x,int y,int t)
{
	x-=3,y-=7;
	switch(Lv)
	{
		case 1:	setcolor(RGB(53,223,49));break;
		case 2:	setcolor(RGB(159,184,255));break;
		case 3: setcolor(RGB(179,159,247));
	}
	
	switch(t)
	{
		case 0:		outtextxy(x,y,_T("0"));break;
		case 1:		outtextxy(x,y,_T("1"));
	}
	
}

void JudgeGetData()
{
	for(int i=0;i<DATANUM;i++)
		if((abs(dataworm.crd[0].x-data[i].crd.x)<=20)&&(abs(dataworm.crd[0].y-data[i].crd.y)<=20)&&(data[i].flag==1))
		{
			Getdatanum++;
			if(dataworm.node<DATAWORMLEN)	dataworm.node++;
			if(dataworm.hp<=HP_A)			dataworm.hp+=HPINCREASE;			//�������HP����ΪHP_A
			setcolor(BLACK);
			switch(data[i].type)
			{
				case 0:		outtextxy(data[i].crd.x-3,data[i].crd.y-7,_T("0"));break;
				case 1:		outtextxy(data[i].crd.x-3,data[i].crd.y-7,_T("1"));
			}
			data[i].flag=0;
		}
}

void JudgeCrash()
{
	for(int i=dataworm.node-1;i>0;i--)
	{
		if((dataworm.crd[0].x==dataworm.crd[i].x)&&(dataworm.crd[0].y==dataworm.crd[i].y))
		{
			dataworm.hp-=HPDECREASE;
			EndBatchDraw();
			for(int j=1500;j>=0;j--)							//������汻�ض�ʱ�Ľ��䶯��
			{
				setcolor(RGB(j*255/1500,j*255/1500,j*255/1500));
				for(int k=i;k<dataworm.node;k++)
					outtextxy(dataworm.crd[k].x-3,dataworm.crd[k].y-7,_T("0"));
			}	
			dataworm.node-=dataworm.node-i;
			ShowDataworm();
			BeginBatchDraw();
		}
	}
}

void ClearScreen()
{
	cleardevice();
	if((Lv!=3)||(Sec!=5))	putimage(0,0,&bkimg);
}

void DmgAni()
{
	EndBatchDraw();
	for(int i=500;i>=0;i--)							//��������ܵ��˺�ʱ�Ľ��䶯��
		{
			setcolor(RGB(i*255/500,0,0));
			for(int j=0;j<dataworm.node;j++)
				outtextxy(dataworm.crd[j].x-3,dataworm.crd[j].y-7,_T("0"));
		}	
	ShowDataworm();
	BeginBatchDraw();
}

void DieAni()
{
	EndBatchDraw();									//�����������ʱ�Ľ��䶯��
	setcolor(WHITE);
	for(int j=0;j<dataworm.node;j++)
	{
		outtextxy(dataworm.crd[j].x-3,dataworm.crd[j].y-7,_T("0"));
		Sleep(50);
	}
	BeginBatchDraw();
}

int hcf(int u,int v)								//�����Լ���ĺ���
{
	int t,r;
	if(v>u)
	{
		t=u;u=v;v=t;
	}
	while((r=u%v)!=0)
	{
		u=v;
		v=r;
	}
	return(v);
}

int lcd(int u,int v,int h)							//����С�������ĺ���
{
	return(u*v/h);
}