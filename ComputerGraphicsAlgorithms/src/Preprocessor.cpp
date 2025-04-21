#include "Preprocessor.h"

namespace rtr
{
    math::vec3 Preprocessor::Local2World(const math::vec3& position_) const
    {
        auto position4 = math::vec4(position_.get(0), position_.get(1), position_.get(2), 1.0f);
        math::transform(model_matrix_, position4);
        return math::vec3(position4.get(0), position4.get(1), position4.get(2));
    }

    math::vec3 Preprocessor::World2View(const math::vec3& position_) const
    {
        auto position4 = math::vec4(position_.get(0), position_.get(1), position_.get(2), 1.0f);
        math::transform(view_matrix_, position4);
        return math::vec3(position4.get(0), position4.get(1), position4.get(2));
    }

    math::vec3 Preprocessor::View2Screen(const math::vec3& position_) const
    {
        auto position4 = math::vec4(position_.get(0), position_.get(1), position_.get(2), 1.0f);
        math::transform(projection_matrix_, position4);
        return math::vec3(position4.get(0), position4.get(1), position4.get(2));
    }

    math::vec3 Preprocessor::Local2Sceen(const math::vec3& position_) const
    {
        auto position4 = math::vec4(position_.get(0), position_.get(1), position_.get(2), 1.0f);
        math::transform(model_matrix_, position4);
        math::transform(view_matrix_, position4);
        math::transform(projection_matrix_, position4);

        position4 /= position4.get(3);

        position4[0] = (position4[0] + 1.0f) * width_ * 0.5f;
        position4[1] = (position4[1] + 1.0f) * height_ * 0.5f;

        return math::vec3(position4.get(0), position4.get(1), position4.get(2));
    }

    void Preprocessor::TriangleLocal2Screen(Triangle& triangle) const
    {
        triangle.vertices_[0].position_ = Local2Sceen(triangle.vertices_[0].position_);
        triangle.vertices_[1].position_ = Local2Sceen(triangle.vertices_[1].position_);
        triangle.vertices_[2].position_ = Local2Sceen(triangle.vertices_[2].position_);
    }
}


