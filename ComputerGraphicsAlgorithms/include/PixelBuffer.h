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

		PixelBuffer(const std::uint32_t width, const std::uint32_t height);
		~PixelBuffer();
		
		inline void ColorClear(const color4& c)
		{
			std::fill(color_buffer_.begin(), color_buffer_.end(), c);
		}
		inline void ColorClear(color4&& c)
		{
			std::fill(color_buffer_.begin(), color_buffer_.end(), c);
		}
		inline void ColorfClear(const color4f& c)
		{
			color4 colori = color4(c.get(0), c.get(1), c.get(2), c.get(3));
			std::fill(color_buffer_.begin(), color_buffer_.end(), colori);
		}
		inline void DepthClear(const float d)
		{
			std::fill(depth_buffer_.begin(), depth_buffer_.end(), d);
		}
		inline void ClearBuffers(const color4& c, const float d)
		{
			std::fill(color_buffer_.begin(), color_buffer_.end(), c);
			std::fill(depth_buffer_.begin(), depth_buffer_.end(), d);
		}

		inline std::uint32_t Height()
		{
			return height_;
		};
		inline std::uint32_t Width()
		{
			return width_;
		}
		inline std::vector<color4>& ColorBuffer()
		{
			return color_buffer_;
		}
		inline std::vector<float>& DepthBuffer()
		{
			return depth_buffer_;
		}

		
		inline std::uint32_t xy_to_index(const std::uint32_t x, const std::uint32_t y) const
		{
			return width_ * y + x;
		}
		inline color4& GetPixel(const std::uint32_t x, const std::uint32_t y)
		{
			return color_buffer_[xy_to_index(x, y)];
		}
		inline void SetPixelf(const std::uint32_t x, const std::uint32_t y, const color4f& colorf)
		{
			auto& colori = color_buffer_[xy_to_index(x, y)];
			colori[0] = static_cast<byte>(colorf.get(0));
			colori[1] = static_cast<byte>(colorf.get(1));
			colori[2] = static_cast<byte>(colorf.get(2));
			colori[3] = static_cast<byte>(colorf.get(3));
		}
		bool DepthCheck(const std::uint32_t x, const std::uint32_t y, float depth) const;
		bool DepthCheckExchange(const std::uint32_t x, const std::uint32_t y, float depth);
	
		void Resize(const std::uint32_t height, const std::uint32_t width);
		void SaveColorToFile(const char* filename) const;
	};
}



#endif // !PIXEL_BUFFER_H
