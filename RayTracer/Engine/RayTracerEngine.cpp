#include "Camera.h"
#include "Image/BmpImage.h"
#include "Intersection.h"
#include "Objects/IObject.h"
#include "Objects/Light.h"
#include "Objects/Material.h"
#include "Ray.h"
#include "RayTracerEngine.h"
#include "Scene.h"
#include "StepPooler.h"
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

namespace RayTracer
{
namespace
{
std::unique_ptr<StepPooler> stepPooler;
std::mutex stepMutex_;
}

RayTracerEngine::RayTracerEngine(const Scene &scene, uint32 threadsCount)
    : scene_(scene)
{
    if (scene.camera_ == nullptr || threadsCount <= 0)
    {
        return;
    }
    stepPooler.reset(new StepPooler(scene_.camera_->getViewPort()));

    image_ = std::make_unique<BmpImage>(scene.camera_->getViewPort(), 3);
    multiThreadsRun(threadsCount);
}

RayTracerEngine::~RayTracerEngine()
{
}

void RayTracerEngine::saveImage(const std::string& filename) const
{
    image_->save(filename);
}

void RayTracerEngine::multiThreadsRun(uint32 threadsCount)
{
    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;

    for (uint32 x = 0; x < threadsCount - 1; ++x)
    {
        threads.emplace_back(&RayTracerEngine::run, this);
    }

    run();

    for (auto& thread : threads)
    {
        thread.join();
    }

    std::cout << std::endl;

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::ratio<1,1>> durration = endTime - startTime;

    std::cout << "Time : " << durration.count() << "s." << std::endl;

}

void RayTracerEngine::run()
{
    while (true)
    {
        wb::optional<vec2ui> s;
        {
            std::lock_guard<std::mutex> m(stepMutex_);
            s = stepPooler->getNextStep();
        }

        if (!s)
        {
            break;
        }

        step(s.get().x, s.get().y);
    }
}

void RayTracerEngine::step(uint32 x, uint32 y)
{
    float energy = 1.0f;
    vec3 pixelVector(x, y, 1.0f);
    vec3 dirVector = glm::normalize(pixelVector * scene_.camera_->getMatrix());
    Ray ray(scene_.camera_->getPosition(), dirVector, x, y);
    auto color = trace(ray, energy);
    image_->setPixel(vec2ui(x, y), convertColor(color));
}

vec3 RayTracerEngine::trace(const Ray &ray, float &energy, const IObject *parent)
{
    auto intersection = findIntersection(ray, parent);

    if (!intersection)
    {
        return vec3(0.f);
    }

    auto color = calculateColor(ray, intersection, energy);

    const auto &material = intersection.getObject()->getMaterial();
    energy -= material.absorption_;

    if (energy < 0.1f || !material.isReflect)
    {
        return color;
    }

    const auto &normal         = intersection.getNormal();
    auto reflectedRayDirection = ray.getDirection() - (2.f * ray.getDirection() * normal) * normal;
    Ray reflectedRay(intersection.getPoint(), reflectedRayDirection, ray.getX(), ray.getY());

    auto totalColor = color + trace(reflectedRay, energy, intersection.getObject());
    limtColorValue(totalColor);
    return totalColor;
}
Intersection RayTracerEngine::findIntersection(const Ray &ray, const IObject *parent) const
{
    Intersection result;

    float t = std::numeric_limits<float>::max();

    for (const auto &obj : scene_.objects_)
    {
        if (parent && obj->getId() == parent->getId())
        {
            continue;
        }

        auto intersectionPoint = obj->intersect(ray);

        if (intersectionPoint)
        {
            if (intersectionPoint.get() < t)
            {
                t = intersectionPoint.get();
                result.setObject(obj.get());
            }
        }
    }

    result.calculateIntersectionPointAndObjNormal(ray, t);

    return result;
}
vec3 RayTracerEngine::calculateColor(const Ray &ray, const Intersection &intersection, float energy)
{
    vec3 outputColor = scene_.bgColor_;

    const auto &normal = intersection.getNormal();

    for (const auto &light : scene_.lights_)
    {
        outputColor +=
            procesLight(ray, light, intersection.getPoint(), intersection.getNormal(), intersection.getObject()) * energy;
    }

    limtColorValue(outputColor);
    return outputColor;
}
vec3 RayTracerEngine::procesLight(const Ray &ray, const Light &light, const vec3 &intersectionPoint, const vec3 &normal,
                                  const IObject *obj)
{
    auto lightDirection = glm::normalize(light.position_ - intersectionPoint);
    Ray shadowRay(intersectionPoint, lightDirection, ray.getX(), ray.getY());

    if (isShadow(shadowRay))
    {
        return vec3(0);
    }
    vec3 ambient = obj->getMaterial().ambient_ * light.color_;

    float intensity = glm::dot(normal, lightDirection);

    if (intensity < 0)
    {
        return ambient;
    }

    vec3 r  = 2.f * intensity * normal - lightDirection;
    vec3 v  = glm::normalize(ray.getPosition() - intersectionPoint);
    float s = glm::dot(v, r);

    vec3 diffuse = obj->getMaterial().diffuse_ * intensity;
    vec3 specular(0.f);

    if (s > 0.f && s < 90.f * PI / 180.f)
    {
        specular = obj->getMaterial().specular_ * light.color_ * powf(s, obj->getMaterial().shineDamper_);
    }

    return ambient + diffuse + specular;
}

bool RayTracerEngine::isShadow(const Ray &ray) const
{
    for (const auto &obj : scene_.objects_)
    {
        const auto& intersectionPoint = obj->intersect(ray);

        if (intersectionPoint)
        {
            return true;
        }
    }

    return false;
}
void RayTracerEngine::limtColorValue(vec3 &color) const
{
    if (color.x > 1.f)
    {
        color.x = 1.f;
    }

    if (color.y > 1.f)
    {
        color.y = 1.f;
    }

    if (color.z > 1.f)
    {
        color.z = 1.f;
    }
}
}  // namespace RayTracer
