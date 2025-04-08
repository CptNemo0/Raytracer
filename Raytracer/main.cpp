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
#include "lights/PointLight.h"

int main(int argc, char** argv)
{
	rendering::PerspectiveCamera cam;
	cam.scale_ = 3.025f;
	
	rendering::Material material1(
		rendering::color4f(25.5f, 0.0f, 0.0f, 255.0f),
		rendering::color4f(255.0f, 0.0f, 0.0f, 255.0f),
		rendering::color4f(250.0f, 250.0f, 250.0f, 255.0f),
		8.0f
	);


	rendering::PixelBuffer buffer(1920, 1080);

	rendering::Renderer renderer(&cam, &buffer);

	srand(static_cast<unsigned int>(time(nullptr)));
	for (int i = 0; i < 50; i++)
	{
		float x = static_cast<float>(rand() % 300) * 0.1f - 15.0f;
		float y = static_cast<float>(rand() % 300) * 0.1f - 15.0f;
		float z = static_cast<float>(rand() % 100) * 0.1f + 10.0f;
		float r = rand() % 3 + 1;

		auto sphere = renderer.AddSphere(math::vec3(x, y, z), r);
		sphere->SetMaterial(material1);
	}

	lights::PointLight light(math::vec3(-5.0f, 5.0f, 5.0f), rendering::color4f(1.0f, 1.0f, 0.2f, 1.0f), 1.0f);
	light.setAttenuation(0.0f, 0.0f, 0.0f);
	renderer.AddPointLight(light);
	//auto sphere2 = renderer.AddSphere(math::vec3(5.0f, 0.0f, 10.0f), 5.0f);
	//
	//sphere1->SetMaterial(material1);
	//sphere2->SetMaterial(material1);

	//renderer.FillBackground();
	renderer.Render();

	return 0;
}