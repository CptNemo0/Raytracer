#ifndef MATH_MAT_OPERATIONS
#define MATH_MAT_OPERATIONS

#include <cstdint>
#include "mat.h"

namespace math
{
	template <std::uint32_t m, std::uint32_t n, std::uint32_t p, typename T>
	requires std::is_arithmetic_v<T>
	mat<m, p, T> matmul(const mat<m, n, T>& a, const mat<n, p, T>& b)
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
	void transpose(mat<S, S, T>& matrix)
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
	mat<columns, rows, T> transpose(const mat<rows, columns, T>& matrix)
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
}

#endif // !MATH_MAT_OPERATIONS
