#include "Triangle.h"

namespace RayTracer
{
Triangle::Triangle(const vec3& v1, const vec3& v2, const vec3& v3)
    : v1_(v1)
    , v2_(v2)
    , v3_(v3)
    , useCustomNormal(false)
{
}
Triangle::Triangle(const vec3& v1, const vec3& v2, const vec3& v3, const vec3& normal)
    : v1_(v1)
    , v2_(v2)
    , v3_(v3)
    , useCustomNormal(true)
{
    normal_ = normal;
}
float Triangle::intersect(const Ray& ray) const
{
    return 0.0f;
}
void Triangle::calculateNormal(const vec3& intersectPoint)
{
    if (useCustomNormal)
    {
        return;
    }
}
vec3 Triangle::calcualteFlatNormal() const
{
    vec3 AB     = v2_ - v1_;
    vec3 CB     = v3_ - v2_;
    vec3 normal = glm::cross(AB, CB);
    return normal;
}
}  // namespace RayTracer
