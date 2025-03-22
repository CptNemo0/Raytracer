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
			for (std::uint32_t i = 0; i < length; ++i)
			{
				std::copy(other.data_.begin(), other.data_.end(), data_.begin());
			}
		}

		T& operator[](const std::uint32_t index)
		{
#ifdef _DEBUG
			assert(index < length);
#endif
			return data_[index];
		}

		const T& get(std::uint32_t index) const
		{
			return data_[index];
		}

		std::uint32_t size() const
		{
			return data_.size();
		}

		vec& operator=(const vec<length, T>& other)
		{
			for (std::uint32_t i = 0; i < length; ++i)
			{
				std::copy(other.data_.begin(), other.data_.end(), data_.begin());
			}
			return *this;
		}

		vec operator+(const vec<length, T>& other) const
		{
			vec<length, T> result;
			for (std::uint32_t i = 0; i < length; ++i)
			{
				result.data_[i] = data_[i] + other.data_[i];
			}
			return result;
		}

		void operator+=(const vec<length, T>& other)
		{
			for (std::uint32_t i = 0; i < length; ++i)
			{
				data_[i] += other.data_[i];
			}
		}

		vec operator-(const vec<length, T>& other) const
		{
			vec<length, T> result;
			for (std::uint32_t i = 0; i < length; ++i)
			{
				result.data_[i] = data_[i] - other.data_[i];
			}
			return result;
		}

		void operator-=(const vec<length, T>& other)
		{
			for (std::uint32_t i = 0; i < length; ++i)
			{
				data_[i] -= other.data_[i];
			}
		}

		vec operator*(float init) const
		{
			vec<length, T> result;
			for (std::uint32_t i = 0; i < length; ++i)
			{
				result.data_[i] = data_[i] * init;
			}
			return result;
		}

		vec operator/(float num) const
		{
			vec<length, T> result;
			float inverse = 1.0f / num;
			for (std::uint32_t i = 0; i < length; ++i)
			{
				result.data_[i] = data_[i] * inverse;
			}
			return result;
		}

		void operator*=(const float init) 
		{
			for (std::uint32_t i = 0; i < length; ++i)
			{
				data_[i] *= init;
			}
		}

		void operator/=(const float init)
		{
			float inverse = 1.0f / init;

			for (std::uint32_t i = 0; i < length; ++i)
			{
				data_[i] *= inverse;
			}
		}
	
		bool operator==(const vec<length, T>& other)
		{
			auto eps = std::numeric_limits<float>::epsilon();
			const auto eq = [&](float a, float b)
			{
				return fabs(a - b) < eps;
			};

			for (std::uint32_t i = 0; i < length; i++)
			{
				if (!eq(data_[i], other.data_[i])) return false;
			}
			return true;
		}

		bool operator!=(const vec<length, T>& other)
		{
			auto eps = std::numeric_limits<float>::epsilon();
			const auto eq = [&](float a, float b)
			{
				return fabs(a - b) < eps;
			};

			for (std::uint32_t i = 0; i < length; i++)
			{
				if (eq(data_[i], other.data_[i])) return false;
			}
			return true;
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