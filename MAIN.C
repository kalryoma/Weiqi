#include <bios.h>
#include <stdio.h>
#include <stdlib.h>
#include "time.c"
#include "Qipan.h"
#include "hanzi.c"
#include "key.c"

enum Action{
	NO = -1,NONE,YES,OK,XIAZI,TIZI,
	BLACKBT,WHITEBT,BLACKHUIQI,WHITEHUIQI,
	BLACKRENSHU,WHITERENSHU,EXIT,SAVE,
	OPEN,START_OVER,TIZIOVER,UIMODE
};

#define CLOCKX 12
#define CLOCKY 120
#define CLOCKLEN 75
char *savefilename = "save.txt";
char *temp = "temp.txt";
int clicked = 0;
enum Action LocStatus(int x,int y)
{
	int temp = MAX - 1 + 2*BIANJU;
	if (HasDialogue == 1)
	{
		if (DialogueMode == MB_OK&&getmaxx()/2 - SIZEX/2 <= x&& y >= getmaxy()/2 + WIDTH/4 && x <= getmaxx()/2 + SIZEX/2 && y <= getmaxy()/2 + WIDTH/4 + SIZEY)
			return OK;
		else if (DialogueMode == YES_NO && 
			x >= getmaxx()/2 - 3 * SIZEX/2 && y >= getmaxy()/2+WIDTH/4 && x <= getmaxx()/2 - SIZEX/2 && y <= getmaxy()/2+WIDTH/4+ SIZEY)
			return YES;
		else if (DialogueMode == YES_NO && 
			x >= getmaxx()/2 + SIZEX/2 && getmaxy()/2+WIDTH/4 && x <= getmaxx()/2+ 3*SIZEX/2 && y <= getmaxy()/2+WIDTH/4 + SIZEY)
			return NO;
		else return NONE;
	}
	else if ((Is_Start==1||Is_Tiziing==1)&&((x - START_X - (int)(BIANJU * LEN_OF_GEZI))%LEN_OF_GEZI <= 6 || (x - START_X - (int)(BIANJU * LEN_OF_GEZI))%LEN_OF_GEZI >= 16)
			&& ((y - START_Y - (int)(BIANJU * LEN_OF_GEZI))%LEN_OF_GEZI <= 6 || (y - START_Y - (int)(BIANJU * LEN_OF_GEZI))%LEN_OF_GEZI >= 16)
			&& x > START_X && y > START_Y
			&& y < START_Y + temp*LEN_OF_GEZI && x < START_X + temp*LEN_OF_GEZI)
	    {
			if (Is_Tiziing && hasqizi(x, y))
				return TIZI;
			else if (Is_Start == 1 && !hasqizi(x,y))
				return XIAZI;
			else return NONE;
		}
	else if (Is_Tiziing == 0)
	{
		if (Is_Start==1 && bywho == PBLACK && x > BUTTON_LOC - 10 && y > BUTTON_LOC && x < BUTTON_LOC + BUTTON_SIZEX*3/2 - 10 && y < BUTTON_LOC + BUTTON_SIZEY*3/2)
			return BLACKBT;
		else if (XialaBlack && x > BUTTON_LOC + BUTTON_SIZEX/4 - 10 && y > 100 
				&& x < BUTTON_LOC + BUTTON_SIZEX*5/4 - 10 && y < BUTTON_SIZEY + 100)
			return BLACKHUIQI;
		else if (XialaBlack && x > BUTTON_LOC + BUTTON_SIZEX/4 - 10 && y > 100+BUTTON_JIANJU 
				&& x < BUTTON_LOC + BUTTON_SIZEX*5/4 - 10 && y < 100 + BUTTON_SIZEY + BUTTON_JIANJU)
			return BLACKRENSHU;
			
		else if (Is_Start==1 && bywho == PWHITE && x > getmaxx()-BUTTON_LOC-BUTTON_SIZEX*3/2 + 10 && y > BUTTON_LOC && x < getmaxx() -BUTTON_LOC + 10 && y < BUTTON_LOC + BUTTON_SIZEY*3/2)
			return WHITEBT;
		else if (XialaWhite && x > getmaxx()-(BUTTON_LOC + BUTTON_SIZEX/4 - 10)-BUTTON_SIZEX && y > 100 
				&& getmaxx()-(BUTTON_LOC + BUTTON_SIZEX/4 - 10) && y < BUTTON_SIZEY + 100)
			return WHITEHUIQI;
		else if (XialaWhite && x >= getmaxx()-(BUTTON_LOC + BUTTON_SIZEX/4 - 10)-BUTTON_SIZEX && y > 100+BUTTON_JIANJU 
				&& x <= getmaxx()-(BUTTON_LOC + BUTTON_SIZEX/4 - 10) && y < 100 + BUTTON_SIZEY + BUTTON_JIANJU)
			return WHITERENSHU;
		else if (x >= 1 && y>= getmaxy() - 51 && x<= 71 && y<= getmaxy() -1 )
			return UIMODE;
		else if (x > getmaxx() - 50 && y > getmaxy() - 30)
			return EXIT;
		else if (x > getmaxx() - 105 && y > getmaxy() - 30 && x < getmaxx() - 55)
			return SAVE;
		else if (x > getmaxx() - 161 && y > getmaxy() - 30 && x < getmaxx() - 111)
			return OPEN;
		else if (x > getmaxx() - 216 && y > getmaxy() - 30 && x < getmaxx() - 161)
			return START_OVER;
		else return NONE;
	}else if (Is_Tiziing && x >= getmaxx()/2-BUTTON_SIZEX/2 && y >= getmaxy()-35
		&& x <= getmaxx()/2+BUTTON_SIZEX/2 && y<= getmaxy() - 5)
		return TIZIOVER;
	else 
		return NONE;
}

