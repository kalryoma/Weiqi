#ifndef _H_WEIQI
#define _H_WEIQI
#include <string.h>
#include <stdio.h>
#include "header.h"

#define MAX 19
#define MAXQIZI 500
enum Status
{
	EMPTY,PBLACK,PWHITE,BORDER
}bywho;

struct qizi
{
	enum Status status;
	int order;
}Qipan[MAX+2][MAX+2];

struct qiziList
{
	enum Status bywho;
	int locx;
	int locy;
}Order[MAXQIZI];

int current;
int tizidian[MAX*MAX];
int tizinum;
int Black, White;

int d[4][2] = {{0,-1},{-1,0},{0,1},{1,0}};
/*	棋局开始前初始化棋盘 */
void initQipan()
{
	int i,j;
	for (i=0;i<=MAX+1;++i)
	{
		if (i==0||i==MAX+1)
		{
			for (j=0;j<=MAX+1;++j)
			{
				Qipan[i][j].order=0;
				Qipan[i][j].status=BORDER;
			}	
			continue;
		}
		for (j=0;j<=MAX+1;++j)
		{
			if (j==0||j==MAX+1) 
			{
				Qipan[i][j].order=0;
				Qipan[i][j].status=BORDER;
				continue;
			}
			Qipan[i][j].order=0;
			Qipan[i][j].status=EMPTY;
		}
	}
	White = 0;
	Black = 0;
}
void initOrder()
{
	int i;
	for (i=0;i!=MAXQIZI;++i)
	{
		Order[i].bywho=EMPTY;
		Order[i].locx=-1;
		Order[i].locy=-1;
	}
	current=0;
	bywho = PBLACK;
}

/*判断x,y处是不是禁着点*/
int is_jinzhuodian(enum Status by_who,int x,int y)
{
	int i,xx,yy;
	enum Status cur;
	Qipan[x][y].status=by_who;
	for (i=0;i!=4;++i)
	{
		xx=x+d[i][0];
		yy=y+d[i][1];
		cur=Qipan[xx][yy].status;
		if (by_who==cur&&!is_huoqi(xx,yy))
		{
			Qipan[x][y].status=EMPTY;
			return 1;
		}
	}
	for (i=0;i!=4;++i)
	{
		xx=x+d[i][0];
		yy=y+d[i][1];
		cur=Qipan[xx][yy].status;
		if(by_who==cur||cur==EMPTY)
		{
			Qipan[x][y].status=EMPTY;
			return 0;
		}
	}
	
	for (i=0;i!=4;++i)
	{
		xx=x+d[i][0];
		yy=y+d[i][1];
		cur=Qipan[xx][yy].status;
		if(by_who!=cur&&!is_huoqi(xx,yy))
		{
			Qipan[x][y].status=EMPTY;
			return 0;
		}
	}
	Qipan[x][y].status=EMPTY;
	return 1;
}

/*判断坐标为x,y的子是不是活棋*/
int is_huoqi(int x,int y)
{
	enum Status cur = Qipan[x][y].status;
	int flag[MAX+2][MAX+2];
	int queue[(MAX+2)*(MAX+2)],head, tail;
	int row=MAX+2;
	int cx,cy;
	int i;

	memset(flag,0,(MAX+2)*(MAX+2)*sizeof(int));
	
	head=tail=0;
	queue[tail++]=x*row+y;
	flag[x][y]=1;
	
	while (head!=tail)
	{
		cx=queue[head]/row;
		cy=queue[head]%row;
		head++;
		for (i=0;i!=4;++i)
		{
			if (!flag[cx+d[i][0]][cy+d[i][1]]&&Qipan[cx+d[i][0]][cy+d[i][1]].status==cur)
			{
				queue[tail++]=(cx+d[i][0])*row+cy+d[i][1];
				flag[cx+d[i][0]][cy+d[i][1]]=1;
			}
			else if(Qipan[cx+d[i][0]][cy+d[i][1]].status==EMPTY)
				return 1;
		}
	}

	return 0;
}

/*如果x,y所在处为死棋则吃掉*/
void chizi(int x,int y)
{
	enum Status cur = Qipan[x][y].status;
	int queue[(MAX+2)*(MAX+2)],head, tail;
	int row=MAX+2;
	int cx,cy;
	int i;

	head=tail=0;
	queue[tail++]=x*row+y;
	tizidian[tizinum++] = x*row + y;
	while (head!=tail)
	{
		cx=queue[head]/row;
		cy=queue[head]%row;
		cur == PBLACK? Black--: White--;
		Qipan[cx][cy].status=EMPTY;
		
		head++;
		for (i=0;i!=4;++i)
		{
			if (Qipan[cx+d[i][0]][cy+d[i][1]].status==cur)
			{
				queue[tail++]=(cx+d[i][0])*row+cy+d[i][1];
				tizidian[tizinum++] = (cx+d[i][0])*row+cy+d[i][1];
			}
		}
	}
}

/*用户下子之后的操作
  如果所下点为禁着点则返回-1
  如果已经有棋子则返回-2
  如果下完之后有死棋则返回1
  否则返回0*/
