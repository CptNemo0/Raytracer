#pragma once  
//#include "raytracer_math.h"


namespace buffer
{
	class ColorBuffer  
	{  
	public:  
	   ColorBuffer(int width, int height, int colorDepth);  
	   ~ColorBuffer();  

	   void SetPixel(int x, int y, unsigned int color);  
	   unsigned int GetPixel(int x, int y) const;  

	   int GetWidth() const;  
	   int GetHeight() const;  
	   int GetColorDepth() const;  

	private:  
	   int width_;  
	   int height_;  
	   int colorDepth_;  
	   unsigned int* colorBuffer_;  
	};

}

