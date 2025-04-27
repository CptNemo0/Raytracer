#include "Preprocessor.h"

namespace rtr
{
    void Preprocessor::Local2World(math::vec3& position_) const
    {
        auto position4 = math::vec4(position_.get(0), position_.get(1), position_.get(2), 1.0f);
        math::transform(model_matrix_, position4);
		position_[0] = position4.get(0);
		position_[1] = position4.get(1);
		position_[2] = position4.get(2);
    }

    void Preprocessor::World2View(math::vec3& position_) const
    {
        auto position4 = math::vec4(position_.get(0), position_.get(1), position_.get(2), 1.0f);
        math::transform(view_matrix_, position4);
        position_[0] = position4.get(0);
        position_[1] = position4.get(1);
        position_[2] = position4.get(2);
    }

    void Preprocessor::View2Screen(math::vec3& position_) const
    {
        auto position4 = math::vec4(position_.get(0), position_.get(1), position_.get(2), 1.0f);
        math::transform(projection_matrix_, position4);
        position_[0] = position4.get(0);
        position_[1] = position4.get(1);
        position_[2] = position4.get(2);
    }

    void Preprocessor::Local2Screen(math::vec3& position_) const
    {
        auto position4 = math::vec4(position_.get(0), position_.get(1), position_.get(2), 1.0f);
        math::transform(model_matrix_, position4);
        math::transform(view_matrix_, position4);
        math::transform(projection_matrix_, position4);

        position4 /= position4.get(3);

        position4[0] = static_cast<float>(static_cast<int>((position4[0] + 1.0f) * width_ * 0.5f));
        position4[1] = static_cast<float>(static_cast<int>((position4[1] + 1.0f) * height_ * 0.5f));

        position_[0] = position4.get(0);
        position_[1] = position4.get(1);
        position_[2] = position4.get(2);
    }

    void Preprocessor::TriangleLocal2World(mesh::Triangle& triangle) const
    {
        Local2World(triangle.vertices_[0].position_);
        Local2World(triangle.vertices_[1].position_);
        Local2World(triangle.vertices_[2].position_);
    }

    void Preprocessor::TriangleWorld2View(mesh::Triangle& triangle) const
    {
        World2View(triangle.vertices_[0].position_);
        World2View(triangle.vertices_[1].position_);
        World2View(triangle.vertices_[2].position_);
    }

	void Preprocessor::TriangleView2Screen(mesh::Triangle& triangle) const
	{
		View2Screen(triangle.vertices_[0].position_);
		View2Screen(triangle.vertices_[1].position_);
		View2Screen(triangle.vertices_[2].position_);
	}

    void Preprocessor::TriangleLocal2Screen(mesh::Triangle& triangle) const
    {
        Local2Screen(triangle.vertices_[0].position_);
        Local2Screen(triangle.vertices_[1].position_);
        Local2Screen(triangle.vertices_[2].position_);
    }

    math::vec3 Preprocessor::FixNormal(const math::vec3& normal) const
    {
		auto normal4 = math::vec4(normal.get(0), normal.get(1), normal.get(2), 1.0f);
		math::transform(ti_model_matrix, normal4);
        normal4[3] = 0.0f;
        math::normalize(normal4);
		return math::vec3(normal4.get(0), normal4.get(1), normal4.get(2));
    }
}


