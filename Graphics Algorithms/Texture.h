#ifndef TEXTURE_H
#define TEXTURE_H

#include "raytracer_math.h"
#include <string>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "third_party/stb_image_write.h"
#include "third_party/stb_image.h"

class Texture
{
public:
    int width = 0, height = 0, channels = 0;
    std::vector<unsigned char> data;

    bool load(const std::string& filename) {
        unsigned char* img = stbi_load(filename.c_str(), &width, &height, &channels, 0);
        if (!img) return false;
        data.assign(img, img + (width * height * channels));
        stbi_image_free(img);
        return true;
    }

    math::vec3 getColor(float u, float v) const {
        if (width == 0 || height == 0) return { 1.0f, 0.0f, 1.0f }; 

        // Wrap UV
        u = fmod(fmod(u, 1.0f) + 1.0f, 1.0f);
        v = fmod(fmod(v, 1.0f) + 1.0f, 1.0f);

        int x = static_cast<int>(u * width);
        int y = static_cast<int>((1.0f - v) * height); // Y odwrócone (OpenGL style)

        int idx = (y * width + x) * channels;
        float r = data[idx] / 255.0f;
        float g = data[idx + 1] / 255.0f;
        float b = data[idx + 2] / 255.0f;
        return { r, g, b };
    }
};

#endif // !TEXTURE_H




