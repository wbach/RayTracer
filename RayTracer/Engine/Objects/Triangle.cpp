#include "../Ray.h"
#include "Triangle.h"

namespace RayTracer
{
namespace
{
float u = 0.f, v = 0.f;
}
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
float Triangle::intersect(const Ray& ray) const
{
    float t =
        -(normal_.x * ray.getPosition().x + normal_.y * ray.getPosition().y + normal_.z * ray.getPosition().z + d_) /
        (normal_.x * ray.getDirection().x + normal_.y * ray.getDirection().y + normal_.z * ray.getDirection().z);
    vec3 point = ray.getPosition() + t * ray.getDirection();
    vec3 v2    = point - v1_;

    vec3 v1 = v2_ - v1_;

    float dot01    = glm::dot(v0_, v1);
    float dot02    = glm::dot(v0_, v2);
    float dot11    = glm::dot(v1, v1);
    float dot12    = glm::dot(v1, v2);
    float invDenom = 1 / (dot00_ * dot11 - dot01 * dot01);

    u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    v = (dot00_ * dot12 - dot01 * dot02) * invDenom;

    if ((u >= 0) && (v >= 0) && (u + v < 1))
    {
        return t;
    }

    return 0.0f;
}
void Triangle::calculateNormal(const vec3& intersectPoint)
{
}

void Triangle::calculateStaticNormal()
{
    if (useCustomNormal)
    {
        return;
    }

    normal_ = useSmoothNormal ? calculateSmoothNormal() : calcualteFlatNormal();

    d_ = -1.f * glm::dot(normal_, v1_);
}

vec3 Triangle::calcualteFlatNormal() const
{
    vec3 AB     = v2_ - v1_;
    vec3 CB     = v3_ - v2_;
    vec3 normal = glm::normalize(glm::cross(AB, CB));
    return normal;
}
vec3 Triangle::calculateSmoothNormal() const
{
    vec3 n;
    float s = u + v;
    n.x     = -((1.0 - s) * v2_.x + v1_.x * u + v3_.x * v);
    n.y     = -((1.0 - s) * v2_.y + v1_.y * u + v3_.y * v);
    n.z     = -((1.0 - s) * v2_.z + v1_.z * u + v3_.z * v);
    n       = glm::normalize(n);
    return n;
}
}  // namespace RayTracer
