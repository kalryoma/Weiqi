#ifndef _H_QIPAN
#define _H_QIPAN
#include <graphics.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Dialogue.c"
#include "weiqi.h"
#include "hanzi.c"
#include "mouse.c"
#include "time.c"
#include "Mygraph.c"
#include "header.h"
int START_X = 103;
int START_Y = 25;

#define BIANJU (1.0/2)
#define LEN_OF_GEZI 22

#define HUIQI 11
#define DAKAI 12


#define BUTTON_SIZEX 55
#define BUTTON_SIZEY 30
#define BUTTON_LOC 20
#define BUTTON_JIANJU 40

#define SOURCEX 60
#define SOURCEY	80




void DrawScore();
void DrawButton();
void DrawbasicUI();
void initGraph();


void initGraph(){
	/* 要求自动检测 */
	int gdriver = DETECT, gmode, errorcode;
	char *temp[10];
	/* 初始化图形模式 */
	initgraph(&gdriver, &gmode, "");

	/* 读取初始化结果 */
	errorcode = graphresult();

	if (errorcode != grOk)  /* 发生错误 */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);             /* 具有错误代码的返回 */
	}
	settextjustify(1, 1);
	setbkcolor(BLACK);
	UImode = 0;
}

void DrawbasicUI()
{
	int x = BUTTON_LOC - 10;
	int shadowcolor = LIGHTGRAY;
	setfillstyle(SOLID_FILL,WHITE);
	bar(0,0,getmaxx(),getmaxy());
	drawframe(x,getmaxy()/2-HZLEN,BUTTON_SIZEX*3/2,BUTTON_SIZEX*3/2,0,0,WHITE,BLACK,shadowcolor,"");
	dissen(50,getmaxy()/2,"黑子",DARKGRAY);
	
	drawframe(getmaxx()-x-BUTTON_SIZEX*3/2,getmaxy()/2-HZLEN,BUTTON_SIZEX*3/2,BUTTON_SIZEX*3/2,0,0,WHITE,BLACK,shadowcolor,"");
	dissen(getmaxx()-50,getmaxy()/2,"白子",DARKGRAY);
	
	drawframe(x,getmaxy()/2+2*HZLEN+NUM_LEN,BUTTON_SIZEX*3/2,BUTTON_SIZEX*3/2,0,0,WHITE,BLACK,shadowcolor,"");
	dissen(50,getmaxy()/2+NUM_LEN+60,"已用时间",DARKGRAY);
	
	drawframe(getmaxx()-x-BUTTON_SIZEX*3/2,getmaxy()/2+2*HZLEN+NUM_LEN,BUTTON_SIZEX*3/2,BUTTON_SIZEX*3/2,0,0,WHITE,BLACK,shadowcolor,"");
	dissen(getmaxx()-50,getmaxy()/2+NUM_LEN+60,"已用时间",DARKGRAY);
	DrawButton();
}
void DrawQipan()
{
    int i,j;
	int temp = MAX - 1 + 2*BIANJU;
	setcolor(BROWN);
	if (UImode == 0)
	{
		START_X = 103;
		START_Y = 25;
		setfillstyle(SOLID_FILL,BROWN);
		bar3d(START_X,START_Y,START_X + LEN_OF_GEZI*temp,START_Y + LEN_OF_GEZI*temp,10,1);
		setfillstyle(SOLID_FILL,YELLOW);
		floodfill(START_X + 40,START_Y - 3,BROWN);
		floodfill(START_X+LEN_OF_GEZI*temp + 3,START_Y + 3,BROWN);
	}
	else
	{	
		setfillstyle(SOLID_FILL,YELLOW);
		START_X = 110;
		START_Y = 25;
		bar(START_X,START_Y,START_X + LEN_OF_GEZI*temp,START_Y + LEN_OF_GEZI*temp);
	}
	
   
	setcolor(BLACK);
	for (i = 0; i != MAX;++i)
	{
		line(START_X + LEN_OF_GEZI*BIANJU,
		START_Y + LEN_OF_GEZI*(i + BIANJU),
		START_X + LEN_OF_GEZI*(MAX - 1+ BIANJU),
		START_Y + LEN_OF_GEZI*(i + BIANJU));
		line(START_X + LEN_OF_GEZI*(i + BIANJU),
        START_Y + LEN_OF_GEZI*BIANJU,
        START_X + LEN_OF_GEZI*(i + BIANJU),
        START_Y + LEN_OF_GEZI*(MAX - 1+ BIANJU));
	}

	for (i=0;i!=3;++i)
	for (j=0;j!=3;++j)
	{
		setcolor(BLACK);
		setfillstyle(SOLID_FILL,BLACK);
		pieslice(START_X + LEN_OF_GEZI * (i*6 + BIANJU + 3), START_Y + LEN_OF_GEZI * (j*6 + BIANJU + 3), 0, 360, 2);
	}
}

