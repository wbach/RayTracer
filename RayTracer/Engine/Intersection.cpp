#include "Intersection.h"
#include "Ray.h"
#include "Objects/IObject.h"

namespace RayTracer
{
Intersection::Intersection()
    : objPtr_(nullptr)
    , isSet_(false)
{
}
void Intersection::calculateIntersectionPointAndObjNormal(const Ray& ray, float t)
{
    if (isSet_)
    {
        point_ = ray.getPosition() + t * ray.getDirection();
        objPtr_->calculateNormal(point_);
    }
}
const IObject* Intersection::getObject() const
{
    return objPtr_;
}
void Intersection::setObject(IObject* ptr)
{
    objPtr_ = ptr;
    isSet_  = true;
}
const vec3& Intersection::getPoint() const
{
    return point_;
}
}  // namespace RayTracer
