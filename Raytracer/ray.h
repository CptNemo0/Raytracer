#pragma once
#include "math/vec.h"

namespace itersections 
{
	class Ray
	{
	public:
		Ray() : origin_(), direction_(), destination_(), distance_(0.0f) {}

		Ray(const math::vec3& origin, const math::vec3& direction)
			: origin_(origin), direction_(direction), destination_(), distance_(0.0f) {
		}

		
        Ray(const math::vec3& origin, float distance)
           : origin_(origin), direction_(), destination_(origin), distance_(distance) {
        }
		Ray(const math::vec3& origin, const math::vec3& direction, float distance)
			: origin_(origin), direction_(direction), destination_(origin + direction * distance), distance_(distance) {
		}
		~Ray() {};

		const math::vec3& getOrigin() const { return origin_; }
		const math::vec3& getDirection() const { return direction_; }
		const math::vec3& getDestination() const { return destination_; }
		float getDistance() const { return distance_; }

		void setOrigin(const math::vec3& origin) { origin_ = origin; }
		void setDirection(const math::vec3& direction) { direction_ = direction; }
		void setDestination(const math::vec3& destination) { destination_ = destination; }
		void setDistance(float distance) { distance_ = distance; }


	private:
		math::vec3 origin_;
		math::vec3 direction_;
		math::vec3 destination_;
		float distance_;
	};
}