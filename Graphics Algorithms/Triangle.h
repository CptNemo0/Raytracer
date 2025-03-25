class Triangle
{

public:
    Triangle(const math::vec<2, float>& v0, const math::vec<2, float>& v1, const math::vec<2, float>& v2)
    {
        auto isClockwise = [](const math::vec<2, float>& a, const math::vec<2, float>& b, const math::vec<2, float>& c) {
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
        }
    }
	
	bool isLeft(const math::vec<2, float>& x1, const math::vec<2, float>& y1, const math::vec<2, float>& x2, const math::vec<2, float>& y2) const
	{
		return (y1[1] - y2[1]) * x1[0] + (x2[0] - x1[0]) * y1[1] + (x1[1] - y1[1]) * x2[0] > 0;
	}

    void drawTriangle(buffer::ColorBuffer& buffer, const Color4 color) 
    {
		for (int i = 0; i < buffer.GetWidth(); i++)
		{
			for (int j = 0; j < buffer.GetHeight(); j++)
			{
				math::vec<2, float> p = { i, j };
				if (isLeft(v0_, v1_, v2_, p) && isLeft(v1_, v2_, v0_, p) && isLeft(v2_, v0_, v1_, p))
				{
					buffer.SetColor(i, j, color);
				}
			}
		}
	}

private:
	math::vec<2, float> v0_;
	math::vec<2, float> v1_;
	math::vec<2, float> v2_;
};