int MouseStatus()/*��갴�����*/
{
    int x,y;
    int press=0;
    int i,j,color;
	int ret;
    static int status=0;/*Ĭ�����û���ƶ�*/
    x=MouseX;
    y=MouseY;
	if (status == 1)
	{
    if ((ret = LocStatus(MouseX,MouseY)) != NONE)
			HandOn(MouseX,MouseY);
		else MouseOn(MouseX,MouseY);                         
	}
    {
        if(LeftPress()&&RightPress())
        press=1;
        else if(LeftPress()||kbhit())
            press=2;
        else if(RightPress())
            press=3;
        MouseGetXY();
        if(MouseX!=x||MouseY!=y||press!=0)
            status=1;
		else status = 0;
    }
	
	if (status){/*�ƶ������������ʾ���*/
		if (Mouse_Hand == 0)
		{
		for(i=0;i<16;i++)/*ԭλ�������ȥ*/
            for(j=0;j<16;j++)
			{
                if(mouse_draw[i][j]==3||mouse_draw[i][j]==4)
                    continue;
                color=getpixel(x+j,y+i);
                putpixel(x+j,y+i,color^color);
                putpixel(x+j,y+i,pixel_save[i][j]);
            }
		}
		else 
		{
		for(i=0;i<16;i++)/*ԭλ�������ȥ*/
            for(j=0;j<16;j++)
			{
                if(hand_draw[i][j]==3||hand_draw[i][j]==4)
                    continue;
                color=getpixel(x+j,y+i);
                putpixel(x+j,y+i,color^color);
                putpixel(x+j,y+i,pixel_save[i][j]);
            }
		}
		
    }

    if(press!=0)/*�а��������*/
        return press;
    return 0;/*ֻ�ƶ������*/
}
int main()
{
	int i,j, flag = 1;
	int second = 0;
	open_hzk();
	initMouse();
	initTime();
	initGraph();
	DrawbasicUI();
	DrawScore();
	DrawQipan();
	MouseOn(MouseX,MouseY);
	drawClock(second,CLOCKX,getmaxy()-CLOCKY,presecBlack);
	drawClock(second,getmaxx()-CLOCKX-CLOCKLEN,getmaxy()-CLOCKY,presecWhite);
	
	while(flag)
	{
		clicked = MouseStatus();

		switch(clicked)/*���������������*/
		{
			case 2:
			{	
				enum Action s;
				if (bioskey(1))
				{
					switch (bioskey(0))
					{
					case ENTER:
						if (HasDialogue == 1&&DialogueMode == MB_OK)
							s = OK;
						else if (HasDialogue == 1&&DialogueMode == YES_NO)
							s = YES;
						else if (Is_Start == 1)
							{
								if (bywho == PBLACK)
									s = BLACKBT;
								else s = WHITEBT;
							}
						else if (Is_Tiziing == 0)						
							s = START_OVER;
						else 
							s = TIZIOVER;
						break;
					case ESC:
						if (HasDialogue == 1&&DialogueMode == YES_NO)
							s = NO;
						else if (HasDialogue == 1&&DialogueMode == MB_OK)
							s = OK;
						else if (HasDialogue == 0)
						{
							if (Is_Start == 1&&Is_Tiziing == 0)
								s = START_OVER;
							else if(Is_Tiziing == 1)
								s = TIZIOVER;
							else s = EXIT;
						}
						else s = NONE;
						break;
					case TAB:
						s = UIMODE;
						break;
					case UPPERO-0x40:
							s = OPEN;
						break;
					case UPPERS-0x40:
							s = SAVE;
						break;
					case UPPERX-0x40:
							s = EXIT;
						break;
					case UPPERH-0x40:
						if (Is_Start)
						{
							s = bywho==PBLACK ? BLACKHUIQI:WHITEHUIQI;
						}
						else s = NONE;
						break;
					case UPPERR-0x40:
						if (Is_Start)
						{
							s = bywho==PBLACK ? BLACKRENSHU:WHITERENSHU;
						}
						else s = NONE;
						break;
					case UPPERN:case LOWERN:
						if (HasDialogue&&DialogueMode == YES_NO)
							s = NO;
						else s = NONE;
						break;
					case UPPERY:case LOWERY:
						if (HasDialogue&&DialogueMode == YES_NO)
							s = YES;
						else s = NONE;
						break;
					case F2:
						if (Is_Start == 0)
							s = START_OVER;
						else s = NONE;
						break;
					default:
						s = NONE;
					}
				}
				else 
					s = LocStatus(MouseX,MouseY);
				
				if (s != NO && s != BLACKHUIQI && s != BLACKRENSHU && XialaBlack == 1 && s != BLACKBT)
				{
					Shouhui(PBLACK);
				}
				if (s != NO && s != WHITERENSHU && s != WHITERENSHU && XialaWhite == 1 && s != WHITEBT)
				{
					Shouhui(PWHITE);
				}
				switch(s)/*�������λ�ý�������*/
				{
				case NO:
					switch(getDiagFun())
					{
					case DSAVEEXIT:
						{
							CancelDiag();
							setDiagFun(DEXIT);
							Dialogue("��ȷ��Ҫ�˳�Χ����",YES_NO);
						}
						break;
					case DSAVEOPEN:
						{
							CancelDiag();
							setDiagFun(DOPEN);
							Dialogue("ȷ��Ҫ����",YES_NO);
						}
						break;
					case DTIZI:
						{
							int x = getmaxx()-216,y = getmaxy()-31;
							CancelDiag();
							panduan();
							DrawScore();
							setDiagFun(DOVER);
							drawbutton(x, y, 50, 30, GREEN, WHITE, LIGHTGRAY,"��ʼ",9);
							Is_Start = 0;
							if (2*Black - 11 > 2*White)
							{
								Dialogue("����ʤ����",MB_OK);
								dissen(50,200,"ʤ����",RED);
							}
							else
							{
								Dialogue("����ʤ����",MB_OK);
								dissen(getmaxx()-50,200,"ʤ����",RED);
							}
						}
						break;
					default:
						CancelDiag();
						break;
					}
					break;
				case YES:
					switch(getDiagFun())
					{
					case DHUIQI:
						CancelDiag();
						huiqi();
						huiqi();
						Refresh(HUIQI);						
						break;
					case DRENSHU:
						{
							CancelDiag();
							panduan();
							DrawScore();
							Is_Start = 0;
							if (bywho == PBLACK)
							{
								Dialogue("����ʤ����",MB_OK);
								dissen(50,200,"ʤ����",RED);
							}
							if (bywho == PWHITE)
							{
								Dialogue("����ʤ����",MB_OK);
								dissen(getmaxx()-50,200,"ʤ����",RED);
							}
						}
						break;
					case DOVER:
						CancelDiag();
						setDiagFun(DTIZI);
						Is_Start = 0;
						Dialogue("��Ϸ��Ҫ��������������ȡ֮������ж���Ӯ���Ƿ�Ҫ��ȡ����",YES_NO);
						break;
					case DSAVE:
						CancelDiag();
						baocun(savefilename);
						break;
					case DEXIT:
						CancelDiag();
						flag = 0;
						break;
					case DOPEN:
						{
							CancelDiag();
							initOrder();
							initQipan();
							duru(savefilename);
							Refresh(DAKAI);
							bios_time = biostime(1,0L);
							drawClock(presecBlack[4]/CLK_TCK,CLOCKX,getmaxy()-CLOCKY,presecBlack);
							drawClock(presecWhite[4]/CLK_TCK,getmaxx()-CLOCKX-CLOCKLEN,getmaxy()-CLOCKY,presecWhite);
							if (Is_Start == 0)
							{
								int x = getmaxx()-216,y = getmaxy()-31;
								drawbutton(x, y, 50, 30, MAGENTA, WHITE, LIGHTGRAY,"����",9);
								Is_Start = 1;
							}
							Delay(0.3);
						}
						break;
					case DSAVEOPEN:
						{
							CancelDiag();
							baocun(temp);
							initOrder();
							initQipan();
							duru(savefilename);
							remove(savefilename);
							rename(temp,savefilename);
							Refresh(DAKAI);
							bios_time = biostime(1,0L);
							
							drawClock(presecBlack[4]/CLK_TCK,CLOCKX,getmaxy()-CLOCKY,presecBlack);
							drawClock(presecWhite[4]/CLK_TCK,getmaxx()-CLOCKX-CLOCKLEN,getmaxy()-CLOCKY,presecWhite);
							if (Is_Start == 0)
							{
								int x = getmaxx()-216,y = getmaxy()-31;
								drawbutton(x, y, 50, 30, MAGENTA, WHITE, LIGHTGRAY,"����",9);
								Is_Start = 1;
							}
							Delay(0.3);
						}
						break;
					case DSAVEEXIT:
						CancelDiag();
						baocun(savefilename);
						setDiagFun(DEXIT);
						Dialogue("��ȷ��Ҫ�˳�Χ����",YES_NO);
						break;
					case DTIZI:
						CancelDiag();
						JieshuButton();
						Dialogue("���ӽ����󰴡�������������",MB_OK);
						break;
					case DTIZIOVER:
						{
							int x = getmaxx()-216,y = getmaxy()-31;
							CancelDiag();
							panduan();
							DrawScore();
							DeleteJB();
							drawbutton(x, y, 50, 30, GREEN, WHITE, LIGHTGRAY,"��ʼ",9);
							Is_Start = 0;
							setDiagFun(DOVER);
							if (2*Black - 11 > 2*White)
							{
								Dialogue("����ʤ����",MB_OK);
								dissen(50,200,"ʤ����",RED);
							}
							else 
							{
								Dialogue("����ʤ����",MB_OK);
								dissen(getmaxx()-50,200,"ʤ����",RED);
							}
						}
						break;
					}
					break;
				case XIAZI:
					{
						int y = (MouseX - START_X)/LEN_OF_GEZI + 1;
						int x = (MouseY - START_Y)/LEN_OF_GEZI + 1;
						
						if (Qipan[x][y].status == EMPTY)
						{
							int ret = xiazi(bywho, x, y);
							switch(ret)/*�������ڵ�����*/
							{
							case -2:
								break;
							case -1:
								Dialogue("��Ϊ���ŵ㣡", MB_OK);
								break;
							case 0:
								DrawQizi(x, y, PBLACK + PWHITE - bywho);
								DrawScore();
								DrawCurPlayer();
								if (bywho==PWHITE)
									presecBlack[4] += bios_time;
								if (bywho==PBLACK)
									presecWhite[4] += bios_time;
								bios_time = biostime(1,0L);
								break;
							case 1:
								{
									int i;
									DrawQizi(x, y, PBLACK + PWHITE - bywho);
									DrawScore();
									DrawCurPlayer();
									for (i = 0; i!= tizinum; ++i)
									{
										DeleteQizi(tizidian[i]/(MAX+2),tizidian[i]%(MAX+2),bywho);
										DrawScore();
									}
										
									if (bywho==PWHITE)
										presecWhite[4] += bios_time;
									if (bywho==PBLACK)
										presecBlack[4] += bios_time;
									bios_time = biostime(1,0L);
								}
								break;
							}
						}
					}
					break;
				case UIMODE:
					UImode = 1 - UImode;
					DrawbasicUI();
					if (Is_Start)
					{
						int x = getmaxx()-216,y = getmaxy()-31;
						drawbutton(x, y, 50, 30, MAGENTA, WHITE, LIGHTGRAY, "����",9);
						DrawCurPlayer();
					}
					Refresh(HUIQI);
					DrawScore();
					if (Is_Start == 0)
						initTime();
					if (bywho==PWHITE)
					{
						second = getTime(presecWhite);
						drawClock(second,getmaxx()-CLOCKX-CLOCKLEN,getmaxy()-CLOCKY,presecWhite);
						if (presecBlack[3] == 0)
							presecBlack[3] = 1;
						drawClock(presecBlack[4]/CLK_TCK,CLOCKX,getmaxy()-CLOCKY,presecBlack);
					}
					else
					{
						second = getTime(presecBlack);
						if (presecWhite[3] == 0)
							presecWhite[3] = 1;
						drawClock(presecWhite[4]/CLK_TCK,getmaxx()-CLOCKX-CLOCKLEN,getmaxy()-CLOCKY,presecWhite);
						drawClock(second,CLOCKX,getmaxy()-CLOCKY,presecBlack);
					}
					Delay(0.2);
					break;
				case TIZI:
					{
						int y = (MouseX - START_X)/LEN_OF_GEZI + 1;
						int x = (MouseY - START_Y)/LEN_OF_GEZI + 1;
						if (Qipan[x][y].status!= EMPTY)
						{
							DeleteQizi(x, y, Qipan[x][y].status);
							tizi(x, y);
							DrawScore();
						}
					}
					break;
				case OK:
					if (getDiagFun() == DOVER)
					{
						CancelDiag();
					}
					else CancelDiag();
					break;
				case BLACKBT:
					if (XialaBlack == 0 && bywho == PBLACK)
						Xiala(PBLACK);
					else if (XialaBlack == 1)
						Shouhui(PBLACK);
					break;
				case WHITEBT:
					if (XialaWhite == 0 && bywho == PWHITE)
						Xiala(PWHITE);
					else if (XialaWhite == 1)
						Shouhui(PWHITE);
					break;
				case BLACKHUIQI:
					setDiagFun(DHUIQI);
					Dialogue("ȷ��Ҫ������",YES_NO);
					break;
				case WHITEHUIQI:
					setDiagFun(DHUIQI);
					Dialogue("ȷ��Ҫ������",YES_NO);
					break;
				case BLACKRENSHU:
					setDiagFun(DRENSHU);
					Dialogue("��ȷ��Ҫ������",YES_NO);
					break;
				case WHITERENSHU:
					setDiagFun(DRENSHU);
					Dialogue("��ȷ��Ҫ������",YES_NO);
					break;
				case EXIT:
					if (current != 0)
					{
						setDiagFun(DSAVEEXIT);
						Dialogue("��ȷ��Ҫ������",YES_NO);
					}
					else 
					{
						setDiagFun(DEXIT);
						Dialogue("��ȷ��Ҫ�˳�Χ����",YES_NO);
					}
					break;
				case OPEN:
					if (current != 0)
					{
						setDiagFun(DSAVEOPEN);
						Dialogue("����ֻḲ�ǵ�ǰ��֣�������Ҫ���浱ǰ�����",YES_NO);
					}
					else
					{
						setDiagFun(DOPEN);
						Dialogue("ȷ��Ҫ����",YES_NO);
					}
					break;
				case SAVE:
					if (current != 0)
					{
						setDiagFun(DSAVE);
						Dialogue("��ȷ��Ҫ������",YES_NO);
					}
					break;
				case START_OVER:
					{
						if (Is_Start == 0)
						{
							int x = getmaxx()-216,y = getmaxy()-31;
							Is_Start = 1;
							initOrder();
							initQipan();
							DrawScore();
							DrawCurPlayer();
							DrawQipan();
							initTime();
							second = getTime(presecBlack);
							drawClock(second,CLOCKX,getmaxy()-CLOCKY,presecBlack);
							drawClock(second,getmaxx()-CLOCKX-CLOCKLEN,getmaxy()-CLOCKY,presecWhite);
							drawbutton(x, y, 50, 30, MAGENTA, WHITE, LIGHTGRAY, "����",9);
							Dialogue("��ֿ�ʼ��",MB_OK);
						}
						else 
						{
							setDiagFun(DOVER);
							Dialogue("��ȷ��Ҫ������ǰ�����",YES_NO);
						}
					}
					break;
				case TIZIOVER:
					setDiagFun(DTIZIOVER);
					Dialogue("����������",YES_NO);
					break;
				}
			}
			break;
		case 3:
			jiance(bywho);
			tixingdian();
			break;
		}
		if (!flag) break;
		
		if (Is_Start)
		{
			if (bywho==PWHITE)
			{
				second = getTime(presecWhite);
				drawClock(second,getmaxx()-CLOCKX-CLOCKLEN,getmaxy()-CLOCKY,presecWhite);
			}
			else
			{
				second = getTime(presecBlack);
				drawClock(second,CLOCKX,getmaxy()-CLOCKY,presecBlack);
			}
		}
	}
	
	closegraph();
		
	return 0;
}