class Triangle
{

public:
    Triangle(const math::vec<2, float>& v0, const math::vec<2, float>& v1, const math::vec<2, float>& v2)
    {
        auto isClockwise = [](const math::vec<2, float> a, const math::vec<2, float> b, const math::vec<2, float> c) {
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
	
	bool isLeft(const math::vec<2, float>& v1, const math::vec<2, float>& v2, const math::vec<2, float>& p) const
	{
		return (v1[0] - v2[0]) * (p[1] - v1[1]) - (v1[1] - v2[1]) * (p[0] - v1[0]) < 0;
	}

    void drawTriangle(buffer::ColorBuffer& buffer, const Color4 color) 
    {
		for (int i = 0; i < buffer.GetWidth(); i++)
		{
			for (int j = 0; j < buffer.GetHeight(); j++)
			{
				math::vec<2, float> p = { i, j };
				if (isLeft(v0_, v1_, p) && isLeft(v1_, v2_, p) && isLeft(v2_, v0_, p))
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
