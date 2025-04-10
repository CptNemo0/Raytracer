
#include <iostream>
#include "ColorBuffer.h"
#include "Triangle.h"

int main()
{
	buffer::ColorBuffer colorBuffer(800, 600);
	Color4 color(0, 255, 0, 255);
	colorBuffer.fillColorBuffer(color);

	Color4 colorT(255, 0, 255, 255);


	math::vec3 v0_ndc(0.0f, -0.5f, 0.0f);
	math::vec3 v1_ndc(-0.5f, 0.0f, 0.0f);
	math::vec3 v2_ndc(0.0f, 0.8f, 3.0f);

	math::vec3 v0(0.5f, 0.5f, 2.0f);
	math::vec3 v1(-0.4f, -0.5f, 2.0f);
	math::vec3 v2(0.0f, 1.0f, 2.0f);

    int height = colorBuffer.height_;
    int width = colorBuffer.width_;

    math::vec3 v0_screen = { float((v0_ndc[0] + 1) * 0.5 * width), float((1 - v0_ndc[1]) * 0.5 * height), v0_ndc[2] };
    math::vec3 v1_screen = { float((v1_ndc[0] + 1) * 0.5 * width), float((1 - v1_ndc[1]) * 0.5 * height), v1_ndc[2] };
    math::vec3 v2_screen = { float((v2_ndc[0] + 1) * 0.5 * width), float((1 - v2_ndc[1]) * 0.5 * height), v2_ndc[2] };

	// Convert to screen coordinates
	math::vec3 v0_screen1 = { float((v0[0] + 1) * 0.5 * width), float((1 - v0[1]) * 0.5 * height), v0[2] };
	math::vec3 v1_screen1 = { float((v1[0] + 1) * 0.5 * width), float((1 - v1[1]) * 0.5 * height), v1[2] };
	math::vec3 v2_screen1 = { float((v2[0] + 1) * 0.5 * width), float((1 - v2[1]) * 0.5 * height), v2[2] };


    Triangle triangle(v0_screen, v1_screen, v2_screen);
	Triangle triangle1(v0_screen1, v1_screen1, v2_screen1);
	triangle1.SetColors(colorT, colorT, colorT);

	triangle1.drawTriangle(colorBuffer);
	triangle.drawTriangle(colorBuffer);

	colorBuffer.generateBMP("test.bmp");
	return 0;
}

