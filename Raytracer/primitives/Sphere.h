#pragma once

#include "Geometry.h"
#include "../intersections/Ray.h"
#include "raytracer_math.h"

namespace primitives 
{
	class Sphere : public Geometry<Sphere>
    {  
    public:
        friend Geometry;

        math::vec3 center_ = math::vec3(0.0f);
        float radius_ = 1.0f;

        Sphere() = default;
        Sphere(const math::vec3& center, float radius) : center_(center), radius_(radius) {}
             
        //bool Hit(const intersections::Ray& ray, float t_min, float t_max, math::vec3& hitPoint) const
        //{
        //    const math::vec3 oc = ray.origin_ - center_;
        //    const float a = math::dot(ray.direction_, ray.direction_);
        //    const float b = 2.0f * math::dot(oc, ray.direction_);
        //    const float c = math::dot(oc, oc) - radius_ * radius_;
        //    const float discriminant = b * b - 4 * a * c;
        //    const float discriminant_sqrt = sqrtf(discriminant);
        //    const float inv_2a = 1.0f / 2.0f * a;
        //
        //    if (discriminant > 0) 
        //    {
        //        float temp = (-b - discriminant_sqrt) / inv_2a;
        //        if (temp < t_max && temp > t_min) 
        //        {
        //            hitPoint = ray.SolveParametricEquation(temp);
        //            return true;
        //        }
        //        temp = (-b + discriminant_sqrt) / inv_2a;
        //        if (temp < t_max && temp > t_min) 
        //        {
        //            hitPoint = ray.SolveParametricEquation(temp);
        //            return true;
        //        }
        //    }
        //    if (discriminant == 0) 
        //    {
        //        float temp = (-b / inv_2a);
        //        if (temp < t_max && temp > t_min) 
        //        {
        //            hitPoint = ray.SolveParametricEquation(temp);
        //            return true;
        //        }
        //    }
        //    return false;
        //}
        //
        //bool Hit(const intersections::Ray& ray, float t_min, float t_max, math::vec3& hitPoint1, math::vec3& hitPoint2) const
        //{
        //    const math::vec3 oc = ray.origin_ - center_;
        //    const float a = math::dot(ray.direction_, ray.direction_);
        //    const float b = 2.0f * math::dot(oc, ray.direction_);
        //    const float c = math::dot(oc, oc) - radius_ * radius_;
        //    const float discriminant = b * b - 4 * a * c;
        //    const float discriminant_sqrt = sqrtf(discriminant);
        //    const float inv_2a = 1.0f / 2.0f * a;
        //
        //
        //    if (discriminant > 0) {
        //        float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
        //        float t2 = (-b + sqrt(discriminant)) / (2.0f * a);
        //
        //        bool hit = false;
        //        if (t1 < t_max && t1 > t_min) {
        //            hitPoint1 = ray.SolveParametricEquation(t1);
        //            hit = true;
        //        }
        //        if (t2 < t_max && t2 > t_min) {
        //            hitPoint2 = ray.SolveParametricEquation(t2);
        //            hit = true;
        //        }
        //        return hit;
        //    }
        //
        //    if (discriminant == 0) {
        //        float t = -b / (2.0f * a);
        //        if (t < t_max && t > t_min) {
        //            hitPoint1 = ray.SolveParametricEquation(t);
        //            return true;
        //        }
        //    }
        //
        //    return false;
        //}

        friend std::ostream& operator<<(std::ostream& os, const Sphere& sphere)
        {
		    os << "Sphere:\n"
               << "{\n"
			   << "\tCenter: "   << sphere.center_
			   << "\n\tRadius: " << sphere.radius_
			   << "\n}";
            return os;
        }

    private:
        intersections::IntersectionResult IntersectImpl(const intersections::Ray& ray, float range) const;
    };
}