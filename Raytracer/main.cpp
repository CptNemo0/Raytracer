#include <iostream>
#include "raytracer_math.h";

void Photorealistic1stLab()
{
	{
		std::cout << "1 - 2. Basic operations\n";
		math::vec4 a(1, 2, 3, 4);
		math::vec4 b(5, 6, 7, 8);

		std::cout << "a = " << a << std::endl;
		std::cout << "b = " << b << std::endl;
		std::cout << "a + b = " << a + b << std::endl;
		std::cout << "b + a = " << b + a << std::endl;
		std::cout << "a - b = " << a - b << std::endl;
		std::cout << "b - a = " << b - a << std::endl;
		std::cout << "a * 2 = " << a * 2 << std::endl;
		std::cout << "a / 2 = " << a / 2 << std::endl;
	}

	{
		std::cout << "\n3. Find an angle between vectors [0,3,0] a [5,5,0]\n";
		math::vec3 a(0, 3, 0);
		math::vec3 b(5, 5, 0);
		std::cout << "angle_degrees(a, b) = " << math::angle_deg(a, b) << std::endl;
	}
		
	{
		std::cout << "\n4. Find a vector perpendicular to [4,5,1] i [4,1,3]\n";
		math::vec3 a(4, 5, 1);
		math::vec3 b(4, 1, 3);
		math::vec3 c = math::cross(a, b);
		std::cout << "cross(a, b) = c " << c << std::endl;

		std::cout << "\n5. Normalize this vector\n";
		math::normalize(c);
		std::cout << "c: " << c << std::endl;
	}

	std::cout << "\n\nAdditional\n";

	{
		std::cout << "1 - 2. Basic operations\n";
		math::mat4x4 a(2.0f, true);
		math::mat4x4 b(8.0f, true);

		std::cout << "a + b = c:" << std::endl;
		auto c = a + b;
		a.log();

		std::cout << "b - a = d:" << std::endl;
		auto d = b - a;
		d.log();

		std::cout << "a * 2 = e:" << std::endl;
		auto e = a * 2;
		e.log();

		std::cout << "a / 2 = f:" << std::endl;
		auto f = a / 2;
		f.log();
	}

	{
		std::cout << "\n3. Rotate vector [1, 0, 0, 1] 90 deg around axis Y.\n";
		math::vec4 a(1.0f, 0.0f, 0.0f, 1.0f);
		std::cout << "a: " << a << std::endl;
		auto M = math::rotation_matrix_y_deg(90.0f);
		std::cout << "M rotation matrix: \n";
		M.log();
		auto b = math::transformed(M, a);
		std::cout << "M * a = b: " << b << std::endl;	
	}

	{
		std::cout << "\n4. Proove that matrix multiplication is no commutative\n";
		math::mat4x4 A(
			1, 2, 3, 4,
			4, 5, 6, 7,
			1, 2, 3, 4,
			4, 5, 6, 7
		);
		math::mat4x4 B(
			4, 5, 6, 7,
			1, 2, 3, 4,
			4, 5, 6, 7,
			1, 2, 3, 4
			);
		std::cout << "A: \n";
		A.log();
		std::cout << "B: \n";
		B.log();
		auto C = math::matmul(A, B);
		auto D = math::matmul(B, A);
		std::cout << "A * B = C: \n";
		C.log();
		std::cout << "B * A = D:\n";
		D.log();
	}
}

int main(int argc, char** argv)
{
	Photorealistic1stLab();
	return 0;
}