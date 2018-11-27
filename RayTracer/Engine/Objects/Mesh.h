#pragma once
#include "Triangle.h"
#include <vector>

namespace RayTracer
{
class Mesh : public BaseObject
{
public:
    Mesh();
    Mesh(const std::vector<Triangle>& triangles);
    virtual OptionalFloat intersect(const Ray& ray) const final;
    virtual void calculateNormal(const vec3& intersectPoint) final;
    void addTriangle(const Triangle& triangle);

private:
    std::vector<Triangle> triangles_;
};
}  // namespace RayTracer
