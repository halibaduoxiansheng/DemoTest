#include <stdio.h>
#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>


int main(void)
{
	//printf("Hello~\n");
	initgraph(500, 400, EX_SHOWCONSOLE);
	
	HRGN rgn = CreateRectRgn(100, 100, 200, 200);



	// ��������˳�
	_getch();
	closegraph();
	return 0;
}