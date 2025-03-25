
#include <iostream>
#include "ColorBuffer.h"

int main()
{
	buffer::ColorBuffer colorBuffer(800, 600);
	colorBuffer.fillColorBuffer(Color4(255, 0, 0, 255));

	colorBuffer.generateBMP("test.bmp");
	return 0;
}

