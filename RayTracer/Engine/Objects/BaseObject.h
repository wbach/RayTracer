#pragma once
#include "IObject.h"
#include "Material.h"
#include "Transform.h"

namespace RayTracer
{
class BaseObject : public IObject
{
public:
    BaseObject();
    virtual void setTransform(const Transform& transform) final;
    virtual const vec3& getNormal() const final;
    virtual const Material& getMaterial() const;
    virtual uint32 getId() const;
    virtual void setMaterial(const Material&);
    virtual vec3 getNormal(const vec3& intersectPoint) const;

protected:
    Material material_;
    Transform transform_;
    vec3 normal_;
    uint32 id_;
    static uint32 sId;
};
}  // namespace RayTracer
