#include "Triangle.h"
#include <iostream>

namespace rtr
{
	Triangle::Triangle(const Triangle& other)
	{
		std::copy(other.vertices_.begin(), other.vertices_.end(), vertices_.begin());
	}

	Triangle& Triangle::operator=(const Triangle& other)
	{
		std::copy(other.vertices_.begin(), other.vertices_.end(), vertices_.begin());
		return *this;
	}
}

