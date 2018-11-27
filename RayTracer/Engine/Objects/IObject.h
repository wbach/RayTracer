#pragma once
#include "../../Utils/Types.h"
#include "../../Utils/optional.hpp"

namespace RayTracer
{
class Ray;
class Image;
struct Transform;
struct Material;

typedef wb::optional<float> OptionalFloat;

class IObject
{
public:
    virtual ~IObject()
    {
    }
    virtual uint32 getId() const                             = 0;
    virtual void setTransform(const Transform& pos)          = 0;
    virtual OptionalFloat intersect(const Ray& ray) const    = 0;
    virtual void calculateNormal(const vec3& intersectPoint) = 0;
    virtual const vec3& getNormal() const                    = 0;
    virtual const Material& getMaterial() const              = 0;
    virtual void setMaterial(const Material&)                = 0;
    // virtual const vec3& imageMap(const Ray&, const vec3& point, const Image& img) = 0;
    // virtual const Image& getTexture(int id) const                                 = 0;
    // virtual bool checkTexture() const                                             = 0;
};
}  // namespace RayTracer
