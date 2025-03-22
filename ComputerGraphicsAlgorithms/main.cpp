#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif // !STB_IMAGE_WRITE_IMPLEMENTATION

#include "PixelBuffer.h"

int main(int argv, char** argc)
{
    PixelBuffer buffers(1920, 1080);
    buffers.ColorClear(color4(222, 121, 255, 255));
    buffers.SaveColorToFile("image.bmp");
    return 0;
}