
#include <iostream>
#include "ColorBuffer.h"

int main()
{
	buffer::ColorBuffer colorBuffer(800, 600);
	Color4 color(255, 0, 0, 255);
	colorBuffer.fillColorBuffer(color);

	colorBuffer.generateBMP("test.bmp");
	return 0;
}

