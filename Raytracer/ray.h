#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "vec.h"

namespace intersections 
{

	struct IntersectionResult {
		enum Type {
			MISS,              
			HIT,               
			INSIDE_PRIMITIVE   
		};

		Type type;                  
		math::vec3 LPOINT;          
		float distance;             
		math::vec3 intersectionNormal;
	};



	class Ray
	{
	public:
		Ray() : origin_(), direction_(), destination_(), distance_(0.0f) {}

		Ray(const math::vec3& origin, const math::vec3& direction)
			: origin_(origin), direction_(direction), destination_(), distance_(0.0f) {}

		
        Ray(const math::vec3& origin, float distance)
           : origin_(origin), direction_(), destination_(origin), distance_(distance) {}
		Ray(const math::vec3& origin, const math::vec3& direction, float distance)
			: origin_(origin), direction_(direction), destination_(origin + direction * distance), distance_(distance) {}
		~Ray() {};

		math::vec3 solveParametricEquation(float t) const 
		{
		     return origin_ + direction_ * t;
		}

		const math::vec3& getOrigin() const { return origin_; }
		const math::vec3& getDirection() const { return direction_; }
		const math::vec3& getDestination() const { return destination_; }
		float getDistance() const { return distance_; }

		void setOrigin(const math::vec3& origin) { origin_ = origin; }
		void setDirection(const math::vec3& direction) { direction_ = direction; }
		void setDestination(const math::vec3& destination) { destination_ = destination; }
		void setDistance(float distance) { distance_ = distance; }
		
        friend std::ostream& operator<<(std::ostream& os, const Ray& ray) 
		{
            os << "Ray\n(" 
               << "Origin: " << ray.origin_ 
               << ",\nDirection: " << ray.direction_ 
               << ",\nDestination: " << ray.destination_ 
               << ",\nDistance: " << ray.distance_ 
               << ")";
            return os;
        }        

	private:
		math::vec3 origin_;
		math::vec3 direction_;
		math::vec3 destination_;
		float distance_;
	};


}