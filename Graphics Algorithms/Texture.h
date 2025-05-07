#ifndef TEXTURE_H
#define TEXTURE_H

#include "raytracer_math.h"
#include <string>
#include <vector>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "third_party/stb_image.h"

class Texture
{
public:
    int width = 0, height = 0, channels = 0;
    std::vector<math::vec3> data;

	Texture() = default;

	Texture(std::string path)
	{
		if (!load(path)) {
			std::cerr << "Failed to load texture: " << path << std::endl;
		}
	}

    bool load(const std::string& filename) {
        unsigned char* img = stbi_load(filename.c_str(), &width, &height, &channels, 0);
        if (!img) return false;

        data.resize(width * height);

        for (int i = 0; i < width * height; ++i) {
            int offset = i * channels;
            float r = img[offset] / 255.0f;
            float g = img[offset + 1] / 255.0f;
            float b = img[offset + 2] / 255.0f;
            data[i] = math::vec3(r, g, b);
        }

        stbi_image_free(img);
        return true;
    }

	math::vec3 Sample(const math::vec2& uv) const {
        if (data.empty()) {
            std::cerr << "[Texture] No texture data loaded.\n";
            return math::vec3(0.0f, 0.0f, 0.0f);
        }

        // Upewnij siê, ¿e uv s¹ w zakresie [0, 1]
        float u = std::clamp(uv[0], 0.0f, 1.0f);
        float v = std::clamp(uv[1], 0.0f, 1.0f);

        // Przekszta³cenie wspó³rzêdnych do zakresu tekstury
        int x = static_cast<int>(u * static_cast<float>(width));
        int y = static_cast<int>((1.0f - v) * static_cast<float>(height));  // flip V

        // Clamp do rozmiarów tekstury (na wszelki wypadek)
        x = std::clamp(x, 0, width - 1);
        y = std::clamp(y, 0, height - 1);

        // Oblicz indeks w buforze
        int index = y * width + x;

        return data[index];
    }
};

#endif // !TEXTURE_H
#endif // !STB_IMAGE_IMPLEMENTATION



