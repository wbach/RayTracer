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
    void setVertexNormals(const vec3& vn1, const vec3& vn2, const vec3& vn3);
    void setUVs(const vec2& vt1, const vec2& vt2, const vec2& vt3);
    void enableSmoothNormals(bool);

private:
    vec3 calculateSmoothNormal(const vec2& uv) const;
    vec3 calculateStaticNormal(const vec3& v1, const vec3& v2, const vec3& v3);
    vec2 calculateUV(const vec3& intersectPoint) const;
    bool isInPlanePointInTriangle(const vec2& uv) const;
    void calculateIntersectionConstVariables();

private:
    vec3 v1_;
    vec3 v2_;
    vec3 v3_;
    vec3 vn1_;
    vec3 vn2_;
    vec3 vn3_;
    bool useSmoothNormal_;
    float d_;
    float dot00_;
    vec3 v0_;
};
}  // namespace RayTracer
