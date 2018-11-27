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
    virtual vec3 getNormal(const vec3& intersectPoint) const;

private:
    float radius_;
};
}  // namespace RayTracer
