
#include <iostream>
#include "Rasterizer.h"

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


	math::mat4x4 projectionMatrix = math::projection_matrix(90.0f, float(width) / float(height), 0.1f, 100.0f);

	Triangle triangle(v0_ndc, v1_ndc, v2_ndc);
	Triangle triangle1(v0, v1, v2);
	triangle1.SetColors(colorT, colorT, colorT);


	Rasterizer rasterizer(colorBuffer);
	rasterizer.addProjectionMatrix(projectionMatrix);
	
	rasterizer.rasterize(triangle);
	rasterizer.rasterize(triangle1);


	colorBuffer.generateBMP("test.bmp");
	return 0;
}

