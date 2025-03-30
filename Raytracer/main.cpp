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

//void Photorealistic1stLab()
//{
//	{
//		std::cout << "1 - 2. Vectors basic operations\n";
//		math::vec4 a(1, 2, 3, 4);
//		math::vec4 b(5, 6, 7, 8);
//
//		std::cout << "a = " << a << std::endl;
//		std::cout << "b = " << b << std::endl;
//		std::cout << "a + b = " << a + b << std::endl;
//		std::cout << "b + a = " << b + a << std::endl;
//		std::cout << "a - b = " << a - b << std::endl;
//		std::cout << "b - a = " << b - a << std::endl;
//		std::cout << "a * 2 = " << a * 2 << std::endl;
//		std::cout << "a / 2 = " << a / 2 << std::endl;
//	}
//
//	{
//		std::cout << "\n3. Find an angle between vectors [0,3,0] a [5,5,0]\n";
//		math::vec3 a(0, 3, 0);
//		math::vec3 b(5, 5, 0);
//		std::cout << "angle_degrees(a, b) = " << math::angle_deg(a, b) << std::endl;
//	}
//		
//	{
//		std::cout << "\n4. Find a vector perpendicular to [4,5,1] i [4,1,3]\n";
//		math::vec3 a(4, 5, 1);
//		math::vec3 b(4, 1, 3);
//		math::vec3 c = math::cross(a, b);
//		std::cout << "cross(a, b) = c " << c << std::endl;
//
//		std::cout << "\n5. Normalize this vector\n";
//		math::normalize(c);
//		std::cout << "c: " << c << std::endl;
//
//		
//	}
//	{
//		std::cout << "\n7. Define a sphere S with center at (0,0,0) and radius 10\n";
//		primitives::Sphere S(math::vec3(0, 0, 0), 10);
//		std::cout << "S: " << S << std::endl;
//
//		std::cout << "\n8. Define a ray R1 starting at (0,0,-20), directed towards the center of the sphere S\n";
//		intersections::Ray R1(math::vec3(0, 0, -20), math::vec3(0, 0, 1));
//		std::cout << "R1: " << R1 << std::endl;
//
//		std::cout << "\n9. Define a ray R2 with the same starting point as R1, but directed parallel to the Y-axis\n";
//		intersections::Ray R2(math::vec3(0, 0, -20), math::vec3(0, 1, 0));
//		std::cout << "R2: " << R2 << std::endl;
//
//		std::cout << "\n10 - 11. Check if the sphere S intersects with rays R1 and R2\n";
//		math::vec3 hitPoint1, hitPoint2;
//			//if (S.Hit(R1, 0, 100, hitPoint1)) {//sprawdza tylko pierwszy punkt przeciecia
//			//	std::cout << "S intersects with R1 at: " << hitPoint1 << std::endl;
//			//}
//			//else {
//			//	std::cout << "S does not intersect with R1" << std::endl;
//			//}
//			//if (S.Hit(R2, 0, 100, hitPoint1)) {
//			//	std::cout << "S intersects with R2 at: " << hitPoint1 << std::endl;
//			//}
//			//else {
//			//	std::cout << "S does not intersect with R2" << std::endl;
//			//}
//
//			if (S.Hit(R1, 0, 100, hitPoint1, hitPoint2)) {//sprawdza oba punkty przeciecia
//				std::cout << "S intersects with R1 at: " << hitPoint1 << "and" << hitPoint2 << std::endl;
//			}
//			else {
//				std::cout << "S does not intersect with R1" << std::endl;
//			}
//			if (S.Hit(R2, 0, 100, hitPoint1, hitPoint2)) {
//				std::cout << "S intersects with R2 at: " << hitPoint1 << "and" << hitPoint2 << std::endl;
//			}
//			else {
//				std::cout << "S does not intersect with R2" << std::endl;
//			}
//
//		std::cout << "\n12. Define any ray R3 such that it intersects the sphere S at exactly one point. Provide the coordinates of the intersection point.\n";
//        intersections::Ray R3(math::vec3(10, -10, 0), math::vec3(0, 1, 0));
//        std::cout << "R3: " << R3 << std::endl;
//
//            if (S.Hit(R3, 0, 100, hitPoint1)) {
//                std::cout << "S intersects with R3 at: " << hitPoint1 << std::endl;
//            } else {
//                std::cout << "S does not intersect with R3" << std::endl;
//            }
//	
//		std::cout << "\n13 - 14. Define a plane P passing through (0,0,0), with a normal vector forming a 45° angle with both the Y- and Z-axes. Find the intersection point of plane P with ray R2\n";
//		math::vec3 normal(0, sqrt(2) / 2, sqrt(2) / 2);
//		math::normalize(normal);
//		primitives::Plane P(normal, math::vec3(0, 0, 0));
//		std::cout << "P: " << P << std::endl;
//
//		intersections::IntersectionResult result = P.Intersects(R2, 0);
//		if (result.type == intersections::IntersectionResult::HIT || result.type == intersections::IntersectionResult::INSIDE_PRIMITIVE) {
//			std::cout << "P intersects with R2 at: " << result.intersection_point << std::endl;
//		}
//		else {
//			std::cout << "P does not intersect with R2" << std::endl;
//		}
//
//	}
//
//
//	{
//		std::cout << "\n15. We have a triangle defined by the points A(0, 0, 0), B(1, 0, 0), and C(0, 1, 0). Check if a line defined by points P1 and P2 intersects this triangle.\n";
//		primitives::Triangle T(math::vec3(0, 0, 0), math::vec3(1, 0, 0), math::vec3(0, 1, 0));
//		std::cout << "T: " << T << std::endl;
//		std::cout << "\n1) \n" << std::endl;
//		math::vec3 P1(-1, 0.5, 0);
//		math::vec3 P2(1, 0.5, 0);
//		math::vec3 direction = P2 - P1;
//		math::normalize(direction);
//		intersections::Ray R(P1, direction);
//		math::vec3 result;
//		if (T.IntersectTriangle(R, T.vertices[0], T.vertices[1], T.vertices[2], result))
//		{
//			std::cout << "true" << ", result:" << result << std::endl;
//		}
//		else
//		{
//			std::cout << "false" << std::endl;
//		}
//
//		std::cout << "\n2) \n" << std::endl;
//		P1 = math::vec3(2, -1, 0);
//		P2 = math::vec3(2, 2, 0);
//		direction = P2 - P1;
//		math::normalize(direction);
//		R = intersections::Ray(P1, direction);
//		if (T.IntersectTriangle(R, T.vertices[0], T.vertices[1], T.vertices[2], result))
//		{
//			std::cout << "true" << ", result:" << result << std::endl;
//		}
//		else
//		{
//			std::cout << "false" << std::endl;
//		}
//
//		std::cout << "\n3) \n" << std::endl;
//		P1 = math::vec3(0, 0, -1);
//		P2 = math::vec3(0, 0, 1);
//		direction = P2 - P1;
//		math::normalize(direction);
//		R = intersections::Ray(P1, direction);
//
//		if (T.IntersectTriangle(R, T.vertices[0], T.vertices[1], T.vertices[2], result))
//		{
//			std::cout << "true" << ", result:" << result << std::endl;
//		}
//		else
//		{
//			std::cout << "false" << std::endl;
//		}
//	}
//		
//	std::cout << "\n\nAdditional\n";
//
//	{
//		std::cout << "1 - 2. Matrices basic operations\n";
//		math::mat4x4 a(2.0f, true);
//		math::mat4x4 b(8.0f, true);
//
//		std::cout << "a + b = c:" << std::endl;
//		auto c = a + b;
//		a.log();
//
//		std::cout << "b - a = d:" << std::endl;
//		auto d = b - a;
//		d.log();
//
//		std::cout << "a * 2 = e:" << std::endl;
//		auto e = a * 2;
//		e.log();
//
//		std::cout << "a / 2 = f:" << std::endl;
//		auto f = a / 2;
//		f.log();
//	}
//
//	{
//		std::cout << "\n3. Rotate vector [1, 0, 0, 1] 90 deg around axis Y.\n";
//		math::vec4 a(1.0f, 0.0f, 0.0f, 1.0f);
//		std::cout << "a: " << a << std::endl;
//		auto M = math::rotation_matrix_y_deg(90.0f);
//		std::cout << "M rotation matrix: \n";
//		M.log();
//		auto b = math::transformed(M, a);
//		std::cout << "M * a = b: " << b << std::endl;	
//	}
//
//	{
//		std::cout << "\n4. Proove that matrix multiplication is no commutative\n";
//		math::mat4x4 A(
//			1, 2, 3, 4,
//			4, 5, 6, 7,
//			1, 2, 3, 4,
//			4, 5, 6, 7
//		);
//		math::mat4x4 B(
//			4, 5, 6, 7,
//			1, 2, 3, 4,
//			4, 5, 6, 7,
//			1, 2, 3, 4
//			);
//		std::cout << "A: \n";
//		A.log();
//		std::cout << "B: \n";
//		B.log();
//		auto C = math::matmul(A, B);
//		auto D = math::matmul(B, A);
//		std::cout << "A * B = C: \n";
//		C.log();
//		std::cout << "B * A = D:\n";
//		D.log();
//	}
//
//	{
//		std::cout << "\n5. Quaternion basic operations\n";
//		math::quat a(1.0f, 2.0f, 3.0f, 4.0f);
//		math::quat b(1.0f, 2.0f, 3.0f, 4.0f);
//		math::quat c = a + b;
//		math::quat d = c - a;
//		std::cout << "a: " << a << std::endl;
//		std::cout << "b: " << b << std::endl;
//		std::cout << "a + b = c: " << c << std::endl;
//		std::cout << "c - a = d: " << d << std::endl;
//		math::quat e(1.0f, 1.0f, 1.0f, 0.0f);
//		math::quat f(1.0f, 0.0f, 1.0f, 0.0f);
//		auto g = e * f;
//		std::cout << "e: " << e << std::endl;
//		std::cout << "f: " << f << std::endl;
//		std::cout << "e * f = g: " << g << std::endl;
//	}
//}

