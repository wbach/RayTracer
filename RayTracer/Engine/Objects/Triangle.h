#pragma once
#include "BaseObject.h"
#include "Material.h"
#include "Transform.h"

namespace RayTracer
{
class Triangle : public BaseObject
{
public:
    Triangle(const vec3& v1, const vec3& v2, const vec3& v3);
    Triangle(const vec3& v1, const vec3& v2, const vec3& v3, const vec3& normal);
    virtual float intersect(const Ray& ray) const final;
    virtual void calculateNormal(const vec3& intersectPoint) final;

private:
    vec3 calcualteFlatNormal() const;

private:
    vec3 v1_;
    vec3 v2_;
    vec3 v3_;
    bool useCustomNormal;
    bool useSmoothNormal;
};
}  // namespace RayTracer
