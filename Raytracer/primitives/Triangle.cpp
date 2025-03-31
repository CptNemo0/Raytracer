#include "Triangle.h"
#include "Plane.h"

namespace primitives
{
	intersections::IntersectionResult Triangle::IntersectImpl(const intersections::Ray& ray, float range) const
	{
        intersections::IntersectionResult result;
        constexpr float epsilon = std::numeric_limits<float>::epsilon();

        const math::vec3 edge1 = vertices[1] - vertices[0];
        const math::vec3 edge2 = vertices[2] - vertices[0];
        const math::vec3 ray_cross_e2 = math::cross(ray.direction_, edge2);
        const float det = math::dot(edge1, ray_cross_e2);

        if (det > -epsilon && det < epsilon) return result;

        const float inv_det = 1.0f / det;
        const math::vec3 s = ray.origin_ - vertices[0];
        const float u = inv_det * math::dot(s, ray_cross_e2);

        if ((u < 0 && fabsf(u) > epsilon) || (u > 1.0f && fabsf(u - 1.0f) > epsilon)) return result;

        const math::vec3 s_cross_e1 = math::cross(s, edge1);
        const float v = inv_det * math::dot(ray.direction_, s_cross_e1);

        if ((v < 0 && abs(v) > epsilon) || (u + v > 1.0f && abs(u + v - 1.0f) > epsilon)) return result;

        const float t = inv_det * dot(edge2, s_cross_e1);

        if (t <= epsilon) return result;

        result.intersection_point = ray.SolveParametricEquation(t);
        result.distance = math::distance(result.intersection_point, ray.origin_);
        result.type = intersections::IntersectionType::HIT;
        result.intersection_normal = normals[0]; 

        return result;
	}
}