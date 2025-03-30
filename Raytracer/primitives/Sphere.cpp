#include "Sphere.h"
#include <algorithm>
#include <iostream>

namespace primitives
{
    intersections::IntersectionResult Sphere::IntersectImpl(const intersections::Ray& ray, float range) const
    {
        intersections::IntersectionResult result;
        const auto center_origin = center_ - ray.origin_;
        const auto ray_direction = math::normalized(ray.direction_ - ray.origin_);
        const auto t_ca = ray_direction.dot(center_origin);
        if (t_ca < 0) return result;

       // std::cout << "AA\n";

        const auto d2 = math::dot(center_origin, center_origin) - t_ca * t_ca;
        const auto radius2 = radius_ * radius_;
        if (d2 > radius2) return result;

        //std::cout << "BB\n";
        const auto t_hc = sqrtf(radius2 - d2);

        auto t0 = t_ca - t_hc;
        auto t1 = t_ca + t_hc;

        if (t0 > t1) std::swap(t0, t1);

        if (t0 < 0)
        {
            t0 = t1;
            if (t0 < 0) return result;
        }

        //std::cout << "CC\n";

        const float t = t0;

        result.type = intersections::IntersectionType::HIT;
        result.intersection_point = ray.origin_ + ray_direction * t;
        result.distance = t;
        result.intersection_normal = math::normalized(result.intersection_point - center_);
        return result;
    }
}

