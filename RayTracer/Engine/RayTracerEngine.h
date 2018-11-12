#pragma once
#include <memory>
#include <utility>
#include "../Utils/Types.h"

namespace RayTracer
{
class Ray;
class IImage;
class IObject;
struct Light;
struct Scene;
class Intersection;


class RayTracerEngine
{
public:
    RayTracerEngine(const Scene&);
    ~RayTracerEngine();

private:
    void run();
    vec3 trace(const Ray& ray, float& energy, const IObject* parent = nullptr);
    Intersection findIntersection(const Ray& ray, const IObject* parent) const;
    vec3 calculateColor(const Ray& ray, const Intersection& intersection, float energy);
    vec3 procesLight(const Ray& ray, const Light& light, const vec3& intersectionPoint, const vec3& normal,
                     const IObject* obj);
    bool isShadow(const Ray& ray) const;
    void limtColorValue(vec3& color) const;

private:
    const Scene& scene_;
    std::unique_ptr<IImage> image_;
};
}  // namespace RayTracer
