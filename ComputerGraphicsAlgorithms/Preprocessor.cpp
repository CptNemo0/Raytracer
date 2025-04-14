#include "Preprocessor.h"

math::vec3 Preprocessor::Local2World(const math::vec3& position) const
{
    auto position4 = math::vec4(position.get(0), position.get(1), position.get(2), 1.0f);
    math::transform(model_matrix_, position4);
    return math::vec3(position4.get(0), position4.get(1), position4.get(2));
}

math::vec3 Preprocessor::World2View(const math::vec3& position) const
{
    auto position4 = math::vec4(position.get(0), position.get(1), position.get(2), 1.0f);
    math::transform(view_matrix_, position4);
    return math::vec3(position4.get(0), position4.get(1), position4.get(2));
}

math::vec3 Preprocessor::View2Screen(const math::vec3& position) const
{
    auto position4 = math::vec4(position.get(0), position.get(1), position.get(2), 1.0f);
    math::transform(projection_matrix_, position4);
    return math::vec3(position4.get(0), position4.get(1), position4.get(2));
}

math::vec3 Preprocessor::Local2Sceen(const math::vec3& position) const
{
    auto position4 = math::vec4(position.get(0), position.get(1), position.get(2), 1.0f);
    math::transform(model_matrix_, position4);
    math::transform(view_matrix_, position4);
    math::transform(projection_matrix_, position4);

    position4[0] = (position4[0] + 1.0f) * width_ * 0.5f;
    position4[1] = (position4[1] + 1.0f) * height_ * 0.5f;

    return math::vec3(position4.get(0), position4.get(1), position4.get(2));
}

void Preprocessor::TriangleLocal2Screen(Triangle& triangle) const
{
    triangle.vertices[0].position = Local2Sceen(triangle.vertices[0].position);
    triangle.vertices[1].position = Local2Sceen(triangle.vertices[1].position);
    triangle.vertices[2].position = Local2Sceen(triangle.vertices[2].position);
}
