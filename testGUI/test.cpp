#include <graphics.h>		// Reference graphics library header file
#include <conio.h>
int main()
{
	initgraph(640, 480);	// Create a graphics window with a size of 640x480 pixels
	circle(200, 200, 100);	// Draw a circle with center (200, 200) and radius 100
	_getch();				// Press any key to continue
	closegraph();			// Close the graphics window
	return 0;
}
