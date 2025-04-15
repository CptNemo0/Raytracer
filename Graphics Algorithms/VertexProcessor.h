#ifndef VERTEX_PROCESSOR_H
#define VERTEX_PROCESSOR_H

#include "raytracer_math.h"


class VertexProcessor
{

public:
	math::mat4x4 modelMatrix_;
	math::mat4x4 viewMatrix_;
	math::mat4x4 projectionMatrix_;

	VertexProcessor()
	{
		modelMatrix_ = math::mat4x4(1.0f);
		viewMatrix_ = math::mat4x4(1.0f);
		projectionMatrix_ = math::mat4x4(1.0f);
	};

	math::vec3 LocalToWorld(const math::vec3& local)
	{
		auto pos = math::vec4(local[0], local[1], local[2], 1.0f);
		math::transform(modelMatrix_, pos);
		return { pos[0], pos[1], pos[2] };
	};

	math::vec3 WorldToView(const math::vec3& world)
	{
		auto pos = math::vec4(world[0], world[1], world[2], 1.0f);
		math::transform(viewMatrix_, pos);
		return { pos[0], pos[1], pos[2] };
	};

	math::vec3 ViewToClip(const math::vec3& view)
	{
		auto pos = math::vec4(view[0], view[1], view[2], 1.0f);
		math::transform(projectionMatrix_, pos);
		return { pos[0], pos[1], pos[2] };
	};

	math::vec3 LocalToScreen(const math::vec3& local, float width, float height)
	{
		auto pos = math::vec4(local[0], local[1], local[2], 1.0f);
		math::transform(modelMatrix_, pos);
		math::transform(viewMatrix_, pos);
		math::transform(projectionMatrix_, pos);

		pos[0] = (pos[0] + 1.0f) * 0.5f * width;
		pos[1] = (1.0f - pos[1]) * 0.5f * height;

		return { pos[0], pos[1], pos[2] };
	};


	void TriangleLocal2Screen(const math::vec3& v0, const math::vec3& v1, const math::vec3& v2, float width, float height)
	{
		auto pos0 = LocalToScreen(v0, width, height);
		auto pos1 = LocalToScreen(v1, width, height);
		auto pos2 = LocalToScreen(v2, width, height);
	};

};



#endif // !VERTEX_PROCESSOR_H




