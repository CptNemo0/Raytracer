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
	template <std::uint32_t S, typename T>
	requires std::is_arithmetic_v<T>
	inline mat<S, S, T> inverse(const mat<S, S, T>& matrix)
	{
		mat<S, S, T> result;
		mat<S, S * 2, T> augmented;

		for (std::uint32_t i = 0; i < S; i++)
		{
			for (std::uint32_t j = 0; j < S; j++)
			{
				augmented.get(j, i) = matrix.get(j, i);
				augmented.get(j + S, i) = (i == j) ? 1 : 0;
			}
		}

		for (std::uint32_t i = 0; i < S; i++)
		{
			T diag = augmented.get(i, i);
			if (diag == 0)
				throw std::runtime_error("Matrix is singular and cannot be inverted.");

			for (std::uint32_t j = 0; j < S * 2; j++)
			{
				augmented.get(j, i) /= diag;
			}

			for (std::uint32_t k = 0; k < S; k++)
			{
				if (k == i) continue;

				T factor = augmented.get(i, k);
				for (std::uint32_t j = 0; j < S * 2; j++)
				{
					augmented.get(j, k) -= factor * augmented.get(j, i);
				}
			}
		}

		for (std::uint32_t i = 0; i < S; i++)
		{
			for (std::uint32_t j = 0; j < S; j++)
			{
				result.get(j, i) = augmented.get(j + S, i);
			}
		}

		return result;
	}
}

#endif // !MATH_MAT_OPERATIONS
