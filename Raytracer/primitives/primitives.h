#ifndef PRIMITIVES_PRIMITIVES_H
#define PRIMITIVES_PRIMITIVES_H

#include <variant>
#include <vector>
#include "Geometry.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"

namespace primitives
{
	using geometry = std::variant<Plane, Sphere, Triangle>;
}

#endif // !PRIMITIVES_PRIMITIVES_H