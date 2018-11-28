#include "Triangle.h"
#include "../Ray.h"

namespace RayTracer
{
Triangle::Triangle(const vec3& v1, const vec3& v2, const vec3& v3)
    : v1_(v1)
    , v2_(v2)
    , v3_(v3)
    , useCustomNormal(false)
    , useSmoothNormal(false)
{
    calculateStaticNormal();
    v0_    = v3_ - v1_;
    dot00_ = glm::dot(v0_, v0_);
}
Triangle::Triangle(const vec3& v1, const vec3& v2, const vec3& v3, const vec3& normal)
    : v1_(v1)
    , v2_(v2)
    , v3_(v3)
    , useCustomNormal(true)
    , useSmoothNormal(false)
{
    normal_ = normal;
    calculateStaticNormal();
    v0_    = v3_ - v1_;
    dot00_ = glm::dot(v0_, v0_);
}
OptionalFloat Triangle::intersect(const Ray& ray) const
{
    float t =
        -(normal_.x * ray.getPosition().x + normal_.y * ray.getPosition().y + normal_.z * ray.getPosition().z + d_) /
        (normal_.x * ray.getDirection().x + normal_.y * ray.getDirection().y + normal_.z * ray.getDirection().z);

    if (t < 0.001f)
    {
        return OptionalFloat();
    }

    vec3 intersectPoint = ray.getPosition() + t * ray.getDirection();

    const auto& uv = calculateUV(intersectPoint);

    if (isInPlanePointInTriangle(uv))
    {
        return t;
    }

    return OptionalFloat();
}

vec3 Triangle::getNormal(const vec3& intersectPoint) const
{
    if (useCustomNormal || !useSmoothNormal)
    {
        return normal_;
    }

    const auto& uv = calculateUV(intersectPoint);
    return calculateSmoothNormal(uv);
}

bool Triangle::isInPlanePointInTriangle(const vec2& uv) const
{
    return (uv.x >= 0) && (uv.y >= 0) && (uv.x + uv.y < 1);
}

vec2 Triangle::calculateUV(const vec3& intersectPoint) const
{
    vec3 v2 = intersectPoint - v1_;
    vec3 v1 = v2_ - v1_;

    float dot01    = glm::dot(v0_, v1);
    float dot02    = glm::dot(v0_, v2);
    float dot11    = glm::dot(v1, v1);
    float dot12    = glm::dot(v1, v2);
    float invDenom = 1.f / (dot00_ * dot11 - dot01 * dot01);

    vec2 result;
    result.x = (dot11 * dot02 - dot01 * dot12) * invDenom;
    result.y = (dot00_ * dot12 - dot01 * dot02) * invDenom;

    return result;
}

void Triangle::calculateStaticNormal()
{
    if (useCustomNormal)
    {
        return;
    }

    vec3 ab = v2_ - v1_;
    vec3 cb = v3_ - v2_;
    normal_ = glm::normalize(glm::cross(ab, cb));
    d_      = -1.f * glm::dot(normal_, v1_);
}

vec3 Triangle::calculateSmoothNormal(const vec2& uv) const
{
    vec3 n;
    float s = uv.x + uv.y;
    n.x     = -((1.0f - s) * v2_.x + v1_.x * uv.x + v3_.x * uv.y);
    n.y     = -((1.0f - s) * v2_.y + v1_.y * uv.x + v3_.y * uv.y);
    n.z     = -((1.0f - s) * v2_.z + v1_.z * uv.x + v3_.z * uv.y);
    n       = glm::normalize(n);
    return n;
}
}  // namespace RayTracer
