#ifndef _H_HANZI
#define _H_HANZI
#include <stdio.h>
#include <string.h>
#include <graphics.h>

#define HZLEN 20

FILE *hzk_p;
void open_hzk(void);
void get_hz(char incode[],char bytes[]);
void dishz(int x,int y,char cade[],int color);

void open_hzk()
{

	hzk_p=fopen("hzk16","rb");
	if (!hzk_p){
		printf("The file HZK16 not exist! Enter to system\n");
	    getch();
		closegraph();
		exit(1);
	}
}
void close_hzk()
{
	fclose(hzk_p);
}
void get_hz(char incode[],char bytes[])
{
	unsigned char qh,wh;
	unsigned long offset;
	qh=incode[0]-0xa0;				/*得到区号*/
	wh=incode[1]-0xa0;			/*得到位号*/
	offset=(94*(qh-1)+(wh-1))*32L;	/*得到偏移位置*/
	fseek(hzk_p,offset,SEEK_SET);	/*移文件指针到要读取的汉字点阵处*/
	fread(bytes,32,1,hzk_p);			/*读取32字节的汉字点阵信息*/
}

void dishz(int x0,int y0,char code[],int color)
{
	unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
        /*屏蔽点阵每行各位的数组*/
	int i,j,x,y,pos;
	char mat[32];
	get_hz(code,mat);
	y=y0;
	for (i=0;i<16;++i)
	{
		x=x0;
		pos=2*i;
		for(j=0;j<16;++j)
		{
                 /*屏蔽出汉字点阵的一个位，即一个点是1则显示，否则不显示该点*/
			if ((mask[j%8]&mat[pos+j/8])!=NULL)
				putpixel(x,y,color);
			++x;
		}
		++y;
	}
}


void dissen(int x, int y, char sen[], int color)
{
	int len = strlen(sen);
	char *s = sen;
	int num;
	int x0;
	int xx;
	
	y = y - HZLEN*(len/20+1)/2+2;
	
	while (*s != NULL)
	{
		num = len/2 > 11 ? 5:(int)(len/4.0);
		x0 = x - HZLEN*num + 2;
		xx = 0;
		while (xx < 200&& *s != NULL)
		{
			dishz(xx+x0,y,s,color);
			xx += 20;
			s += 2;
			len -= 2;
		}
		y += 20;
	}
}
#endif