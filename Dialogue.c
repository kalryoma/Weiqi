#ifndef _H_DIAG
#define _H_DIAG

#include <graphics.h>

#include "hanzi.c"
#include "mouse.c"
#include "time.c"
#include "mygraph.c"
#define LENGTH 240
#define WIDTH 160

#define SIZEX 50
#define SIZEY 30

#define MB_OK 0
#define YES_NO 1

enum DiagFun{
	DNONE,DSAVE,DSAVEOPEN,DSAVEEXIT,DOVER,DHUIQI,DRENSHU,DEXIT,DOPEN,DTIZI,DTIZIOVER
}diagfun;

int DialogueMode = 0;
int HasDialogue = 0;
void *buffer;

enum DiagFun getDiagFun()
{
	return diagfun;
}

void setDiagFun(enum DiagFun fun)
{
	diagfun = fun;
}

int Dialogue(char *content, int mode)
{
	int size = imagesize(getmaxx()/2-LENGTH/2,getmaxy()/2-WIDTH/2-2,getmaxx()/2+LENGTH/2+3,getmaxy()/2+WIDTH/2);
	buffer = malloc(size);
	getimage(getmaxx()/2-LENGTH/2,getmaxy()/2-WIDTH/2-2,getmaxx()/2+LENGTH/2+3,getmaxy()/2+WIDTH/2, buffer);
	HasDialogue = 1;
	if (UImode == 0)
		setfillstyle(SOLID_FILL,BROWN);
	else 
		setfillstyle(SOLID_FILL,YELLOW);
	bar(getmaxx()/2-LENGTH/2,getmaxy()/2-WIDTH/2-2,getmaxx()/2+LENGTH/2+3,getmaxy()/2+WIDTH/2);
	
	DialogueMode = mode;
	drawframe(getmaxx()/2-LENGTH/2,getmaxy()/2-WIDTH/2,LENGTH,WIDTH,
		LENGTH/2,2*WIDTH/5,LIGHTGRAY,BLACK,DARKGRAY,content);
	switch(mode)
	{
	case MB_OK:	
		drawbutton(getmaxx()/2 - SIZEX/2,getmaxy()/2 + WIDTH*1/4,SIZEX,SIZEY,WHITE,BLACK,DARKGRAY,"确定",10);
		break;
	case YES_NO:
		drawbutton(getmaxx()/2 - 3 * SIZEX/2, getmaxy()/2+WIDTH/4,SIZEX,SIZEY,WHITE,BLACK,DARKGRAY,"确定",10);
		drawbutton(getmaxx()/2 + SIZEX/2, getmaxy()/2+WIDTH/4,SIZEX,SIZEY,WHITE,BLACK,DARKGRAY,"取消",11);
		break;
	}
}

int CancelDiag()
{
	HasDialogue = 0;
	setDiagFun(DNONE);
	putimage(getmaxx()/2-LENGTH/2,getmaxy()/2-WIDTH/2-2,buffer , COPY_PUT);
	free(buffer);
	Delay(0.4);
}

#endif