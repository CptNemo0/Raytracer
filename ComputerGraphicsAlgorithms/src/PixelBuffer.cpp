#include "PixelBuffer.h"

namespace rtr
{
	PixelBuffer::PixelBuffer(std::uint32_t width, std::uint32_t height)
	{
		Resize(width, height);
	}

	PixelBuffer::~PixelBuffer()
	{

	}

	void PixelBuffer::Resize(std::uint32_t width, std::uint32_t height)
	{
		height_ = height;
		width_ = width;

		length_ = height_ * width_;

		color_buffer_size_ = length_ * sizeof(color4);
		depth_buffer_size_ = length_ * sizeof(float);

		color_buffer_.resize(length_);
		depth_buffer_.resize(length_);
	}

	void PixelBuffer::SaveColorToFile(const char* filename) const
	{
		color4* data = const_cast<color4*>(&(color_buffer_.data()[0]));
		stbi_write_bmp
		(
			filename,
			width_,
			height_,
			4,
			static_cast<void*>(data)
		);
	}

	bool PixelBuffer::DepthCheck(const std::uint32_t x, const std::uint32_t y, float depth) const
	{
		return depth_buffer_[xy_to_index(x, y)] > depth + 0.000001f;
	}

	bool PixelBuffer::DepthCheckExchange(const std::uint32_t x, const std::uint32_t y, float depth)
	{
		if (depth_buffer_[xy_to_index(x, y)] > depth)
		{
			depth_buffer_[xy_to_index(x, y)] = depth;
			return true;
		}
		return false;
	}
}

