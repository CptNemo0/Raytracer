#include <immintrin.h>
#include <iostream>
#include "math/vec.h"
#include "math/mat.h"

int main(int argc, char** argv)
{
	math::vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
	math::vec4 b(5.0f, 6.0f, 7.0f, 8.0f);
	auto c = a + b;
	c += c;

	math::mat4x4 m(1.0f);
	math::mat4x4 n(2.0f);
	m.get(0, 0) = 3.0f;
	auto o = m + n;
	m = o;
	math::mat4x4 p(m);
	math::mat4x4 z{
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
	};
	z.log();
	

	for (std::uint32_t i = 0; i < c.size(); ++i)
	{
		std::cout << c[i] << std::endl;
	}
	
	return 0;
}