#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif // !STB_IMAGE_WRITE_IMPLEMENTATION

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#include "rendering/stb_image_write.h"
#include "rendering/PixelBuffer.h"
#include "rendering/Camera.h"

#include <iostream>
#include "raytracer_math.h"

#include <vector>
#include <memory>
#include <variant>

#include "intersections/Ray.h"
#include "intersections/IntersectionResult.h"
#include "intersections/IntersectionType.h"

#include "primitives/primitives.h"
#include "rendering/Renderer.h"

int main(int argc, char** argv)
{
	rendering::OrthographicCamera cam;
	cam.scale_ = 0.025f;

	rendering::Material material1(rendering::color4(255, 0, 0, 255));
	rendering::Material material2(rendering::color4(0, 0, 255, 255));
	rendering::Material material3(rendering::color4(0, 255, 0, 255));

	rendering::PixelBuffer buffer(1920, 1080);

	rendering::Renderer renderer(&cam, &buffer);
	auto sphere1 = renderer.AddSphere(math::vec3(1.0f, 0.0f, 10.0f), 2.0f);
	auto sphere2 = renderer.AddSphere(math::vec3(-1.0f, 0.0f, 15.0f), 2.0f);
	auto triangle = renderer.AddTriangle(math::vec3(-3.0f, 0.0f, 1.0f), math::vec3(3.0f, 0.0f, 1.0f), math::vec3(0.0f, 3.0f, 1.0f));

	sphere1->SetMaterial(material1);
	sphere2->SetMaterial(material2);
	triangle->SetMaterial(material3);

	renderer.FillBackground();
	renderer.Render();

	return 0;
}