#pragma once

#include "math/vec.h"
#include "ray.h"


namespace primitives {
    class Sphere  
    {  
    public:
       Sphere() {};
       Sphere(const math::vec3& center, float radius) 
           : center_(center), radius_(radius) {}  
     
         
     
       bool Hit(const intersections::Ray& ray, float t_min, float t_max) const
       {
           math::vec3 oc = ray.getOrigin() - center_;
           float a = ray.getDirection().dot(ray.getDirection());
           float b = 2.0f * oc.dot(ray.getDirection());
           float c = oc.dot(oc) - radius_ * radius_;
           float discriminant = b * b - 4 * a * c;

           if (discriminant > 0) {
               float temp = (-b - sqrt(discriminant)) / (2.0f * a);
               if (temp < t_max && temp > t_min) {
                   return true;
               }
               temp = (-b + sqrt(discriminant)) / (2.0f * a);
               if (temp < t_max && temp > t_min) {
                   return true;
               }
           }
           return false;
       }

       const math::vec3& getCenter() const { return center_; }
       float getRadius() const { return radius_; }

	   void setCenter(const math::vec3& center) { center_ = center; }
	   void setRadius(float radius) { radius_ = radius; }

       friend std::ostream& operator<<(std::ostream& os, const Sphere& sphere)
       {
		   os << "Sphere("
			   << "Center: " << sphere.center_
			   << ", Radius: " << sphere.radius_
			   << ")";
		   return os;
       }

    private:  
       math::vec3 center_;
       float radius_;  
    };

}