#ifndef MATH_MAT_OPERATIONS
#define MATH_MAT_OPERATIONS

#include <cstdint>
#include "mat.h"

namespace math
{
	template <std::uint32_t m, std::uint32_t n, std::uint32_t p, typename T>
	requires std::is_arithmetic_v<T>
	inline mat<m, p, T> matmul(const mat<m, n, T>& a, const mat<n, p, T>& b)
	{
		auto _ = a.get(0, 0) + b.get(0, 0);

		mat<m, p, T> return_value;

		for (std::uint32_t i = 0; i < m; i++)
		{
			for (std::uint32_t j = 0; j < p; j++)
			{
				T sum = 0;
				for (std::uint32_t k = 0; k < n; k++)
				{
					sum += a.get(k, i) * b.get(j, k);
				}
				return_value.get(j, i) = sum;
			}
		}

		return return_value;
	}

	template <std::uint32_t S, typename T>
	requires std::is_arithmetic_v<T>
	inline void transpose(mat<S, S, T>& matrix)
	{
		for (std::uint32_t y = 0; y < S; y++)
		{
			for (std::uint32_t x = y + 1; x < S; x++)
			{
				std::swap(matrix.get(x, y), matrix.get(y, x));
			}
		}
	}

	template <std::uint32_t rows, std::uint32_t columns, typename T>
	requires std::is_arithmetic_v<T>
	inline mat<columns, rows, T> transposed(const mat<rows, columns, T>& matrix)
	{
		mat<columns, rows, T> return_value;
		for (std::uint32_t y = 0; y < rows; y++)
		{
			for (std::uint32_t x = 0 ; x < columns; x++)
			{
				return_value.get(y, x) = matrix.get(x, y);
			}
		}
		return return_value;
	}

	inline float det(const mat2x2& mat)
	{
		return mat.get(0, 0) * mat.get(1, 1) - mat.get(0, 1) * mat.get(1, 0);
	}

	inline float det(const mat3x3& mat)
	{
		return mat.get(0) * mat.get(4) * mat.get(8) +
			   mat.get(1) * mat.get(5) * mat.get(6) +
			   mat.get(2) * mat.get(3) * mat.get(7) -
			   mat.get(2) * mat.get(4) * mat.get(6) -
			   mat.get(1) * mat.get(3) * mat.get(8) -
			   mat.get(0) * mat.get(5) * mat.get(7);
	}

    inline float det(const mat4x4& mat)
    {
					// Helper lambda to calculate 3x3 determinant
		auto det3x3 = [](float a1, float a2, float a3, float b1, float b2, float b3, float c1, float c2, float c3) {
			return a1 * (b2 * c3 - b3 * c2) -
				   a2 * (b1 * c3 - b3 * c1) +
				   a3 * (b1 * c2 - b2 * c1);
		};

					// Calculate determinant using cofactor expansion along the first row
		return mat.get(0, 0) * det3x3(mat.get(1, 1), mat.get(1, 2), mat.get(1, 3),
								      mat.get(2, 1), mat.get(2, 2), mat.get(2, 3),
								      mat.get(3, 1), mat.get(3, 2), mat.get(3, 3)) -
			   mat.get(0, 1) * det3x3(mat.get(1, 0), mat.get(1, 2), mat.get(1, 3),
			        mat.get(2, 0), mat.get(2, 2), mat.get(2, 3),
			        mat.get(3, 0), mat.get(3, 2), mat.get(3, 3)) +
			   mat.get(0, 2) * det3x3(mat.get(1, 0), mat.get(1, 1), mat.get(1, 3),
			        mat.get(2, 0), mat.get(2, 1), mat.get(2, 3),
			        mat.get(3, 0), mat.get(3, 1), mat.get(3, 3)) -
			   mat.get(0, 3) * det3x3(mat.get(1, 0), mat.get(1, 1), mat.get(1, 2),
			        mat.get(2, 0), mat.get(2, 1), mat.get(2, 2),
			        mat.get(3, 0), mat.get(3, 1), mat.get(3, 2));
    }

	inline mat4x4 adj(const mat4x4& mat)
	{
		mat4x4 adj_mat;
		for (std::uint32_t i = 0; i < 4; i++)
		{
			for (std::uint32_t j = 0; j < 4; j++)
			{
				mat3x3 sub_mat;
				std::uint32_t sub_i = 0;
				for (std::uint32_t k = 0; k < 4; k++)
				{
					if (k == i) continue;
					std::uint32_t sub_j = 0;
					for (std::uint32_t l = 0; l < 4; l++)
					{
						if (l == j) continue;
						sub_mat.get(sub_i, sub_j) = mat.get(k, l);
						sub_j++;
					}
					sub_i++;
				}
				adj_mat.get(j, i) = ((i + j) % 2 == 0 ? 1 : -1) * det(sub_mat);
			}
		}
		return adj_mat;
	}
}

#endif // !MATH_MAT_OPERATIONS
