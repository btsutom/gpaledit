/**************************************
 gpaledit.c
 
 一応こんなソフトでも著作権は放棄しません。
 もし配布する場合は、tsutoban@gmail.comに
 連絡してもらえるとうれしいです。
 ここの表示(／＊ から ＊／ まで）は消さないでください。
 **************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "sg.h"

#define ESC		0x00
#define ENTER	0x1c
#define UP		0x3a
#define LEFT	0x3b
#define RIGHT	0x3c
#define DOWN	0x3d
#define F1		0x62
#define F2		0x63
#define F3		0x64
#define F4		0x65
#define F5		0x66
#define F6		0x67
#define F7		0x68
#define F8		0x69
#define F9		0x6a
#define F10   0x6b
#define KEY_1  1
#define KEY_0 10
#define KEY_W 17   // R1 of RGB : up
#define KEY_E 18   // G1 of RGB : up
#define KEY_R 19   // B1 of RGB : up
#define KEY_S 30   // R1 of RGB : down
#define KEY_D 31   // G1 of RGB : down
#define KEY_F 32   // B1 of RGB : down
#define KEY_U 22   // R0 of RGB : up
#define KEY_I 23   // G0 of RGB : up
#define KEY_O 24   // B0 of RGB : up
#define KEY_J 35   // R0 of RGB : down
#define KEY_K 36   // G0 of RGB : down
#define KEY_L 37   // B0 of RGB : down

int KeyScan(void)
{
 int key=0;
 
 asm mov ah, 0h;
 asm int 018h;
 asm mov key, ah;
 
 return key;
}

void initscreen()
{
	gotoxy(9,3); printf("1:左を選択　    0:右を選択　　　ESC:終了");
	gotoxy(9,5); printf("左 R  G  B      R  G  B 右");
	gotoxy(9,6); printf("↑ w  e  r      u  i  o ↑");
	gotoxy(9,7); printf("↓ s  d  f      j  k  l ↓");
}

void printvalue(int key, int* r, int* g, int* b)
{
	gotoxy(12,10);
	printf("R  G  B");
	gotoxy(11,11);
	printf("%2d %2d %2d", r[0], g[0], b[0]);
	gotoxy(25, 10);
	printf("R  G  B");
	gotoxy(24, 11);
	printf("%2d %2d %2d", r[1], g[1], b[1]);

	if( key == KEY_W && r[0] < 15) r[0] += 1;
	if( key == KEY_E && g[0] < 15) g[0] += 1;
	if( key == KEY_R && b[0] < 15) b[0] += 1;
	if( key == KEY_S && r[0] > 0 ) r[0] -= 1;
	if( key == KEY_D && g[0] > 0 ) g[0] -= 1;
	if( key == KEY_F && b[0] > 0 ) b[0] -= 1;

	if( key == KEY_U && r[1] < 15) r[1] += 1;
	if( key == KEY_I && g[1] < 15) g[1] += 1;
	if( key == KEY_O && b[1] < 15) b[1] += 1;
	if( key == KEY_J && r[1] > 0 ) r[1] -= 1;
	if( key == KEY_K && g[1] > 0 ) g[1] -= 1;
	if( key == KEY_L && b[1] > 0 ) b[1] -= 1;

	if ((key == KEY_1) || (key == LEFT))
	{
		gotoxy(26,9);
		printf("   ");
		gotoxy(13,9);
		printf("  *");
	}
	else if ((key == KEY_0) || (key == RIGHT))
	{
	  gotoxy(13,9);
	  printf("   ");
		gotoxy(26,9);
		printf("  *");
	}

/**
	gotoxy(12,10);
	printf("R  G  B");
	gotoxy(11,11);
	printf("%2d %2d %2d", r[0], g[0], b[0]);
	gotoxy(25, 10);
	printf("R  G  B");
	gotoxy(24, 11);
	printf("%2d %2d %2d", r[1], g[1], b[1]);
 **/
}

void initbox()
{
		boxf(100, 200, 130, 250, 1);
		boxf(200, 200, 230, 250, 2);
}

void drawbox(int s, int* r, int* g, int* b)
{
	if((s == KEY_1) || (s == LEFT))
	{
		gpal1( 1, g[0], r[0], b[0] );
		boxf(100, 200, 130, 250, 1);
	} else if((s == KEY_0) || (s == RIGHT))
	{
		gpal1( 2, g[1], r[1], b[1] );
		boxf(200, 200, 230, 250, 2);
	}
}

int main()
{
	int r[2]={5, 6}, g[2]={9, 7}, b[2]={2, 8};
	int key=0, s=1;

	gon(0);
	clrscr();
	gcls();
	initscreen();
	gpal1( 1, g[0], r[0], b[0] );
	gpal1( 2, g[1], r[1], b[1] );
	initbox();
	printvalue(KEY_0, r, g, b);
	while( (key=KeyScan()) != ESC)
	{
			printvalue(key, r, g, b);
			drawbox(s, r, g, b);
			if( (key == KEY_0) || (key == KEY_1) ||
		 		(key == LEFT) || (key == RIGHT)) s = key;
	}
	goff();
	clrscr();
	return 0;
}
