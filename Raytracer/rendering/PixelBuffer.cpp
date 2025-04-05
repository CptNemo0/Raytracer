#include "PixelBuffer.h"
#include "stb_image_write.h"
namespace rendering
{
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
		auto result = stbi_write_bmp(
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

	math::vec4 PixelBuffer::GetPixelf(const std::uint32_t x, const std::uint32_t y) const
	{
		auto& c = color_buffer_[xy_to_index(x, y)];
		math::vec4 rv;
		rv[0] = c.get(0);
		rv[1] = c.get(1);
		rv[2] = c.get(2);
		rv[3] = c.get(3);
		return rv;
	}
	void PixelBuffer::SetPixel(const std::uint32_t x, const std::uint32_t y, const color4& color)
	{
		color_buffer_[xy_to_index(x, y)] = color;
	}

	void PixelBuffer::SetPixelf(const std::uint32_t x, const std::uint32_t y, const math::vec4& color)
	{
		auto& c = color_buffer_[xy_to_index(x, y)];

		c[0] = static_cast<byte>(color.get(0));
		c[1] = static_cast<byte>(color.get(1));
		c[2] = static_cast<byte>(color.get(2));
		c[3] = static_cast<byte>(color.get(3));
	}

	void PixelBuffer::AddPixelf(const std::uint32_t x, const std::uint32_t y, const math::vec4& color)
	{
		auto& c = color_buffer_[xy_to_index(x, y)];

		c[0] += static_cast<byte>(color.get(0));
		c[1] += static_cast<byte>(color.get(1));
		c[2] += static_cast<byte>(color.get(2));
		c[3] += static_cast<byte>(color.get(3));
	}
}