#ifndef _H_MYGRAPH
#define _H_MYGRAPH

#include <graphics.h>
#include <stdlib.h>
#include "hanzi.c"
#include "time.c"
#include "header.h"

#define NUM_MARGIN 3
#define NUM_BIANJU 3

#define NUM_WID 24
#define NUM_LEN 34
void DrawDigit(int num, int strx, int stry, int endx, int endy)
{
	int midy;
	midy = (stry + endy)/2;
	setfillstyle(SOLID_FILL,WHITE);
  	bar(strx,stry,endx,endy);
	setcolor(BLACK);
	rectangle(strx+NUM_MARGIN,stry+NUM_MARGIN,endx-NUM_MARGIN,endy-NUM_MARGIN);
	rectangle(strx+NUM_MARGIN+NUM_BIANJU-1,stry+NUM_MARGIN+NUM_BIANJU-1,endx-NUM_MARGIN-NUM_BIANJU+1,midy-NUM_BIANJU/2);
	rectangle(strx+NUM_MARGIN+NUM_BIANJU-1,midy+NUM_BIANJU/2,endx-NUM_MARGIN-NUM_BIANJU+1,endy-NUM_MARGIN-NUM_BIANJU+1);
	
	
	setfillstyle(SOLID_FILL,BLACK);
  	floodfill(strx+NUM_BIANJU+1,stry+NUM_BIANJU+1,BLACK);
	setfillstyle(SOLID_FILL,WHITE);
	if (num==0)
	{
  		bar(strx+NUM_MARGIN+NUM_BIANJU,midy-NUM_BIANJU/2,endx-NUM_BIANJU-NUM_MARGIN,midy+NUM_BIANJU/2+1);
	}
	if (num==1)
	{
  		bar(strx,stry,endx-NUM_BIANJU-NUM_MARGIN,endy-NUM_MARGIN);
	}
	if (num==2)
	{
		bar(strx+NUM_MARGIN,
		stry+NUM_MARGIN+NUM_BIANJU,
		strx+NUM_MARGIN+NUM_BIANJU,
		midy-NUM_BIANJU/2-1);
		bar(endx-NUM_MARGIN-NUM_BIANJU,
		midy+NUM_BIANJU/2+1,
		endx-NUM_MARGIN,
		endy-NUM_MARGIN-NUM_BIANJU);
	}
	if (num==3)
	{
		bar(strx+NUM_MARGIN,
		stry+NUM_MARGIN+NUM_BIANJU,
		strx+NUM_MARGIN+NUM_BIANJU,
		midy-NUM_BIANJU/2-1);
  		bar(strx+NUM_MARGIN,
		midy+NUM_BIANJU/2+1,
		strx+NUM_MARGIN+NUM_BIANJU,
		endy-NUM_MARGIN-NUM_BIANJU);
	}
	if (num==4)
	{
		bar(strx+NUM_MARGIN+NUM_BIANJU,stry+NUM_MARGIN,endx-NUM_MARGIN-NUM_BIANJU,stry+NUM_MARGIN+NUM_BIANJU);
  		bar(strx+NUM_MARGIN,midy+NUM_BIANJU/2+1,endx-NUM_MARGIN-NUM_BIANJU,endy-NUM_MARGIN);
	}
	if (num==5)
	{
		bar(endx-NUM_MARGIN-NUM_BIANJU,
		stry+NUM_MARGIN+NUM_BIANJU,
		endx-NUM_MARGIN,
		midy-NUM_BIANJU/2-1);
  		bar(strx+NUM_MARGIN,
		midy+NUM_BIANJU/2+1,
		strx+NUM_MARGIN+NUM_BIANJU,
		endy-NUM_MARGIN-NUM_BIANJU);
	}
	if (num==6)
	{
		bar(endx-NUM_MARGIN-NUM_BIANJU,
		stry+NUM_MARGIN+NUM_BIANJU,
		endx-NUM_MARGIN,
		midy-NUM_BIANJU/2-1);
	}
	if (num==7)
	{
		bar(strx+NUM_MARGIN,stry+NUM_MARGIN+NUM_BIANJU,endx-NUM_MARGIN-NUM_BIANJU,endy-NUM_MARGIN);
	}
	if (num==9)
	{
		bar(strx+NUM_MARGIN,
		midy+NUM_BIANJU/2+1,
		strx+NUM_MARGIN+NUM_BIANJU,
		endy-NUM_MARGIN-NUM_BIANJU);
	}
}

void DrawNumber(int number, int x, int y)
{
	int n = number;
	int len = 0;
	float startx = 0,xx;
	while (n>0)
	{
		len++;
		n /= 10;
	}
	n = number;
	if (number == 0)
		len = 1;
	startx = x + NUM_WID*len/2.0 - NUM_WID;
	xx = startx;
	
	do
	{	
		DrawDigit(n%10, (int)xx, y-NUM_LEN/2, (int)xx+NUM_WID, y+NUM_LEN/2);
		n /= 10;
		xx -= NUM_WID;
	}while (n>0);
}


struct button{
	int exist;
	int x;
	int y;
	int sizex;
	int sizey;
	int shadow;
}buttons[12];

void drawbutton(int x, int y, int sizex ,int sizey, int bgcolor, int textcolor, int shadowcolor, char *content, int ID)
{
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,bgcolor);
	if (UImode == 0)
	{
		bar3d(x, y, x+sizex, y+sizey,sizex/20,1);
		buttons[ID].shadow = sizex/20;
		setfillstyle(SOLID_FILL,shadowcolor);
		floodfill(x+4, y-1, BLACK);
		floodfill(x+sizex+1,y+3,BLACK);
	}
	else 
	{
		bar(x, y, x+sizex, y+sizey);
		buttons[ID].shadow = 1;
	}
	
	dissen(x+sizex/2, y+sizey/2,content,textcolor);
	buttons[ID].exist = 1;
	buttons[ID].x = x;
	buttons[ID].y = y;
	buttons[ID].sizex = sizex;
	buttons[ID].sizey = sizey;
}

void deletebutton(int ID)
{
	struct button cur = buttons[ID];
	if (cur.exist != 1)
		return;
	setfillstyle(SOLID_FILL,WHITE);
	bar(cur.x, cur.y-buttons[ID].shadow+1, cur.x+cur.sizex+buttons[ID].shadow, cur.y+cur.sizey);
	cur.exist = 0;
	/*Delay(0.1);*/
}

void drawframe(int x, int y, int sizex ,int sizey, int dx, int dy, int bgcolor, int textcolor,int shadowcolor,char *content)
{
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,bgcolor);
	if (UImode == 0)
	{
		bar3d(x, y, x+sizex, y+sizey,3,1);
		setfillstyle(SOLID_FILL,shadowcolor);
		floodfill(x+4, y-1, BLACK);
		floodfill(x+sizex+1,y+3,BLACK);
	}
	else 
		bar(x, y, x+sizex, y+sizey);
	dissen(x+dx, y+dy,content,textcolor);	
}

void *_BUFFER;
int _LEFT;
int _TOP;
int _RIGHT;
int _BOTTOM;
void SaveImage(int left, int top, int right, int bottom)
{
	int size;
	_LEFT = left;
	_TOP = top;
	_RIGHT = right;
	_BOTTOM = bottom;
	size = imagesize(_LEFT, _TOP, _RIGHT, _BOTTOM);
	_BUFFER = malloc(size);
	getimage(_LEFT, _TOP, _RIGHT, _BOTTOM,_BUFFER);
}

void BackImage()
{
	putimage(_LEFT, _TOP,_BUFFER, COPY_PUT);
	free(_BUFFER);
}
#endif