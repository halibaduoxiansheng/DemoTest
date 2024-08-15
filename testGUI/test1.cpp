#include <stdio.h>
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>


int main(void)
{
	//printf("Hello~\n");
	initgraph(500, 400, EX_SHOWCONSOLE);
	
	HRGN rgn = CreateRectRgn(100, 100, 200, 200);



	// 按任意键退出
	_getch();
	closegraph();
	return 0;
}