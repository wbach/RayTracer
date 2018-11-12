#pragma once
#include "../Utils/Types.h"

namespace RayTracer
{
class Ray;
class IObject;

class Intersection
{
public:
    Intersection();

    void calculateIntersectionPointAndObjNormal(const Ray& ray, float t);
    const IObject* getObject() const;
    void setObject(IObject* ptr);
    const vec3& getPoint() const;
    operator bool() const
    {
        return isSet_;
    }

private:
    vec3 point_;
    IObject* objPtr_;
    bool isSet_;
};
}  // namespace RayTracer
