#ifndef ALIASING_H
#define ALIASING_H

#include <cstdint>
#include "raytracer_math.h"

using byte = std::uint8_t;
using color4 = math::vec<4, byte>;
using color4f = math::vec<4, float>;
using color3 = math::vec<3, byte>;
using color3f = math::vec<3, float>;

#endif // !ALIASING_H