void render(rendering::Camera* camera, rendering::PixelBuffer* buffer, const primitives::geometry& geometry)
{
	const auto [w, h] = camera->GetDimensions();
	const auto pixel_width = w / static_cast<float>(buffer->Width());
	const auto pixel_height = h / static_cast<float>(buffer->Height());
	const auto start_x = -w * 0.5f + pixel_width * 0.5f;
	const auto start_y = h * 0.5f - pixel_height * 0.5f;
	const std::int32_t width  = static_cast<std::int32_t>(buffer->Width());
	const std::int32_t height = static_cast<std::int32_t>(buffer->Height());

	const rendering::color4 color(255, 0, 0, 255);

	for (std::int32_t y = 0; y < height; y++)
	{
		for (std::int32_t x = 0; x < width; x++)
		{
			auto& pixel = buffer->GetPixel(x, y);

			const float fx = start_x + static_cast<float>(x) * pixel_width;
			const float fy = start_y - static_cast<float>(y) * pixel_height;

			math::Point pixel_position = camera->GetPixelPosition(fx, fy);

			math::vec3 ray_dir = (pixel_position - camera->position_);
			intersections::Ray ray(camera->position_, ray_dir);

			intersections::IntersectionResult result;

			std::visit
			(
				[&result, &ray](auto& primitive)
				{
					result = primitive.Intersect(ray, 1000);
				},
				geometry
			);

			if (result.type == intersections::IntersectionType::MISS)
			{
				continue;
			}

			pixel = color;
		}
	}
}

int main(int argc, char** argv)
{
	//Photorealistic1stLab();
	
	rendering::Camera cam;

	primitives::Sphere sphere(math::vec3(0.0f, 0.0f, 11.0f), 2.0f);

	rendering::PixelBuffer buffer(1920, 1080);
	buffer.ColorClear(rendering::color4(0, 0, 0, 255));
	
	render(&cam, &buffer, sphere);
	
	buffer.SaveColorToFile("test.bmp");
	return 0;
}