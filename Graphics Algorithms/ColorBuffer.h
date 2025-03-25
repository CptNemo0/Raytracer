#pragma once  
#include "raytracer_math.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "third_party/stb_image_write.h"


using Color4 = math::vec<4, uint8_t>;
using Color3 = math::vec<3, uint8_t>;

namespace buffer
{
	class ColorBuffer
	{
	public:
		ColorBuffer(int width, int height)
			: width_(width), height_(height) {};
		ColorBuffer(int width, int height, Color4* color)
			: width_(width), height_(height), colorBuffer_(color) {};
		ColorBuffer(int width, int height, Color4* color, float* colorDepth)
			: width_(width), height_(height), colorBuffer_(color), colorDepth_(colorDepth) {};

		~ColorBuffer();


        void SetWidth(int width) { width_ = width; }
        void SetHeight(int height) { height_ = height; }
        void Resize(int width, int height) { width_ = width; height_ = height; }

        void SetColorDepth(int x, int y, float depth) { colorDepth_[y * width_ + x] = depth; }
        void SetColor(int x, int y, const Color4& color) { colorBuffer_[y * width_ + x] = color; }
		void SetColorBuffer(Color4* color) { colorBuffer_ = color; }
		void SetColorBufferDepth(float* colorDepth) { colorDepth_ = colorDepth; }

        int GetWidth() const { return width_; }
        int GetHeight() const { return height_; }

        float GetColorDepth(int x, int y) const { return colorDepth_[y * width_ + x]; }
        Color4 GetColor(int x, int y) const { return colorBuffer_[y * width_ + x]; }

		Color4* GetColorBuffer() const { return colorBuffer_; }
		float* GetColorBufferDepth() const { return colorDepth_; }

	private:
		int width_;
		int height_;
		float* colorDepth_;
		Color4* colorBuffer_;
	};

};

