#ifndef PRIMITIVES_PRIMITIVES_H
#define PRIMITIVES_PRIMITIVES_H

#include <variant>
#include <vector>
#include "Geometry.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include <memory>
namespace primitives
{
	using geometry = std::variant<Plane, Sphere, Triangle>;
	using geometry_sp = std::variant<std::shared_ptr<Plane>, std::shared_ptr<Sphere>, std::shared_ptr<Triangle>>;
}

#endif // !PRIMITIVES_PRIMITIVES_H