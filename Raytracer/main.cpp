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
#include <chrono>
int main(int argc, char** argv)
{
	rendering::PerspectiveCamera cam;
	cam.scale_ = 3.025f;
	cam.fov_ = math::pid4;
	cam.position_ = math::vec3(0.0f, -6.0f, -3.0f);
	cam.aspect_ratio_ = 16.0f / 9.0f;
	//cam.scale_ = 0.05f;

	rendering::PixelBuffer buffer(1280, 720);
	rendering::Renderer renderer(&cam, &buffer, 6);

	lights::PointLight light1(math::vec3(3.0f, 7.5f, 5.0f), rendering::color4f(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
	light1.setAttenuation(0.5f, -1.0f, 3.0f);
	renderer.AddPointLight(light1);

	lights::PointLight light2(math::vec3(-3.0f, 7.5f, 5.0f), rendering::color4f(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
	light2.setAttenuation(0.5f, -1.0f, 3.0f);
	renderer.AddPointLight(light2);

	auto red_diffuse = std::make_shared<rendering::Material>(
		rendering::color4f(6.0f, 6.0f, 6.0f, 255.0f),
		rendering::color4f(255.0f, 0.0f, 0.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		4.0f,
		rendering::MaterialType::DIFFUSE
	);

	auto blue_diffuse = std::make_shared<rendering::Material>(
		rendering::color4f(6.0f, 6.0f, 6.0f, 255.0f),
		rendering::color4f(0.0f, 0.0f, 255.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		4.0f,
		rendering::MaterialType::DIFFUSE
	);

	auto white_diffuse = std::make_shared<rendering::Material>(
		rendering::color4f(6.0f, 6.0f, 6.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		4.0f,
		rendering::MaterialType::DIFFUSE
	);

	auto white_diffuse_highspec = std::make_shared<rendering::Material>(
		rendering::color4f(6.0f, 6.0f, 6.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		20.0f,
		rendering::MaterialType::DIFFUSE
	);

	auto reflective = std::make_shared<rendering::Material>(
		rendering::color4f(6.0f, 6.0f, 6.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		40.0f,
		rendering::MaterialType::REFLECTIVE
	);

	auto shinny_green = std::make_shared<rendering::Material>(
		rendering::color4f(6.0f, 6.0f, 6.0f, 255.0f),
		rendering::color4f(0.0f, 255.0f, 0.0f, 255.0f),
		rendering::color4f(0.0f, 255.0f, 0.0f, 255.0f),
		40.0f,
		rendering::MaterialType::DIFFUSE
	);

	auto refractive = std::make_shared<rendering::Material>(
		rendering::color4f(6.0f, 6.0f, 6.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		40.0f,
		rendering::MaterialType::REFRACTIVE
	);
	refractive->refraction_index_ =	1.02f;


	auto hihgly_refractive = std::make_shared<rendering::Material>(
		rendering::color4f(6.0f, 6.0f, 6.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		rendering::color4f(255.0f, 255.0f, 255.0f, 255.0f),
		40.0f,
		rendering::MaterialType::REFRACTIVE
	);
	hihgly_refractive->refraction_index_ = 1.1f;

	auto left_plane = renderer.AddPlane(math::vec3(1.0f, 0.0f, 0.0f), math::vec3(-15.0f, 0.0f, 0.0f));
	left_plane->material_ = blue_diffuse;

	auto right_plane = renderer.AddPlane(math::vec3(-1.0f, 0.0f, 0.0f), math::vec3(15.0f, 0.0f, 0.0f));
	right_plane->material_ = red_diffuse;
	
	auto back_plane = renderer.AddPlane(math::vec3(0.0f, 0.0f, -1.0f), math::vec3(0.0f, 0.0f, 15.0f));
	back_plane->material_ = white_diffuse;
	
	auto bot_plane = renderer.AddPlane(math::vec3(0.0f, 1.0f, 0.0f), math::vec3(0.0f, -10.0f, 0.0f));
	bot_plane->material_ = white_diffuse;
	
	auto top_plane = renderer.AddPlane(math::vec3(0.0f, -1.0f, 0.0f), math::vec3(0.0f, 10.0f, 0.0f));
	top_plane->material_ = white_diffuse;

	auto sphere_1 = renderer.AddSphere(math::vec3(-3.0f, -7.0f, 10.0f), 3.0f);
	sphere_1->material_ = reflective;
	
	auto sphere_2 = renderer.AddSphere(math::vec3(4.0f, -7.0f, 5.0f), 3.0f);
	sphere_2->material_ = refractive;

	auto sphere_3 = renderer.AddSphere(math::vec3(3.0f, -7.0f, 10.0f), 2.0f);
	sphere_3->material_ = shinny_green;
	
	auto sphere_4 = renderer.AddSphere(math::vec3(-5.0f, -7.0f, 2.0f), 3.0f);
	sphere_4->material_ = hihgly_refractive;

	// Start timing
	auto start_time = std::chrono::high_resolution_clock::now();
	renderer.Render();
	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	std::cout << "Rendering took " << duration.count() << " milliseconds." << std::endl;
	return 0;
}