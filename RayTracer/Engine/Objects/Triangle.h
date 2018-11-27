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
    virtual OptionalFloat intersect(const Ray& ray) const final;
    virtual vec3 getNormal(const vec3& intersectPoint) const;

private:
    vec3 calculateSmoothNormal(const vec2& uv) const;
    void calculateStaticNormal();
    vec2 calculateUV(const vec3& intersectPoint) const;
    bool isInPlanePointInTriangle(const vec2& uv) const;

private:
    vec3 v1_;
    vec3 v2_;
    vec3 v3_;
    bool useCustomNormal;
    bool useSmoothNormal;
    float d_;
    float dot00_;
    vec3 v0_;
};
}  // namespace RayTracer