int xiazi(enum Status by_who,int locx,int locy)
{
	enum Status cur;
	int i;
	int xx,yy;
	int flag = 0;
	if (Qipan[locx][locy].status!=EMPTY)return -2;
	if (is_jinzhuodian(by_who,locx,locy)) return -1;
	Order[current].bywho=by_who;
	Order[current].locx=locx;
	Order[current].locy=locy;
	Qipan[locx][locy].order=current;
	Qipan[locx][locy].status=by_who;
	current++;
	tizinum = 0;
	for (i=0;i!=4;++i)
	{
		xx=locx+d[i][0];
		yy=locy+d[i][1];
		cur=Qipan[xx][yy].status;
		if (by_who==cur||cur==EMPTY||cur==BORDER) continue;
		if (is_huoqi(xx,yy)) continue;
			chizi(xx,yy);
			flag = 1;
	}
	bywho = PBLACK + PWHITE - bywho;
	by_who == PBLACK? ++Black: ++White;
	return flag;
}

/*悔棋，通过选手们下的步骤，推出上一步的情况*/
void huiqi()
{
	int i;
	int steps=current-1;
	if (current==0) return;
	current=0;
	bywho = PBLACK;
	initQipan();
	for (i=0;i!=steps;++i)
	{
		xiazi(Order[i].bywho,Order[i].locx,Order[i].locy);
	}
}

/*保存，也只保存选手下的步骤和已下的时间*/
void baocun(char *name)
{
	FILE *fout;
	int i;
	fout = fopen(name,"w");
	fprintf(fout,"%d\n%d\n",presecBlack[4],presecWhite[4]);
	for (i=0;i!=current;++i)
	{
		fprintf(fout,"%d %d %d\n",Order[i].bywho,Order[i].locx,Order[i].locy);
	}
	fclose(fout);
}

/*读入*/
void duru(char *name)
{
	int ret;
	FILE *fin;
	current=0;
	bywho = PBLACK;
	fin = fopen(name,"r");
	fscanf(fin,"%d %d",&presecBlack[4],&presecWhite[4]);
	if (fin != NULL)
	while (!feof(fin))
	{
		if (ret = fscanf(fin,"%d%d%d",&Order[current].bywho,&Order[current].locx,&Order[current].locy));
		if (ret != -1)
			xiazi(Order[current].bywho,Order[current].locx,Order[current].locy);
		/*current++;*/
	}
}

/*玩家提子*/
void tizi(int x,int y)
{
	Qipan[x][y].status == PBLACK? Black--:White--;
	Qipan[x][y].status=EMPTY;
}

/*计算胜负*/
void panduan()
{
	enum Status cur;
	enum Owner
	{
		OEMPTY,OBLACK,OWHITE,OBOTH
	}owner;
	int flag[MAX+2][MAX+2];
	int queue[(MAX+2)*(MAX+2)],head,tail;
	int i,j,k;
	float b=0,w=0;
	int cx,cy,xx,yy;
	memset(flag,0,(MAX+2)*(MAX+2)*sizeof(int));
	for (i=1;i!=MAX+1;++i)
	for (j=1;j!=MAX+1;++j)
	{
		if (!flag[i][j])flag[i][j]=1;
		else continue;
		switch (Qipan[i][j].status)
		{
		case EMPTY:
			{
				owner=OEMPTY;
				head=tail=0;
				queue[tail++]=i*(MAX+2)+j;
				while (head!=tail)
				{
					cx=queue[head]/(MAX+2);
					cy=queue[head]%(MAX+2);
					head++;
					for (k=0;k!=4;++k)
					{
						xx=cx+d[k][0];
						yy=cy+d[k][1];
						cur=Qipan[xx][yy].status;
						switch (cur)
						{
						case EMPTY:
							if (!flag[xx][yy])
							{
								queue[tail++]=xx*(MAX+2)+yy;
								flag[xx][yy]=1;
							}
							break;
						case PBLACK:
							if (owner==OEMPTY)
								owner=OBLACK;
							else if (owner==OWHITE)
								owner=OBOTH;
							break;
						case PWHITE:
							if (owner==OEMPTY)
								owner=OWHITE;
							else if (owner==OBLACK)
								owner=OBOTH;
							break;
						default:
							break;
						}
					}
				}
				switch (owner)
				{
				case OBLACK:
					b+=tail;
					break;
				case OWHITE:
					w+=tail;
					break;
				case OEMPTY:case OBOTH:
					b+=tail/2.0;
					w+=tail/2.0;
					break;
				default:
					break;
				}
			}
			break;
		case PBLACK:
			b++;
			break;
		case PWHITE:
			w++;
			break;
		default:
			break;
		}
	}
	Black=b;
	White=w;
}

/*检测整个棋盘中下子可以提掉对方棋子的点*/
void jiance(enum Status by_who)
{
	enum Status cur;
	int i,j,k;
	int xx,yy;
	memset(tizidian,0,sizeof(int)*MAX*MAX);
	tizinum=0;
	for (i=1;i<=MAX;++i)
	for (j=1;j<=MAX;++j)
	if (Qipan[i][j].status==EMPTY)
	{
		Qipan[i][j].status=by_who;
		for (k=0;k!=4;++k)
		{
			xx=i+d[k][0];
			yy=j+d[k][1];
			cur=Qipan[xx][yy].status;
			if (cur!=EMPTY&&cur!=BORDER&&cur!=by_who&&!is_huoqi(xx,yy))
				tizidian[tizinum++]=i*(MAX+2)+j;
		}
		Qipan[i][j].status=EMPTY;
	}
}

#endif 