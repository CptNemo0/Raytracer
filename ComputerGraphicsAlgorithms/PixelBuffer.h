#ifndef PIXEL_BUFFER_H
#define PIXEL_BUFFER_H

#include "stb_image_write.h"

#include <cstdint>
#include <vec.h>
#include <string_view>

using byte = std::uint8_t;
using color4 = math::vec<4, byte>;
using color3 = math::vec<3, byte>;

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
};

#endif // !PIXEL_BUFFER_H
