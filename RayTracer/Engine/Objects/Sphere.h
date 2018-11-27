#pragma once
#include "BaseObject.h"
#include "Material.h"
#include "Transform.h"

namespace RayTracer
{
class Sphere : public BaseObject
{
public:
    Sphere(float radius);
    virtual OptionalFloat intersect(const Ray& ray) const final;
    virtual void calculateNormal(const vec3& intersectPoint) final;

private:
    float radius_;
};
}  // namespace RayTracer
