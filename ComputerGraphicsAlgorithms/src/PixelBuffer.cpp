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

	void PixelBuffer::ColorClear(const color4& c)
	{
		for (std::uint32_t i = 0; i < length_; i++)
		{
			color_buffer_[i] = c;
		}
	}

	void PixelBuffer::ColorClear(color4&& c)
	{
		for (std::uint32_t i = 0; i < length_; i++)
		{
			color_buffer_[i] = c;
		}
	}

	void PixelBuffer::ColorfClear(const color4f& c)
	{
		color4 colori = color4(c.get(0), c.get(1), c.get(2), c.get(3));
		std::fill(color_buffer_.begin(), color_buffer_.end(), colori);
	}

	void PixelBuffer::DepthClear(const float d)
	{
		std::fill(depth_buffer_.begin(), depth_buffer_.end(), d);
	}

	void PixelBuffer::ClearBuffers(const color4& c, float d)
	{
		std::fill(color_buffer_.begin(), color_buffer_.end(), c);
		std::fill(depth_buffer_.begin(), depth_buffer_.end(), d);
	}

	std::uint32_t PixelBuffer::Height() const
	{
		return height_;
	}

	std::uint32_t PixelBuffer::Width() const
	{
		return width_;
	}

	std::vector<color4>& PixelBuffer::ColorBuffer()
	{
		return color_buffer_;
	}

	std::vector<float>& PixelBuffer::DepthBuffer()
	{
		return depth_buffer_;
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

