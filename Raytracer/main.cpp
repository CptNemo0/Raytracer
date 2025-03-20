#include <immintrin.h>
#include <iostream>

#include "math/vec.h"
#include "math/mat.h"
#include "math/mat_operations.h"
#include "math/vec_operations.h"
#include "math/transformations.h"

int main(int argc, char** argv)
{
	math::vec4 v(1.0f, 0.0f, 0.0f, 1.0f);
	math::mat4x4 M = math::rotation_matrix_y(math::pid2);
	auto z = math::transformed(M, v);
	std::cout << z << std::endl;
	return 0;
}