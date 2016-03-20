/* ************************************************************************
 *       Filename:  interface.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月03日 星期一 03時39分07秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "common.h"
#include "console.h"
#include "file.h"

void show_interface()
{
	int i = 0;
	
	system("clear");
	set_fg_color(COLOR_GREEN);
	printf("═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·");
	printf("═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·");
	printf("═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·\n");
	//fflush(stdout);

	for(i=0;i<36;i++)
	{
		cusor_moveto(114, i+2); //
		printf("‖");
	}
	cusor_moveto(0, 37); //
	printf("═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·");
	printf("═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·");
	printf("═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·═·\n");
	set_fg_color(COLOR_WHITE);
	cusor_moveto(9, 36);
}

void show_musicbar()
{
	int i = 0;
	
	cusor_moveto(0, 12);
	set_fg_color(COLOR_GREEN);
	printf("□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■\n");
	printf("·      >>  歌曲清单  <<      ·\n");
	printf("□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■\n");
	
	for(i=0;i<10;i++)
	{
		printf("                             □\n");
		printf("                             ■\n");	
	}
	printf("□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■\n");
	printf("· 搜索：                     ·\n");
	
	for(i=32;i<114;i++)
	{
		cusor_moveto(i, 12);
		printf("-");
	}
	fflush(stdout);
	set_fg_color(COLOR_WHITE);
	cusor_moveto(9, 36);
}

void show_logo()
{
	cusor_moveto(3, 4);
	printf("．．＿＿＿＿．╭╮╭╮．＿＿＿＿\n");
	cusor_moveto(3, 5);
	printf("．．＿．．．╭－┴┴★╮＿．．．．\n");
	cusor_moveto(3, 6);
	printf("．．＿．．．│◎　　︵│＿．．．\n");
	cusor_moveto(3, 7);
	printf("．．．※※※╰○－－○╯※※※．．\n");
	cusor_moveto(3, 8);
	printf("．．．．．．★ 欢迎光临 ★．．．\n");
	cusor_moveto(3, 9);
	printf("．．．．．．★ 无限透明 ★．．．\n");
}

void show_musiclist(char *plist[])
{
	int i = 0;
	
	set_fg_color(COLOR_BLUE);
	for(i=0;plist[i] != NULL && i<20;i++)
	{
		cusor_moveto(0, 15+i);
		printf("%d. %s",i+1,plist[i]);
	}
	set_fg_color(COLOR_WHITE);
	//show_musicbar();
}
