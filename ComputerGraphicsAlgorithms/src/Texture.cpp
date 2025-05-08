#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // !STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include "stb_image.h"
namespace rtr
{
	Texture::Texture(std::string_view path)
	{
		Load(path);
	}
	Texture::~Texture()
	{
		if (buffer_)
		{
			delete buffer_;
		}
	}
	void Texture::Load(std::string_view path)
	{
		auto channels = 0;
		buffer_ = reinterpret_cast<color3*>(stbi_load(path.data(), &width_, &height_, &channels, 0));
	}

	color3f Texture::Sample(const math::vec2 uv) const
	{
		if (!buffer_) return default_color_;
		
		const auto x = static_cast<int>(std::clamp(0.0f, uv.get(0) * static_cast<float>(width_), static_cast<float>(width_)));
		const auto y = static_cast<int>(std::clamp(0.0f, uv.get(1) * static_cast<float>(height_), static_cast<float>(height_)));

		const auto index = (y * width_ + x) % (width_ * height_);

		auto color_b = buffer_[index];

		color3f color_float = color3f(static_cast<float>(color_b[0]), 
							          static_cast<float>(color_b[1]),
							          static_cast<float>(color_b[2]));

		return color_float;
	}
}