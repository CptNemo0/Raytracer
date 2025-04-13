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

	rendering::PixelBuffer buffer(1920, 1080);
	rendering::Renderer renderer(&cam, &buffer);

	lights::PointLight light1(math::vec3(0.0f, 1.0f, 3.0f), rendering::color4f(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
	light1.setAttenuation(0.0f, 0.5f, 0.0f);
	renderer.AddPointLight(light1);

	rendering::Material red_diffuse(
		rendering::color4f(10.0f, 0.0f, 0.0f, 255.0f),
		rendering::color4f(255.0f, 0.0f, 0.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		4.0f
	);

	rendering::Material blue_diffuse(
		rendering::color4f(0.0f, 0.0f, 10.0f, 255.0f),
		rendering::color4f(0.0f, 0.0f, 255.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		4.0f
	);

	rendering::Material white_diffuse(
		rendering::color4f(3.0f, 3.0f, 3.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		4.0f
	);

	rendering::Material green_specular(
		rendering::color4f(0.0f, 10.0f, 0.0f, 255.0f),
		rendering::color4f(0.0f, 255.0f, 0.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		20.0f
	);

	auto left_plane = renderer.AddPlane(math::vec3(1.0f, 0.0f, 0.0f), math::vec3(-15.0f, 0.0f, 0.0f));
	left_plane->SetMaterial(red_diffuse);
	
	auto right_plane = renderer.AddPlane(math::vec3(-1.0f, 0.0f, 0.0f), math::vec3(15.0f, 0.0f, 0.0f));
	right_plane->SetMaterial(blue_diffuse);
	
	auto back_plane = renderer.AddPlane(math::vec3(0.0f, 0.0f, -1.0f), math::vec3(0.0f, 0.0f, 15.0f));
	back_plane->SetMaterial(white_diffuse);
	
	auto bot_plane = renderer.AddPlane(math::vec3(0.0f, 1.0f, 0.0f), math::vec3(0.0f, -10.0f, 0.0f));
	bot_plane->SetMaterial(white_diffuse);
	
	auto top_plane = renderer.AddPlane(math::vec3(0.0f, -1.0f, 0.0f), math::vec3(0.0f, 10.0f, 0.0f));
	top_plane->SetMaterial(white_diffuse);

	auto sphere_1 = renderer.AddSphere(math::vec3(2.5, 0.0f, 5.0f), 2.0f);
	sphere_1->SetMaterial(green_specular);
	
	auto sphere_2 = renderer.AddSphere(math::vec3(-1.0f, 1.0f, 5.0f), 1.0f);
	sphere_2->SetMaterial(green_specular);
	
	auto sphere_3 = renderer.AddSphere(math::vec3(-3.0f, -1.0f, 5.0f), 0.5f);
	sphere_3->SetMaterial(green_specular);

	renderer.Render();

	return 0;
}