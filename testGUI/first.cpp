/*#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
int main()
{
	initgraph(640, 480, EX_SHOWCONSOLE); // create window 640X480 and show console window
	//circle(200, 200, 100);	// 画圆，圆心(200, 200)，半径 100
	setlinecolor(0xff1010);

	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
	return 0;
}*/

/*#include <graphics.h>
#include <conio.h>

void main()
{
	// 初始化绘图窗口
	initgraph(640, 480);

	// 创建一个矩形区域
	HRGN rgn = CreateRectRgn(100, 100, 200, 200);
	// 将该矩形区域设置为裁剪区
	setcliprgn(rgn);
	// 不再使用 rgn，清理 rgn 占用的系统资源
	DeleteObject(rgn);

	// 画圆，受裁剪区影响，只显示出四段圆弧
	circle(150, 150, 55);

	// 取消之前设置的裁剪区
	setcliprgn(NULL);

	// 画圆，不再受裁剪区影响，显示出一个完整的圆
	circle(150, 150, 60);

	// 按任意键退出
	_getch();
	closegraph();
}*/

/*
// https://easyx.cn
//
#include <graphics.h>
#include <time.h>
#include <conio.h>
// ————————>x
//	|
//	|
//	|
//	|
//  v
//  y
int main(void)
{
	// 设置随机种子
	srand((unsigned) time(NULL));

	// 初始化图形模式
	initgraph(640, 480);

	int  x, y;
	char c;

	settextstyle(16, 8, _T("Courier"));	// 设置字体

	// 设置颜色
	settextcolor(GREEN);
	setlinecolor(BLACK);

	for (int i = 0; i <= 479; i++)
	{
		// 在随机位置显示三个随机字母
		for (int j = 0; j < 4; j++)
		{
			x = (rand() % 80) * 8;
			y = (rand() % 20) * 24;
			c = (rand() % 26) + 65; // 显示大写字母
			outtextxy(x, y, c); // 在 (x,y) 显示字符
		}

		// 画线擦掉一个像素行
		line(0, i, 639, i); // 起始x坐标、气质y坐标  终止x坐标、终止y坐标
		

		Sleep(10);					// 延时
		if (i >= 479)	i = -1;
		if (_kbhit())	break;		// 按任意键退出
	}

	// 关闭图形模式
	closegraph();
	return 0;
}
*/

/*
// 编译环境：Visual C++ 6.0~2022，EasyX_2023大暑版
// https://easyx.cn
//
#include <graphics.h>
#include <time.h>
#include <conio.h>

#define MAXSTAR 200	// 星星总数

struct STAR
{
	double	x;
	int		y;
	double	step;
	int		color;
};

STAR star[MAXSTAR];

// 初始化星星
void InitStar(int i)
{
	star[i].x = 0;
	star[i].y = rand() % 480;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// 速度越快，颜色越亮
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}

// 移动星星
void MoveStar(int i)
{
	// 擦掉原来的星星
	putpixel((int)star[i].x, star[i].y, 0);

	// 计算新位置
	star[i].x += star[i].step;
	if (star[i].x > 640)	InitStar(i);

	// 画新星星
	putpixel((int)star[i].x, star[i].y, star[i].color);
}

// 主函数
int main()
{
	srand((unsigned)time(NULL));	// 随机种子
	initgraph(640, 480);			// 创建绘图窗口

	// 初始化所有星星
	for(int i = 0; i < MAXSTAR; i++)
	{
		InitStar(i);
		star[i].x = rand() % 640;
	}

	// 绘制星空，按任意键退出
	while(!_kbhit())
	{
		for(int i = 0; i < MAXSTAR; i++)
			MoveStar(i);
		Sleep(20);
	}

	closegraph();					// 关闭绘图窗口
	return 0;
}
*/

// 编译环境：Visual C++ 6.0~2022，EasyX_2023大暑版
// https://easyx.cn
//
#include <graphics.h>

int main(void)
{
	// 初始化图形窗口
	initgraph(640, 480);

	ExMessage m;		// 定义消息变量

	while(true)
	{
		// 获取一条鼠标或按键消息
		m = getmessage(EX_MOUSE | EX_KEY);

		switch(m.message)
		{
			case WM_MOUSEMOVE:
				// 鼠标移动的时候画红色的小点
				putpixel(m.x, m.y, RED);
				break;

			case WM_LBUTTONDOWN:
				// 如果点左键的同时按下了 Ctrl 键
				if (m.ctrl)
					// 画一个大方块
					rectangle(m.x - 20, m.y - 20, m.x + 20, m.y + 20);
				else if (m.shift)
					rectangle(m.x - 10, m.y - 10, m.x + 10, m.y + 10);
				else
					// 画一个小方块
					rectangle(m.x - 5, m.y - 5, m.x + 5, m.y + 5);
				break;

			case WM_KEYDOWN:
				if (m.vkcode == VK_ESCAPE)
					return 0;	// 按 ESC 键退出程序
		}
	}

	// 关闭图形窗口
	closegraph();
	return 0;
}


/*
// 编译环境：Visual C++ 6.0~2022，EasyX_2023大暑版
// https://easyx.cn
// ctrl+F6返回到上一个光标
#include <graphics.h>
#include <conio.h>

int main(void)
{
	// 创建绘图窗口
	initgraph(640, 480);

	// 画渐变的天空(通过亮度逐渐增加)
	float H = 190;		// 色相 就是颜色
	float S = 1;		// 饱和度 0~1  0表示最灰 1表示最纯
	float L = 0.7f;		// 亮度 0~1 越大越亮
	for(int y = 0; y < 480; y++)
	{
		L += 0.0005f;
		setlinecolor( HSLtoRGB(H, S, L) );
		line(0, y, 639, y);
	}

	// 画彩虹(通过色相逐渐增加)
	H = 0;
	S = 1;
	L = 0.5f;
	setlinestyle(PS_SOLID, 2);		// 设置 线宽 为 2
	for(int r = 400; r > 344; r--)
	{
		H += 5;
		setlinecolor( HSLtoRGB(H, S, L) );
		circle(500, 480, r); // 圆心不变 减小半径
	}

	// 按任意键退出
	_getch();
	closegraph();
	return 0;
}*/


/*#include <graphics.h>
#include <conio.h>

int main(void)
{	
	initgraph(640, 480);
	fillcircle(10,10,2);


	_getch();
	closegraph();
	return 0;
}*/