void DrawCurPlayer()
{
	int y = 80;
	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	pieslice(BUTTON_LOC + BUTTON_SIZEX*3/4 - 10,y,0,360,4);
	pieslice(getmaxx()-(BUTTON_LOC + BUTTON_SIZEX*3/4 - 10),y,0,360,4);
	
	setcolor(RED);
	setfillstyle(SOLID_FILL,RED);
	if (bywho == PBLACK)
		pieslice(BUTTON_LOC + BUTTON_SIZEX*3/4 - 10,y,0,360,4);
	else 
		pieslice(getmaxx()-(BUTTON_LOC + BUTTON_SIZEX*3/4 - 10),y,0,360,4);
}

void DrawButton()
{
	int x,y;
	
	x = BUTTON_LOC;
	y = BUTTON_LOC;
	
	drawbutton(x-10, y, BUTTON_SIZEX*3/2, BUTTON_SIZEY*3/2, BROWN, BLACK, DARKGRAY,"黑棋", 4);

	x = getmaxx()-BUTTON_LOC-BUTTON_SIZEX*3/2;
	y = BUTTON_LOC;
	
	drawbutton(x+10, y, BUTTON_SIZEX*3/2, BUTTON_SIZEY*3/2, BROWN, WHITE, DARKGRAY,"白棋", 5);
	
	x = getmaxx()-51;
	y = getmaxy()-31;
	
	drawbutton(x, y, 50, 30, GREEN, WHITE, LIGHTGRAY, "退出", 0);

	x = getmaxx()-106;
	
	drawbutton(x, y, 50, 30, GREEN, WHITE, LIGHTGRAY,"保存", 1);

	x = getmaxx()-161;
	
	drawbutton(x, y, 50, 30, GREEN, WHITE, LIGHTGRAY,"打开", 2);
	
	x = getmaxx()-216;
	
	drawbutton(x, y, 50, 30, GREEN, WHITE, LIGHTGRAY,"开始", 3);
	
	x = 1;
	y = getmaxy() - 51;
	drawbutton(x, y, 70, 50, CYAN, WHITE, LIGHTGRAY,"变身", 8);
}

void JieshuButton()
{
	int x,y;
	x = getmaxx()/2-BUTTON_SIZEX;
	y = getmaxy()-31;
	drawbutton(x, y, 2*BUTTON_SIZEX, BUTTON_SIZEY, CYAN, WHITE, LIGHTGRAY,"提子结束", 5);
	Is_Tiziing = 1;
}
void DeleteJB()
{
	int x,y;
	deletebutton(5);
	Is_Tiziing = 0;
}

int XialaWhite,XialaBlack;
void Xiala(enum Status bywho)
{
	int x,y,color;
	switch(bywho)
	{
	case PBLACK:
		color = BLACK;
		x = BUTTON_LOC + BUTTON_SIZEX/4 - 10;
		XialaBlack = 1;
		break;
	case PWHITE:
		color = WHITE;
		x = getmaxx()-(BUTTON_LOC + BUTTON_SIZEX/4 - 10)-BUTTON_SIZEX ;
		XialaWhite = 1;
		break;
	}
	
	y = 100;
	Delay(0.2);
	drawbutton(x, y, BUTTON_SIZEX, BUTTON_SIZEY, BROWN, color,DARKGRAY, "悔棋", 6);
	Delay(0.2);
	y += BUTTON_JIANJU;
	
	drawbutton(x, y, BUTTON_SIZEX, BUTTON_SIZEY, BROWN, color,DARKGRAY, "认输", 7);
		
}

