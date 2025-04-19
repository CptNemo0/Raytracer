#ifndef MATH_MAT_H
#define MATH_MAT_H

#include <algorithm>
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <numeric>

namespace math
{
	struct mat_size
	{
		std::uint32_t rows;
		std::uint32_t columns;
	};

	template <std::uint32_t rows, std::uint32_t columns, typename T>
	requires std::is_arithmetic_v<T>
	class mat
	{
	private:
		std::array<T, rows* columns> data_;
		
	public:
		const std::uint32_t rows_ = rows;
		const std::uint32_t columns_ = columns;
		const std::uint32_t length_ = rows * columns;
		const mat_size size_ = { rows, columns };

		std::uint32_t xy_to_index(const std::uint32_t x, const std::uint32_t y) const
		{
			return columns_ * y + x;
		}

		T& get(const std::uint32_t x, const std::uint32_t y)
		{
			return data_[xy_to_index(x, y)];
		}

		const T& get(const std::uint32_t x, const std::uint32_t y) const
		{
			return data_[xy_to_index(x, y)];
		}

		mat() 
		{
			data_.fill(static_cast<T>(0));
		};

		mat(const T init, bool identity = true)
		{
			if (identity) [[likely]]
			{
				data_.fill(static_cast<T>(0));
				for (std::uint32_t i = 0; i < rows_; i++)
				{
					std::uint32_t index = xy_to_index(i, i);
					data_[index] = init;
				}
				return;
			}
			
			data_.fill(init);
		}

		mat(const mat<rows, columns, T>& other)
		{
			std::cout << "Matrix copy constructor\n";
			std::copy(other.data_.begin(), other.data_.end(), data_.begin());
		}

		mat(mat<rows, columns, T>&& other) noexcept
		{
			std::cout << "Matrix move constructor\n";
			std::move(other.data_.begin(), other.data_.end(), data_.begin());
		}

		template<typename... Args>
		mat(Args... args) : data_{ static_cast<T>(args)... } {};

		void log() const
		{
			std::stringstream ss;
			for (std::uint32_t y = 0; y < rows_; y++)
			{
				for (std::uint32_t x = 0; x < columns_; x++)
				{
					std::uint32_t index = xy_to_index(x, y);

					ss << data_[index] << std::setw(4);
				}
				ss << "\n";
			}
			std::cout << ss.str();
		}
	
		mat operator+(const mat<rows, columns, T>& other) const
		{
			mat<rows, columns, T> result;
			for (std::uint32_t i = 0; i < length_; ++i)
			{
				result.data_[i] = data_[i] + other.data_[i];
			}
			return result;
		}

		void operator+=(const mat<rows, columns, T>& other)
		{
			for (std::uint32_t i = 0; i < length_; ++i)
			{
				data_[i] += other.data_[i];
			}
		}

		mat operator-(const mat<rows, columns, T>& other) const
		{
			mat<rows, columns, T> result;
			for (std::uint32_t i = 0; i < length_; ++i)
			{
				result.data_[i] = data_[i] - other.data_[i];
			}
			return result;
		}

		void operator-=(const mat<rows, columns, T>& other)
		{
			for (std::uint32_t i = 0; i < length_; ++i)
			{
				data_[i] -= other.data_[i];
			}
		}

		mat operator*(const T& other) const
		{
			mat<rows, columns, T> result;
			for (std::uint32_t i = 0; i < length_; ++i)
			{
				result.data_[i] = data_[i] * other;
			}
			return result;
		}

		void operator*=(const T& other)
		{
			for (std::uint32_t i = 0; i < length_; ++i)
			{
				data_[i] *= other;
			}
		}
	
		mat operator/(const T& other) const
		{
			mat<rows, columns, T> result;
			T inverse = 1.0f / other;
			for (std::uint32_t i = 0; i < length_; ++i)
			{
				result.data_[i] = data_[i] * inverse;
			}
			return result;
		}

		void operator/=(const T& other)
		{
			T inverse = 1.0f / other;
			for (std::uint32_t i = 0; i < length_; ++i)
			{
				data_[i] *= inverse;
			}
		}
	
		mat& operator=(const mat<rows, columns, T>& other) 
		{
			std::cout << "Matrix copy assignement operator\n";
			std::copy(other.data_.begin(), other.data_.end(), data_.begin());
			return *this;
		}	

		mat& operator=(mat<rows, columns, T>&& other) noexcept
		{
			std::cout << "Matrix move assignement operator\n";
			std::move(other.data_.begin(), other.data_.end(), data_.begin());
			return *this;
		}

		bool operator==(const mat<rows, columns, T>& other)
		{
			const auto eq = [](float a, float b)
			{
				constexpr auto eps = std::numeric_limits<float>::epsilon();
				return fabs(a - b) < eps;
			};

			for (std::uint32_t i = 0; i < length_; i++)
			{
				if (!eq(data_[i], other.data_[i])) return false;
			}
			return true;
		}

		bool operator!=(const mat<rows, columns, T>& other)
		{
			const auto eq = [](float a, float b)
			{
				constexpr auto eps = std::numeric_limits<float>::epsilon();
				return fabs(a - b) < eps;
			};

			for (std::uint32_t i = 0; i < length_; i++)
			{
				if (!eq(data_[i], other.data_[i])) return true;
			}
			return false;
		}
	};

	using mat4x4 = mat<4, 4, float>;
	using mat3x3 = mat<3, 3, float>;
	using mat2x2 = mat<2, 2, float>;
}

#endif // !MATH_MAT_H
