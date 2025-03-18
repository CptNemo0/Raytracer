#ifndef MATH_VEC
#define MATH_VEC

#include <array>
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <type_traits>

namespace math
{
	template <std::uint32_t length, typename T>
	requires std::is_arithmetic_v<T>
	class vec
	{
	private:
		std::uint32_t size_ = length;
	public:
		std::array<T, length> data_;
		
		vec()
		{
			for (std::uint32_t i = 0; i < size_; ++i)
			{
				data_[i] = 0;
			}
		}

		vec(const T init)
		{
			for (std::uint32_t i = 0; i < size_; ++i)
			{
				data_[i] = init;
			}
		}
		
		template<typename... Args>
		vec(Args... args) : data_{ static_cast<T>(args)... } {};

		vec(const vec<length, T>& other)
		{
			for (std::uint32_t i = 0; i < size_; ++i)
			{
				std::copy(other.data_.begin(), other.data_.end(), data_.begin());
			}
		}

		T& operator[](const std::uint32_t index)
		{
#ifdef _DEBUG
			assert(index < size_);
#endif
			return data_[index];
		}

		std::uint32_t size() const
		{
			return size_;
		}

		vec& operator=(const vec<length, T>& other)
		{
			for (std::uint32_t i = 0; i < size_; ++i)
			{
				std::copy(other.data_.begin(), other.data_.end(), data_.begin());
			}
			return *this;
		}

		vec operator+(const vec<length, T>& other)
		{
			vec<length, T> result;
			for (std::uint32_t i = 0; i < size_; ++i)
			{
				result.data_[i] = data_[i] + other.data_[i];
			}
			return result;
		}

		vec operator-(const vec<length, T>& other)
		{
			vec<size, T> result;
			for (std::uint32_t i = 0; i < size_; ++i)
			{
				result.data_[i] = data_[i] - other.data_[i];
			}
			return result;
		}

		vec operator*(const float init)
		{
			for (std::uint32_t i = 0; i < size_; ++i)
			{
				data_[i] *= init;
			}
		}
		
		vec operator/(const float init)
		{
			float inverse = 1.0f / init;

			for (std::uint32_t i = 0; i < size_; ++i)
			{
				data_[i] *= inverse;
			}
		}
	
		void operator+=(const vec<length, T>& other)
		{
			for (std::uint32_t i = 0; i < size_; ++i)
			{
				data_[i] += other.data_[i];
			}
		}

		void operator-=(const vec<length, T>& other)
		{
			for (std::uint32_t i = 0; i < size_; ++i)
			{
				data_[i] -= other.data_[i];
			}
		}
	};

	using vec2 = vec<2, float>;
	using vec3 = vec<3, float>;
	using vec4 = vec<4, float>;

	using ivec2 = vec<2, int32_t>;
	using ivec3 = vec<3, int32_t>;
	using ivec4 = vec<4, int32_t>;

	using uvec2 = vec<2, uint32_t>;
	using uvec3 = vec<3, uint32_t>;
	using uvec4 = vec<4, uint32_t>;
}

#endif // !MATH_VEC