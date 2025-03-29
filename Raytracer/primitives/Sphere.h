#pragma once
#include "raytracer_math.h"
#include "vec.h"
#include "ray.h"
#include "geometry.h"


namespace primitives {
	class Sphere : public Geometry
    {  
    public:
       Sphere() {};
       Sphere(const math::vec3& center, float radius) 
           : center_(center), radius_(radius) {}  
     
         
     
       bool Hit(const intersections::Ray& ray, float t_min, float t_max, math::vec3& hitPoint) const
       {
           math::vec3 oc = ray.getOrigin() - center_;
           float a = ray.getDirection().dot(ray.getDirection());
           float b = 2.0f * oc.dot(ray.getDirection());
           float c = oc.dot(oc) - radius_ * radius_;
           float discriminant = b * b - 4 * a * c;

           if (discriminant > 0) {
               float temp = (-b - sqrt(discriminant)) / (2.0f * a);
               if (temp < t_max && temp > t_min) {
                   hitPoint = ray.solveParametricEquation(temp);
                   return true;
               }
               temp = (-b + sqrt(discriminant)) / (2.0f * a);
               if (temp < t_max && temp > t_min) {
                   hitPoint = ray.solveParametricEquation(temp);
                   return true;
               }
           }
           if (discriminant == 0) {
               float temp = (-b / (2.0f * a));
               if (temp < t_max && temp > t_min) {
                   hitPoint = ray.solveParametricEquation(temp);
                   return true;
               }
           }
           return false;
       }

       bool Hit(const intersections::Ray& ray, float t_min, float t_max, math::vec3& hitPoint1, math::vec3& hitPoint2) const
       {
           math::vec3 oc = ray.getOrigin() - center_;
           float a = ray.getDirection().dot(ray.getDirection());
           float b = 2.0f * oc.dot(ray.getDirection());
           float c = oc.dot(oc) - radius_ * radius_;
           float discriminant = b * b - 4 * a * c;


           if (discriminant > 0) {
               float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
               float t2 = (-b + sqrt(discriminant)) / (2.0f * a);

               bool hit = false;
               if (t1 < t_max && t1 > t_min) {
                   hitPoint1 = ray.solveParametricEquation(t1);
                   hit = true;
               }
               if (t2 < t_max && t2 > t_min) {
                   hitPoint2 = ray.solveParametricEquation(t2);
                   hit = true;
               }
               return hit;
           }

           if (discriminant == 0) {
               float t = -b / (2.0f * a);
               if (t < t_max && t > t_min) {
                   hitPoint1 = ray.solveParametricEquation(t);
                   return true;
               }
           }

           return false;
       }

       intersections::IntersectionResult Intersects(const intersections::Ray& ray, float range) const
       {
           return intersections::IntersectionResult();
       }

       const math::vec3& getCenter() const { return center_; }
       float getRadius() const { return radius_; }

	   void setCenter(const math::vec3& center) { center_ = center; }
	   void setRadius(float radius) { radius_ = radius; }

       friend std::ostream& operator<<(std::ostream& os, const Sphere& sphere)
       {
		   os << "Sphere\n("
			   << "Center: " << sphere.center_
			   << "\n, Radius: " << sphere.radius_
			   << ")";
		   return os;
       }

    private:  
       math::vec3 center_;
       float radius_;  

    };

}