void Shouhui(enum Status bywho)
{
	if (bywho == PBLACK)
		XialaBlack = 0;
	else 
		XialaWhite = 0;
		
	Delay(0.1);
	deletebutton(7);
	Delay(0.2);
	deletebutton(6);
}




void drawqizibyloc(int x, int y, int color)
{
	int radius = LEN_OF_GEZI/2 - 2;
	setcolor(color);
	setfillstyle(SOLID_FILL,color);
	pieslice(x,y, 0, 360, radius);
	setcolor(DARKGRAY);
	circle(x,y, radius);
}

void drawqizi(int x,int y, int color)
{
	int desX = START_X + (BIANJU + y - 1)*LEN_OF_GEZI;
	int desY = START_Y + (BIANJU + x - 1)*LEN_OF_GEZI;
	drawqizibyloc(desX,desY,color);
}

void DrawQizi(int x,int y,enum Status bywho)
{
	int i;
	int interval = 20;
	int radius = LEN_OF_GEZI/2 - 2;
	int color;
	double centerX, centerY, dx, dy;
	int desX, desY;
	
	sound(494);
	
	if (bywho == PBLACK)
	{
		centerX = SOURCEX;
		color = BLACK;
	}
	if (bywho == PWHITE)
	{
		centerX = getmaxx() - SOURCEX;
		color = WHITE;
	}
		
	centerY = getmaxy() - SOURCEY;
	desX = START_X + (BIANJU + y - 1)*LEN_OF_GEZI;
	desY = START_Y + (BIANJU + x - 1)*LEN_OF_GEZI;
	dx = (desX - centerX)/interval;
	dy = (desY - centerY)/interval;
#ifndef TEST
	SaveImage((int)centerX - radius, (int)centerY - radius, (int)centerX + radius, (int)centerY + radius);
	
	drawqizibyloc((int)centerX,(int)centerY,color);
	
	for (i = 0; i!= interval; ++i)
	{
		Delay(0.01);
			
		BackImage();
		
		centerX += dx;
		centerY += dy;
		
		SaveImage((int)centerX - radius, (int)centerY - radius, (int)centerX + radius, (int)centerY + radius);
		
		drawqizibyloc((int)centerX,(int)centerY,color);
	}
		
	BackImage();		
#endif
	drawqizibyloc((int)desX,(int)desY,color);
	
	sound(392);
	Delay(0.1);
	sound(330);
	nosound();
}	

void deleteqizi(int x, int y)
{
	int centerX,centerY;
	centerX = START_X + LEN_OF_GEZI * (y - 1 +BIANJU);
	centerY = START_Y + LEN_OF_GEZI * (x - 1 +BIANJU);
	
	setfillstyle(SOLID_FILL,BROWN);
	bar(centerX - LEN_OF_GEZI/2, centerY - LEN_OF_GEZI/2, centerX + LEN_OF_GEZI/2, centerY + LEN_OF_GEZI/2);

    setcolor(BLACK);
    if (x == 1)
        line(centerX, centerY, centerX, centerY+LEN_OF_GEZI/2);
	else if (x == 19)
		line(centerX, centerY-LEN_OF_GEZI/2, centerX, centerY);
	else 
		line(centerX, centerY-LEN_OF_GEZI/2, centerX, centerY+LEN_OF_GEZI/2);
	
	if (y == 1)
		line(centerX, centerY, centerX+LEN_OF_GEZI/2, centerY);
	else if (y == 19)
		line(centerX-LEN_OF_GEZI/2, centerY, centerX, centerY);
	else 
		line(centerX-LEN_OF_GEZI/2, centerY, centerX+LEN_OF_GEZI/2, centerY);  

	if ((x - 4)% 6 == 0&&(y - 4)% 6 == 0)
	{
		setcolor(BLACK);
		setfillstyle(SOLID_FILL,BLACK);
		pieslice(START_X + LEN_OF_GEZI * (y + BIANJU - 1), START_Y + LEN_OF_GEZI * (x + BIANJU - 1), 0, 360, 2);
	}
}


