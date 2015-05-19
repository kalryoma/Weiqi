#ifndef _H_MOUSE
#define _H_MOUSE
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>

int MouseExist;      /*鼠标安装状态*/
int MouseButton;     /*鼠标按键状态*/
int MouseX;          /*鼠标当前水平方向坐标*/
int MouseY;          /*鼠标当前垂直方向坐标*/

int Mouse_Hand;

/*Winxp下INT 33H中断不支持鼠标的显示和关闭，所以要自己编写这两个函数*/

int up[16][16], down[16][16],mouse_draw[16][16],pixel_save[16][16],hand_draw[16][16];

void MouseMath()/*鼠标的形状设置*/
{
    int i,j,jj,k;

/* 箭头形状*/

    long UpNum[16]={
        0x3fff,0x1fff,0x0fff,0x07ff,
        0x03ff,0x01ff,0x00ff,0x007f,
        0x003f,0x00ff,0x01ff,0x10ff,
        0x30ff,0xf87f,0xf87f,0xfc3f
    };
    long DownNum[16]={
        0x0000,0x7c00,0x6000,0x7000,
        0x7800,0x7c00,0x7e00,0x7f00,
        0x7f80,0x7e00,0x7c00,0x4600,
        0x0600,0x0300,0x0300,0x0180
    };

    for(i=0;i<16;i++){
        j=jj=15;
        while(UpNum[i]!=0){
            up[i][j]=UpNum[i]%2;
            j--;
            UpNum[i]/=2;
        }
        while(DownNum[i]!=0){
            down[i][jj--]=DownNum[i]%2;
            DownNum[i]/=2;
        }
        for(k=j;k>=0;k--)
            up[i][k]=0;
        for(k=jj;k>=0;k--)
            down[i][k]=0;
        for(k=0;k<16;k++){/*四种组合方式*/
            if(up[i][k]==0&&down[i][k]==0)
                mouse_draw[i][k]=1;
            else if(up[i][k]==0&&down[i][k]==1)
                mouse_draw[i][k]=2;
            else if(up[i][k]==1&&down[i][k]==0)
                mouse_draw[i][k]=3;
            else
                mouse_draw[i][k]=4;
        }
    }
    mouse_draw[1][2]=4;/*特殊点*/
}

void HandMath()/*手形鼠标的形状设置*/
{
    int i,j,jj,k;

    unsigned int UpNum[16]={
        -7681,-7681,-7681,-7681,
        -7681,-8192,-8192,-8192,
        0,0,0,0,
        0,0,0,0
    };
    unsigned int DownNum[16]={
        7680,4608,4608,4608,
        4608,5119,4681,4681,
        4681,-28671,-28671,-28671,
        -22767,-32767,-32767,-1
    };
	
	
	for(i=0;i<16;i++){
        j=jj=15;
        while(UpNum[i]!=0){
            up[i][j]=UpNum[i]%2;
            j--;
            UpNum[i]/=2;
        }
        while(DownNum[i]!=0){
            down[i][jj--]=DownNum[i]%2;
            DownNum[i]/=2;
        }
        for(k=j;k>=0;k--)
            up[i][k]=0;
        for(k=jj;k>=0;k--)
            down[i][k]=0;
        for(k=0;k<16;k++){/*四种组合方式*/
            if(up[i][k]==0&&down[i][k]==0)
                hand_draw[i][k]=1;
            else if(up[i][k]==0&&down[i][k]==1)
                hand_draw[i][k]=2;
            else if(up[i][k]==1&&down[i][k]==0)
                hand_draw[i][k]=3;
            else
                hand_draw[i][k]=4;
        }
    }
    hand_draw[1][2]=4;/*特殊点*/
}

