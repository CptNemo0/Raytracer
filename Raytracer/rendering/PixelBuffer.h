#ifndef RENDERING_PIXEL_BUFFER_H
#define RENDERING_PIXEL_BUFFER_H

#include <cstdint>
#include <vec.h>
#include <string_view>

namespace rendering
{
	using byte = std::uint8_t;
	using color4 = math::vec<4, byte>;
	using color4f = math::vec<4, float>;
	using color3 = math::vec<3, byte>;

	inline color4f operator*(const color4f& lhs, const color4f& rhs) {
		return color4f(lhs.get(0) * rhs.get(0), lhs.get(1) * rhs.get(1), lhs.get(2) * rhs.get(2), lhs.get(3) * rhs.get(3));
	}

	class PixelBuffer
	{
	private:
		std::uint32_t height_;
		std::uint32_t width_;
		std::uint32_t length_;
		std::uint32_t color_buffer_size_;
		std::uint32_t depth_buffer_size_;

		color4* color_buffer_;
		float* depth_buffer_;

	public:
		PixelBuffer(std::uint32_t width, std::uint32_t height);
		~PixelBuffer();
		void Resize(std::uint32_t height, std::uint32_t width);
		void ColorClear(const color4& c);
		void DepthClear(const float d);
		void ClearBuffers(const color4& c, const float d);
 
		std::uint32_t Height() const;
		std::uint32_t Width() const;
		color4* ColorBuffer();
		float* DepthBuffer();

		void SaveColorToFile(const char* filename) const;
		std::uint32_t xy_to_index(const std::uint32_t x, const std::uint32_t y) const;
		color4& GetPixel(const std::uint32_t x, const std::uint32_t y);
		math::vec4 GetPixelf(const std::uint32_t x, const std::uint32_t y) const;
		void SetPixel(const std::uint32_t x, const std::uint32_t y, const color4& color);
		void SetPixelf(const std::uint32_t x, const std::uint32_t y, const math::vec4& color);
		void AddPixelf(const std::uint32_t x, const std::uint32_t y, const math::vec4& color);
	};
}

#endif // !RENDERING_PIXEL_BUFFER_H
