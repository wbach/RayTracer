#include "Sphere.h"
#include "../Ray.h"

namespace RayTracer
{
Sphere::Sphere(float radius)
    : radius_(radius)
{
}
OptionalFloat Sphere::intersect(const Ray& ray) const
{
    const auto& o = ray.getPosition();
    const auto& d = glm::normalize(ray.getDirection());
    const auto& c = transform_.position_;
    auto v = o - c;

    float A = glm::dot(d, d);
    float B = 2.f * glm::dot(v, d);
    float C = glm::dot(v, v) - radius_ * radius_;

    float t0 = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);
    float t1 = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);

    if (t0 > 0 && t1 > 0)
    {
        if (t0 > t1)
            return t1;
        else
            return t0;
    }

    return OptionalFloat();
}
void Sphere::calculateNormal(const vec3& intersectPoint)
{
    normal_ = glm::normalize(intersectPoint - transform_.position_);
}
}  // namespace RayTracer
