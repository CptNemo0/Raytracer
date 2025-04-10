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
	//cam.scale_ = 0.05f;
	
	rendering::Material material1(
		rendering::color4f(25.5f, 0.0f, 0.0f, 255.0f),
		rendering::color4f(170.0f, 0.0f, 0.0f, 255.0f),
		rendering::color4f(170.0f, 170.0f, 170.0f, 255.0f),
		50.0f
	);


	rendering::Material material2(
		rendering::color4f(25.5f, 0.0f, 0.0f, 255.0f),
		rendering::color4f(170.0f, 0.0f, 0.0f, 255.0f),
		rendering::color4f(170.0f, 170.0f, 170.0f, 255.0f),
		5.0f
	);

	rendering::Material material3(
		rendering::color4f(0.0f, 25.0f, 0.0f, 255.0f),
		rendering::color4f(0.0f, 170.0f, 0.0f, 255.0f),
		rendering::color4f(170.0f, 170.0f, 170.0f, 255.0f),
		1.0f
	);

	rendering::PixelBuffer buffer(1920, 1080);
	rendering::Renderer renderer(&cam, &buffer);

	auto sphere1 = renderer.AddSphere(math::vec3(5.0f, 0.0f, 10.0f), 2.0f);
	auto sphere2 = renderer.AddSphere(math::vec3(-5.0f, 0.0f, 10.0f), 2.0f);
	auto triangle = renderer.AddTriangle(
		math::vec3(0.0f, 50.0f, 20.0f),
		math::vec3(50.0f, -50.0f, 20.0f),
		math::vec3(-50.0f, -50.0f, 30.0f)
	);

	sphere1->SetMaterial(material1);
	sphere2->SetMaterial(material2);
	triangle->SetMaterial(material3);
	lights::PointLight light1(math::vec3(0.0f, 5.0f, 5.0f), rendering::color4f(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
	lights::PointLight light2(math::vec3(5.0f, 5.0f, 5.0f), rendering::color4f(0.0f, 0.0f, 1.0f, 1.0f), 1.0f);
	light1.setAttenuation(0.0f, 0.0f, 0.0f);
	light2.setAttenuation(0.0f, 0.0f, 0.0f);

	

	renderer.AddPointLight(light1);
	renderer.AddPointLight(light2);
	renderer.Render();

	return 0;
}