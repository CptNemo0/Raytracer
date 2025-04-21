#ifndef PIXEL_BUFFER_H
#define PIXEL_BUFFER_H

#include "stb_image_write.h"

#include <cstdint>
#include <vec.h>
#include <string_view>
#include <vector>

#include "aliasing.h"

namespace rtr
{
	class PixelBuffer
	{
	private:
		std::uint32_t height_;
		std::uint32_t width_;
		std::uint32_t length_;
		std::uint32_t color_buffer_size_;
		std::uint32_t depth_buffer_size_;

		std::vector<color4> color_buffer_;
		std::vector<float> depth_buffer_;

	public:

		PixelBuffer(std::uint32_t width, std::uint32_t height);
		~PixelBuffer();
		void Resize(std::uint32_t height, std::uint32_t width);
		void ColorClear(const color4& c);
		void ColorClear(color4&& c);
		void ColorfClear(const color4f& c);
		void DepthClear(const float d);
		void ClearBuffers(const color4& c, const float d);

		std::uint32_t Height() const;
		std::uint32_t Width() const;
		std::vector<color4>& ColorBuffer();
		std::vector<float>& DepthBuffer();

		void SaveColorToFile(const char* filename) const;
		std::uint32_t xy_to_index(const std::uint32_t x, const std::uint32_t y) const;
		color4& GetPixel(const std::uint32_t x, const std::uint32_t y);
		void SetPixelf(const std::uint32_t x, const std::uint32_t y, const color4f& color);
		bool DepthCheck(const std::uint32_t x, const std::uint32_t y, float depth) const;
		bool DepthCheckExchange(const std::uint32_t x, const std::uint32_t y, float depth);
	};
}



#endif // !PIXEL_BUFFER_H
