#include "Mesh.h"
#include <memory>

namespace RayTracer
{
Mesh::Mesh()
{

}
Mesh::Mesh(const std::vector<Triangle>& triangles)
: triangles_(triangles)
{

}
void Mesh::addTriangle(const Triangle& triangle)
{
    triangles_.push_back(triangle);
}
OptionalFloat Mesh::intersect(const Ray& ray) const
{
    float t = std::numeric_limits<float>::max();
    bool isIntersection = false;

    for (const auto& triangle : triangles_)
    {
        const auto& intersectionPoint = triangle.intersect(ray);

        if (intersectionPoint)
        {
            if (intersectionPoint.get() < t)
            {
                t = intersectionPoint.get();
                isIntersection = true;
            }
        }
    }

    if (isIntersection)
    {
        return t;
    }

    return OptionalFloat();
}
vec3 Mesh::getNormal(const vec3& intersectPoint) const
{
    return vec3();
}
}  // namespace RayTracer