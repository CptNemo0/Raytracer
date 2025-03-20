#include <immintrin.h>
#include <iostream>

#include "vec.h"
#include "transformations.h"

int main(int argc, char** argv)
{
	math::vec4 v(1.0f, 0.0f, 0.0f, 1.0f);
	auto M = math::rotation_matrix_y_deg(90.0f);
	math::transform(M, v);
	std::cout << v << std::endl;
	return 0;
}