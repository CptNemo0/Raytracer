#ifndef LIGHT_H
#define LIGHT_H

#include "vec.h"
#include "VertexProcessor.h"
#include "Vertex.h"

struct Fragment
{
    math::vec3 position;
    math::vec3 normal;
};

class Light
{
public:
    math::vec3 ambient;
    math::vec3 diffuse;
    math::vec3 specular;
    float shininess;

    Light(const math::vec3& ambient, const math::vec3& diffuse, const math::vec3& specular, float shininess)
        : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
    {
    }

    virtual math::vec3 calculate(const Fragment& fragment) const = 0;
};

#endif // !LIGHT_H