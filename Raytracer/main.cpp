#include <immintrin.h>
#include <iostream>
#include "math/vec.h"


int main(int argc, char** argv)
{
	math::vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
	math::vec4 b(5.0f, 6.0f, 7.0f, 8.0f);
	auto c = a + b;

	for (std::uint32_t i = 0; i < c.size(); ++i)
	{
		std::cout << c[i] << std::endl;
	}

	return 0;
}