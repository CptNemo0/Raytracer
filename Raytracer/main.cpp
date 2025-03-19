#include <immintrin.h>
#include <iostream>
#include "math/vec.h"
#include "math/mat.h"
#include "math/mat_operations.h"
#include <chrono>
int main(int argc, char** argv)
{
    math::mat4x4 a (1, 2, 3, 4,
                    1, 2, 3, 4,
                    1, 2, 3, 4,
                    1, 2, 3, 4);
    math::mat4x4 b (1, 2, 3, 4,
                    1, 2, 3, 4,
                    1, 2, 3, 4,
                    1, 2, 3, 4);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto c = math::matmul(a, b);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "matmul took "
        << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
        << " nanoseconds\n";
	return 0;
}