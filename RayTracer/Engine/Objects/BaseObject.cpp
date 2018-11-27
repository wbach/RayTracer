#include "BaseObject.h"

namespace RayTracer
{
uint32 BaseObject::sId = 1;

BaseObject::BaseObject()
{
    id_ = sId++;
}
void BaseObject::setTransform(const Transform& transform)
{
    transform_ = transform;
}
const vec3& BaseObject::getNormal() const
{
    return normal_;
}
const Material& BaseObject::getMaterial() const
{
    return material_;
}
uint32 BaseObject::getId() const
{
    return id_;
}
void BaseObject::setMaterial(const Material& material)
{
    material_ = material;
}
vec3 BaseObject::getNormal(const vec3&) const
{
    return normal_;
}
}  // namespace RayTracer
