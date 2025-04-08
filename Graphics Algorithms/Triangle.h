#include "raytracer_math.h"

class Triangle
{

public:
    Triangle(const math::vec2& v0, const math::vec2& v1, const math::vec2& v2)
    {
        /*auto isClockwise = [](const math::vec2 a, const math::vec2 b, const math::vec2 c) {
            return (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0]) > 0;
        };

        if (isClockwise(v0, v1, v2)) {
            v0_ = v0;
            v1_ = v1;
            v2_ = v2;
        } else {
            v0_ = v0;
            v1_ = v2;
            v2_ = v1;
		}*/

		v0_ = v0;
		v1_ = v1;
		v2_ = v2;
    }
	
	bool isLeft(const math::vec2& v1, const math::vec2& v2, const math::vec2& p) const
	{
		return (v1[0] - v2[0]) * (p[1] - v1[1]) - (v1[1] - v2[1]) * (p[0] - v1[0]) < 0;
	}

    void drawTriangle(buffer::ColorBuffer& buffer, const Color4 color) 
    {
		int minx = std::min({ v0_[0], v1_[0], v2_[0] });
		int maxx = std::max({ v0_[0], v1_[0], v2_[0] });
		int miny = std::min({ v0_[1], v1_[1], v2_[1] });
		int maxy = std::max({ v0_[1], v1_[1], v2_[1] });

		minx = std::max(minx, 0);
		maxx = std::min(maxx, buffer.GetWidth() - 1);
		miny = std::max(miny, 0);
		maxy = std::min(maxy, buffer.GetHeight() - 1);


		for (int i = minx; i <= maxx; i++) {

			for (int j = miny; j <= maxy; j++)
			{
				math::vec2 p = { i, j };
				if (isLeft(v0_, v1_, p) && isLeft(v1_, v2_, p) && isLeft(v2_, v0_, p))
				{
					buffer.SetColor(i, j, color);
				}
			}
		}
	}

private:
	math::vec2 v0_;
	math::vec2 v1_;
	math::vec2 v2_;
};
