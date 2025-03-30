#ifndef RENDERING_RENDERER_H
#define RENDERING_RENDERER_H

#include "Camera.h"
#include "PixelBuffer.h"
#include "../primitives/primitives.h"
namespace rendering
{
	class Renderer
	{
	public:
		Renderer() = default;
		Renderer(rendering::Camera* camera, rendering::PixelBuffer* buffer)
			: camera_(camera), buffer_(buffer) {
		}

		void AddGeometry(const primitives::geometry& geometry);
		void RenderScene();

	private:
		Camera* camera_;
		PixelBuffer* buffer_;
		std::vector<primitives::geometry> scene_;

		inline void RenderGeometry(
			const primitives::geometry& geometry,
			std::int32_t width, std::int32_t height,
			float pixel_width, float pixel_height,
			float start_x, float start_y);

	};
}

#endif // RENDERING_RENDERER_H
