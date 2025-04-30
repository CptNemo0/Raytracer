#ifndef TEXTURE
#define TEXTURE

#include "aliasing.h"
#include "raytracer_math.h"
#include <vector>
#include <string_view>

namespace rtr
{
	class Texture
	{
	private:
		const color3f default_color_ = color3f(125.0f, 125.0f, 125.0f);

		color3* buffer_ = nullptr;
		
		int width_ = 0;
		int height_ = 0;

	public:
		Texture() = default;
		Texture(std::string_view path);
		~Texture();
		void Load(std::string_view path);
		color3f Sample(const math::vec2 uv) const;
	};
}

#endif // !TEXTURE

