#ifndef _H_TIME
#define _H_TIME
#include <dos.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <graphics.h>
#include "header.h"
void Delay(double time);
#include "Mygraph.c"

int bios_time;

void Delay(double time)
{
	double t0 = biostime(0,0L)/CLK_TCK;
#ifndef TEST
	while (biostime(0,0L)/CLK_TCK - t0 < time);
#endif
}

void initTime()
{
	memset(presecBlack,0,sizeof(presecBlack)*5);
	memset(presecWhite,0,sizeof(presecWhite)*5);
	presecBlack[3]=1;
	presecWhite[3]=1;
	bios_time = biostime(1,0L);/*计时控制器*/
}

int getTime(int *presec)
{
	bios_time = biostime(0,0L);
	return(int)((bios_time+presec[4])/CLK_TCK);
}

void drawClock(int sec, int strx, int stry, int *presec)
{
	int second,minute;
	int sec1,sec2,min1,min2;

	second = sec%60;
	minute = sec/60;
	sec1 = second%10;
	sec2 = second/10;
	min1 = minute%10;
	min2 = minute/10;

	if (sec1!=presec[3])/*秒数有变化*/
	{
		DrawDigit(min2,strx,stry,strx+17,stry+25);
		DrawDigit(min1,strx+17,stry,strx+34,stry+25);
		setfillstyle(SOLID_FILL,WHITE);
  		bar(strx+34,stry,strx+39,stry+25);
		setcolor(BLACK);
		rectangle(strx+34,stry+5,strx+39,stry+10);
		setfillstyle(SOLID_FILL,BLACK);
	  	floodfill(strx+34+1,stry+5+1,BLACK);
		setcolor(BLACK);
		rectangle(strx+34,stry+15,strx+39,stry+20);
		setfillstyle(SOLID_FILL,BLACK);
	  	floodfill(strx+34+1,stry+15+1,BLACK);
		DrawDigit(sec2,strx+39,stry,strx+56,stry+25);
		DrawDigit(sec1,strx+56,stry,strx+73,stry+25);

		presec[0] = min2;
		presec[1] = min1;
		presec[2] = sec2;
		presec[3] = sec1;
	}
}

#endif