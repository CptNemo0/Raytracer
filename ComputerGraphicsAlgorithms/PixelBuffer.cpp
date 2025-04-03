#include "PixelBuffer.h"

PixelBuffer::PixelBuffer(std::uint32_t width, std::uint32_t height)
{
	Resize(width, height);
}

PixelBuffer::~PixelBuffer()
{
	if (color_buffer_) free(color_buffer_);
	if (depth_buffer_) free(depth_buffer_);
}

void PixelBuffer::Resize(std::uint32_t width, std::uint32_t height)
{
	if (color_buffer_) free(color_buffer_);
	if (depth_buffer_) free(depth_buffer_);

	height_ = height;
	width_ = width;

	length_ = height_ * width_;

	color_buffer_size_ = length_ * sizeof(color4);
	depth_buffer_size_ = length_ * sizeof(float);

	color_buffer_ = static_cast<color4*>(malloc(color_buffer_size_));
	depth_buffer_ = static_cast<float*>(malloc(depth_buffer_size_));
}

void PixelBuffer::ColorClear(const color4& c)
{
	for (std::uint32_t i = 0; i < length_; i++)
	{
		color_buffer_[i] = c;
	}
}

void PixelBuffer::DepthClear(const float d)
{
	for (std::uint32_t i = 0; i < length_; i++)
	{
		depth_buffer_[i] = d;
	}
}

void PixelBuffer::ClearBuffers(const color4& c, float d)
{
	for (std::uint32_t i = 0; i < length_; i++)
	{
		color_buffer_[i] = c;
		depth_buffer_[i] = d;
	}
}

std::uint32_t PixelBuffer::Height() const
{
	return height_;
}

std::uint32_t PixelBuffer::Width() const
{
	return width_;
}

color4* PixelBuffer::ColorBuffer()
{
	return color_buffer_;
}

float* PixelBuffer::DepthBuffer()
{
	return depth_buffer_;
}

void PixelBuffer::SaveColorToFile(const char* filename) const
{
	stbi_write_bmp
	(
		filename,
		width_,
		height_,
		4,
		static_cast<void*>(color_buffer_)
	);
}


std::uint32_t PixelBuffer::xy_to_index(const std::uint32_t x, const std::uint32_t y) const
{
	return width_ * y + x;
}

color4& PixelBuffer::GetPixel(const std::uint32_t x, const std::uint32_t y)
{
	return color_buffer_[xy_to_index(x, y)];
}

void PixelBuffer::SetPixelf(const std::uint32_t x, const std::uint32_t y, const color4f& colorf)
{
	auto& colori = color_buffer_[xy_to_index(x, y)];
	colori[0] = static_cast<byte>(colorf.get(0));
	colori[1] = static_cast<byte>(colorf.get(1));
	colori[2] = static_cast<byte>(colorf.get(2));
	colori[3] = static_cast<byte>(colorf.get(3));
}
