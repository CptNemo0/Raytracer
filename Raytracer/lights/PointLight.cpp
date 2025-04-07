#include "../lights/PointLight.h"

rendering::color3 lights::PointLight::getDiffuse(math::vec3 cameraPosition, intersections::IntersectionResult intersectionInfo)
{
    return rendering::color3();
}

rendering::color3 lights::PointLight::getSpecular(math::vec3 cameraPosition, intersections::IntersectionResult intersectionInfo)
{
    return rendering::color3();
}

bool lights::PointLight::isInShadow(intersections::IntersectionResult intersectionInfo, primitives::geometry& geometry)
{
    return false;
}
