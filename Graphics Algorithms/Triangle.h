#include "raytracer_math.h"

class Triangle
{

public:
    Triangle(const math::vec3& v0, const math::vec3& v1, const math::vec3& v2)
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
		color0_ = Color4(255, 0, 0, 255);
		color1_ = Color4(0, 255, 0, 255);
		color2_ = Color4(0, 0, 255, 255);
    }
	
	void SetColors(const Color4& color0, const Color4& color1, const Color4& color2)
	{
		color0_ = color0;
		color1_ = color1;
		color2_ = color2;
	}

	void SetColor0(const Color4& color) { color0_ = color; }
	void SetColor1(const Color4& color) { color1_ = color; }
	void SetColor2(const Color4& color) { color2_ = color; }

	bool isLeft(const math::vec2& v1, const math::vec2& v2, const math::vec2& p) const
	{
		return (v1[0] - v2[0]) * (p[1] - v1[1]) - (v1[1] - v2[1]) * (p[0] - v1[0]) < 0;
	}

	bool isInsideTopLeft(const math::vec2& p) const
	{
		float w0 = (v1_[0] - v0_[0]) * (p[1] - v0_[1]) - (v1_[1] - v0_[1]) * (p[0] - v0_[0]);
		float w1 = (v2_[0] - v1_[0]) * (p[1] - v1_[1]) - (v2_[1] - v1_[1]) * (p[0] - v1_[0]);
		float w2 = (v0_[0] - v2_[0]) * (p[1] - v2_[1]) - (v0_[1] - v2_[1]) * (p[0] - v2_[0]);

		// top-left edges detection
		int dx01 = (int)(v1_[0] - v0_[0]);
		int dy01 = (int)(v1_[1] - v0_[1]);
		int dx12 = (int)(v2_[0] - v1_[0]);
		int dy12 = (int)(v2_[1] - v1_[1]);
		int dx20 = (int)(v0_[0] - v2_[0]);
		int dy20 = (int)(v0_[1] - v2_[1]);

		bool t01 = (dy01 < 0 || (dy01 == 0 && dx01 > 0));
		bool t12 = (dy12 < 0 || (dy12 == 0 && dx12 > 0));
		bool t20 = (dy20 < 0 || (dy20 == 0 && dx20 > 0));

		return
			(w0 > 0 || (w0 == 0 && t01)) &&
			(w1 > 0 || (w1 == 0 && t12)) &&
			(w2 > 0 || (w2 == 0 && t20));
	}

    void drawTriangle(buffer::ColorBuffer& buffer) 
    {
		int minx = std::min({ v0_[0], v1_[0], v2_[0] });
		int maxx = std::max({ v0_[0], v1_[0], v2_[0] });
		int miny = std::min({ v0_[1], v1_[1], v2_[1] });
		int maxy = std::max({ v0_[1], v1_[1], v2_[1] });

		minx = std::max(minx, 0);
		maxx = std::min(maxx, buffer.GetWidth() - 1);
		miny = std::max(miny, 0);
		maxy = std::min(maxy, buffer.GetHeight() - 1);

		int dx12 = (int)(v1_[0] - v0_[0]);
		int dy12 = (int)(v1_[1] - v0_[1]);
		int dx23 = (int)(v2_[0] - v1_[0]);
		int dy23 = (int)(v2_[1] - v1_[1]);
		int dx31 = (int)(v0_[0] - v2_[0]);
		int dy31 = (int)(v0_[1] - v2_[1]);

		//Top-Left
		bool t01 = (dy12 < 0 || (dy12 == 0 && dx12 > 0));
		bool t12 = (dy23 < 0 || (dy23 == 0 && dx23 > 0));
		bool t20 = (dy31 < 0 || (dy31 == 0 && dx31 > 0));



		for (int i = minx; i <= maxx; i++) {

			for (int j = miny; j <= maxy; j++)
			{
				math::vec2 p = { i + 0.5f, j + 0.5f};
				if (isInsideTopLeft(p))
				{
					float denom = (v1_[1] - v2_[1]) * (v0_[0] - v2_[0]) + (v2_[0] - v1_[0]) * (v0_[1] - v2_[1]);
					float lambda1 = ((v1_[1] - v2_[1]) * (p[0] - v2_[0]) + (v2_[0] - v1_[0]) * (p[1] - v2_[1])) / denom;
					float lambda2 = ((v2_[1] - v0_[1]) * (p[0] - v2_[0]) + (v0_[0] - v2_[0]) * (p[1] - v2_[1])) / denom;
					float lambda3 = 1.0f - lambda1 - lambda2;

					float z = lambda1 * v0_[2] + lambda2 * v1_[2] + lambda3 * v2_[2];

					if (z > buffer.GetColorDepth(i, j)) {
						buffer.SetColorDepth(i, j, z);

						Color4 color;
						color[0] = static_cast<unsigned char>(lambda1 * color0_[0] + lambda2 * color1_[0] + lambda3 * color2_[0]);
						color[1] = static_cast<unsigned char>(lambda1 * color0_[1] + lambda2 * color1_[1] + lambda3 * color2_[1]);
						color[2] = static_cast<unsigned char>(lambda1 * color0_[2] + lambda2 * color1_[2] + lambda3 * color2_[2]);
						color[3] = static_cast<unsigned char>(lambda1 * color0_[3] + lambda2 * color1_[3] + lambda3 * color2_[3]);

						buffer.SetColor(i, j, color);
					}
				}
			}
		}
	}

private:
	math::vec3 v0_;
	math::vec3 v1_;
	math::vec3 v2_;



	Color4 color0_;
	Color4 color1_;
	Color4 color2_;
};
