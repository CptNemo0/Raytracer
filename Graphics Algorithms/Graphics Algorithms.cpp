
#include <iostream>
#include "ColorBuffer.h"
#include "Triangle.h"

int main()
{
	buffer::ColorBuffer colorBuffer(800, 600);
	Color4 color(0, 255, 0, 255);
	colorBuffer.fillColorBuffer(color);

	Color4 colorT(0, 0, 255, 255);
    // Definiujemy współrzędne w układzie [-1, 1]
    math::vec<2, float> v0_ndc = { 0.5, 0.9 };
    math::vec<2, float> v1_ndc = { 0.5, 0.0 };
    math::vec<2, float> v2_ndc = { 0.0, 0.0 };

    // Przekształcamy na współrzędne ekranu
    int height = colorBuffer.height_;
    int width = colorBuffer.width_;

    math::vec<2, float> v0_screen = { float((v0_ndc[0] + 1) * 0.5 * width), float((1 - v0_ndc[1]) * 0.5 * height) };
    math::vec<2, float> v1_screen = { float((v1_ndc[0] + 1) * 0.5 * width), float((1 - v1_ndc[1]) * 0.5 * height) };
    math::vec<2, float> v2_screen = { float((v2_ndc[0] + 1) * 0.5 * width), float((1 - v2_ndc[1]) * 0.5 * height) };

    // Tworzymy trójkąt w przestrzeni ekranu
    Triangle triangle(v0_screen, v1_screen, v2_screen);

	triangle.drawTriangle(colorBuffer, colorT);

	colorBuffer.generateBMP("test.bmp");
	return 0;
}

