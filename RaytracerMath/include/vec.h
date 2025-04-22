#ifndef MATH_VEC
#define MATH_VEC

#include <array>
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <numeric>

namespace math
{
	template <std::uint32_t length, typename T>
	requires std::is_arithmetic_v<T>
	class vec
	{
	public:
		std::array<T, length> data_;
		
		vec()
		{
			for (std::uint32_t i = 0; i < length; ++i)
			{
				data_[i] = static_cast<T>(0);
			}
		}

		vec(const T init)
		{
			for (std::uint32_t i = 0; i < length; ++i)
			{
				data_[i] = init;
			}
		}
		
		template<typename... Args>
		vec(Args... args) : data_{ static_cast<T>(args)... } {};

		vec(const vec<length, T>& other)
		{
			std::copy(other.data_.begin(), other.data_.end(), data_.begin());
		}

		vec(vec<length, T>&& other) noexcept
		{
			std::move(other.data_.begin(), other.data_.end(), data_.begin());
		}

		inline constexpr T& operator[](const std::uint32_t index)
		{
			return data_[index];
		}

		inline constexpr const T& get(std::uint32_t index) const
		{
			return data_[index];
		}

		inline vec& operator=(const vec<length, T>& other)
		{
			std::copy(other.data_.begin(), other.data_.end(), data_.begin());
			return *this;
		}

		inline vec& operator=(vec<length, T>&& other) noexcept
		{
			std::move(other.data_.begin(), other.data_.end(), data_.begin());
			return *this;
		}

		inline vec operator+(const vec<length, T>& other) const
		{
			vec<length, T> result;
			for (std::uint32_t i = 0; i < length; ++i)
			{
				result.data_[i] = data_[i] + other.data_[i];
			}
			return result;
		}

		inline void operator+=(const vec<length, T>& other)
		{
			vec<length, T> result;
			for (std::uint32_t i = 0; i < length; ++i)
			{
				data_[i] += other.data_[i];
			}
		}

		inline vec operator-(const vec<length, T>& other) const
		{
			vec<length, T> result;
			for (std::uint32_t i = 0; i < length; ++i)
			{
				result.data_[i] = data_[i] - other.data_[i];
			}
			return result;
		}

		inline void operator-=(const vec<length, T>& other)
		{
			for (std::uint32_t i = 0; i < length; ++i)
			{
				data_[i] -= other.data_[i];
			}
		}

		inline vec operator*(float init) const
		{
			vec<length, T> result;
			for (std::uint32_t i = 0; i < length; ++i)
			{
				result.data_[i] = data_[i] * init;
			}
			return result;
		}

		inline vec operator/(float num) const
		{
			vec<length, T> result;
			float inverse = 1.0f / num;
			for (std::uint32_t i = 0; i < length; ++i)
			{
				result.data_[i] = data_[i] * inverse;
			}
			return result;
		}

		inline void operator*=(const float init)
		{
			for (std::uint32_t i = 0; i < length; ++i)
			{
				data_[i] *= init;
			}
		}

		inline void operator/=(const float init)
		{
			float inverse = 1.0f / init;

			for (std::uint32_t i = 0; i < length; ++i)
			{
				data_[i] *= inverse;
			}
		}
	
		inline bool operator==(const vec<length, T>& other)
		{
			const auto eq = [](float a, float b)
			{
				constexpr auto eps = std::numeric_limits<float>::epsilon();
				return fabs(a - b) < eps;
			};

			for (std::uint32_t i = 0; i < length; i++)
			{
				if (!eq(data_[i], other.data_[i])) return false;
			}
			return true;
		}

		inline bool operator!=(const vec<length, T>& other)
		{
			const auto eq = [](float a, float b)
			{
				constexpr auto eps = std::numeric_limits<float>::epsilon();
				return fabsf(a - b) < eps;
			};

			for (std::uint32_t i = 0; i < length; i++)
			{
				if (!eq(data_[i], other.data_[i])) return true;
			}
			return false;
		}

        T dot(const vec<length, T>& other) const
        {
            T result = 0;
            for (std::uint32_t i = 0; i < length; ++i)
            {
                result += data_[i] * other.data_[i];
            }
            return result;
        }

		friend std::ostream& operator<<(std::ostream& os, const vec<length, T>& v)
        {
            os << "[";
            for (std::uint32_t i = 0; i < length; ++i)
            {
                os << v.data_[i];
                if (i < length - 1)
                {
                    os << ", ";
                }
            }
            os << "]";
            return os;
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

	using Point = vec<3, float>;
}

#endif // !MATH_VEC