void DeleteQizi(int x, int y, enum Status by_who)
{
    int centerX,centerY;
	int i;
	int interval = 10;
	int color;
	int desX,desY;
	int dx, dy;
	int radius = LEN_OF_GEZI/2 -2;
	sound(440);
	centerX = START_X + LEN_OF_GEZI * (y - 1 +BIANJU);
	centerY = START_Y + LEN_OF_GEZI * (x - 1 +BIANJU);
	desX = by_who == PBLACK? SOURCEX:(getmaxx()-SOURCEX);
	desY = getmaxy() - SOURCEY;
	dx = (desX - centerX)/interval;
	dy = (desY - centerY)/interval;

	color = by_who==PBLACK ? BLACK:WHITE;
	deleteqizi(x,y);
#ifndef TEST	
	SaveImage((int)centerX - radius, (int)centerY - radius, (int)centerX + radius, (int)centerY + radius);
		
	drawqizibyloc((int)centerX,(int)centerY,color);
	
	for (i = 0; i!= interval; ++i)
	{
		Delay(0.01);
		BackImage();
		centerX += dx;
		centerY += dy;
		
		SaveImage((int)centerX - radius, (int)centerY - radius, (int)centerX + radius, (int)centerY + radius);
		drawqizibyloc((int)centerX,(int)centerY,color);
	}
#endif
	nosound();
	BackImage();
}

void Refresh(int mode)
{
	int i,j;
	int color;
	DrawQipan();
	if (mode == HUIQI)
	{
		for (i=1;i<=MAX;++i)
		for (j=1;j<=MAX;++j)
		if (Qipan[i][j].status != EMPTY)
		{
			color = Qipan[i][j].status==PBLACK ? BLACK:WHITE;
			drawqizi(i, j, color);
		}
	}
	else if (mode == DAKAI)
	{
		int steps=current;
		if (current==0) return;
		current=0;
		bywho = PBLACK;
		initQipan();
		for (i=0;i!=steps;++i)
		{
			int ret;
			ret = xiazi(Order[i].bywho,Order[i].locx,Order[i].locy);
			
			DrawQizi(Order[i].locx, Order[i].locy, PBLACK + PWHITE - bywho);
			DrawScore();
			DrawCurPlayer();
			
			if (ret == 1)	
			for (j = 0; j!= tizinum; ++j)
			{
				DeleteQizi(tizidian[j]/(MAX+2),tizidian[j]%(MAX+2),bywho);
				DrawScore();
			}
				
		}
	}
}

void tixingdian()
{
	int i,j;
	int x,y;
	double desX, desY;
	for (j = 0; j != 2; ++j)
	{
		for (i = 0; i !=  tizinum; ++i)
		{
			x = tizidian[i]/(MAX + 2);
			y = tizidian[i]%(MAX + 2);
			desX = START_X + (BIANJU + y - 1)*LEN_OF_GEZI;
			desY = START_Y + (BIANJU + x - 1)*LEN_OF_GEZI;
			setcolor(YELLOW);
			setfillstyle(SOLID_FILL,YELLOW);
			pieslice((int)desX,(int)desY, 0, 360, 3);
		}
		Delay(0.5);
		for (i = 0; i !=  tizinum; ++i)
		{
			x = tizidian[i]/(MAX + 2);
			y = tizidian[i]%(MAX + 2);
			deleteqizi(x, y);
		}
	}
}


void DrawScore()
{
	int x,y;
	
	y = getmaxy()/2 +40;
	x = 2*NUM_WID;
	
	setfillstyle(SOLID_FILL,WHITE);
	bar(x - (int)(3*NUM_WID/2.0),y - NUM_LEN/2,x+(int)(3*NUM_WID/2.0),y+NUM_LEN/2);
	
	DrawNumber(Black, x, y);
	
	setfillstyle(SOLID_FILL,WHITE);
	bar(getmaxx()-x-(int)(3*NUM_WID/2.0),y - NUM_LEN/2,getmaxx()-x+(int)(3*NUM_WID/2.0),y+NUM_LEN/2);
	
	DrawNumber(White, getmaxx()-x, y);
	
}
int hasqizi(int mousex,int mousey)
{
	int x = (mousey - START_Y) / LEN_OF_GEZI + 1;
	int y = (mousex - START_X) / LEN_OF_GEZI + 1;
	if (Qipan[x][y].status == EMPTY)
		return 0;
	else return 1;
}
#endif