/*鼠标光标显示*/
void MouseOn(int x,int y)
{
    int i,j;
    int color;

    for(i=0;i<16;i++){/*画鼠标*/
        for(j=0;j<16;j++) {
            pixel_save[i][j]=getpixel(x+j,y+i);/*保存原来的颜色*/
            if(mouse_draw[i][j]==1)
                putpixel(x+j,y+i,0);
            else if(mouse_draw[i][j]==2)
                putpixel(x+j,y+i,15);
        }
    }
	Mouse_Hand = 0;
}

/*手形鼠标光标显示*/
void HandOn(int x,int y)
{
    int i,j;
    int color;

    for(i=0;i<16;i++){/*画鼠标*/
        for(j=0;j<16;j++) {
            pixel_save[i][j]=getpixel(x+j,y+i);/*保存原来的颜色*/
            if(hand_draw[i][j]==1)
                putpixel(x+j,y+i,0);
            else if(hand_draw[i][j]==2)
                putpixel(x+j,y+i,15);
        }
    }
	
	Mouse_Hand = 1;
}


/*隐藏鼠标*/
void MouseOff()
{
    int i,j,x,y,color;
    x=MouseX;
    y=MouseY;
    for(i=0;i<16;i++)/*原位置异或消去*/
        for(j=0;j<16;j++){
            if(mouse_draw[i][j]==3||mouse_draw[i][j]==4)
                continue;
            color=getpixel(x+j,y+i);
            putpixel(x+j,y+i,color^color);
            putpixel(x+j,y+i,pixel_save[i][j]);
        }
}

void HandOff()
{
    int i,j,x,y,color;
    x=MouseX;
    y=MouseY;
    for(i=0;i<16;i++)/*原位置异或消去*/
        for(j=0;j<16;j++){
            if(hand_draw[i][j]==3||hand_draw[i][j]==4)
                continue;
            color=getpixel(x+j,y+i);
            putpixel(x+j,y+i,color^color);
            putpixel(x+j,y+i,pixel_save[i][j]);
        }
}

/*鼠标是否加载
  MouseExist:1=加载
             0=未加载
  MouseButton:鼠标按键数目
*/
void MouseLoad()
{
    _AX=0x00;
    geninterrupt(0x33);
    MouseExist=_AX;
    MouseButton=_BX;
}

/*鼠标状态值初始化*/
void MouseReset()
{
    _AX=0x00;
    geninterrupt(0x33);
}

/*设置鼠标左右边界
    lx:左边界
    rx:右边界
*/
void MouseSetX(int lx,int rx)
{
    _CX=lx;
    _DX=rx;
    _AX=0x07;
    geninterrupt(0x33);
}

/*设置鼠标上下边界
    uy:上边界
    dy:下边界
*/
void MouseSetY(int uy,int dy)
{
    _CX=uy;
    _DX=dy;
    _AX=0x08;
    geninterrupt(0x33);
}

/*设置鼠标当前位置
    x:横向坐标
    y:纵向坐标
*/
void MouseSetXY(int x,int y)
{
    _CX=x;
    _DX=y;
    _AX=0x04;
    geninterrupt(0x33);
}

/*设置鼠标速度(缺省值:vx=8,vy=1)
  值越大速度越慢
*/
void MouseSpeed(int vx,int vy)
{
    _CX=vx;
    _DX=vy;
    _AX=0x0f;
    geninterrupt(0x33);
}

/*获取鼠标按下键的信息
  是否按下左键
     返回值: 1=按下 0=释放
*/
int LeftPress()
{
    _AX=0x03;
    geninterrupt(0x33);
    return(_BX&1);
}

/*是否按下中键
  返回值同上
*/
int MiddlePress()
{
    _AX=0x03;
    geninterrupt(0x33);
    return(_BX&4);
}

/*是否按下右键
  返回值同上
*/
int RightPress()
{
    _AX=0x03;
    geninterrupt(0x33);
    return(_BX&2);
}

/*获取鼠标当前位置*/
void MouseGetXY()
{
    _AX=0x03;
    geninterrupt(0x33);
    MouseX=_CX;
    MouseY=_DX;
}

void initMouse()
{
	MouseMath();
	HandMath();
}
#endif