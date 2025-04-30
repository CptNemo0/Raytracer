#ifndef MIX_COLOR_H
#define MIX_COLOR_H

#include "aliasing.h"

namespace rtr
{
	color3f mix_color(const color3f& a, const color3f& b)
	{
		return a * 0.5f + b * 0.5f;
	}
}

#endif // !MIX_COLOR_H
