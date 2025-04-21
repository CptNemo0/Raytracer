#include "Triangle.h"
#include <iostream>

Triangle::Triangle(const Triangle& other)
{
	std::copy(other.vertices.begin(), other.vertices.end(), vertices.begin());
}

Triangle& Triangle::operator=(const Triangle& other)
{
	std::copy(other.vertices.begin(), other.vertices.end(), vertices.begin());
	return *this;
}