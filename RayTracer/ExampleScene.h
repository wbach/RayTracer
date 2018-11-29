#pragma once
#include "Engine/Camera.h"
#include "Engine/Objects/Sphere.h"
#include "Engine/Objects/Triangle.h"
#include "Engine/RayTracerEngine.h"
#include "Engine/Scene.h"

using namespace RayTracer;

static void addObject(IObject *obj, const vec3 &position, const vec3 &ambient, const vec3 &diffuse,
               const vec3 &specular, float shine, bool isReflect)
{
    Material material;
    material.ambient_     = ambient;
    material.diffuse_     = diffuse;
    material.specular_    = specular;
    material.shineDamper_ = shine;
    material.isReflect    = isReflect;

    Transform transform;
    transform.position_ = position;

    obj->setTransform(transform);
    obj->setMaterial(material);
}

static void addSphere(Scene &scene, float radius, const vec3 &position, const vec3 &ambient, const vec3 &diffuse,
               const vec3 &specular, float shine, bool isReflect)
{
    scene.objects_.emplace_back(new Sphere(radius));
    addObject(scene.objects_.back().get(), position, ambient, diffuse, specular, shine, isReflect);
}

static void addTriangle(Scene &scene, const vec3 &v1, const vec3 &v2, const vec3 &v3, const vec3 &position,
                 const vec3 &ambient, const vec3 &diffuse, const vec3 &specular, float shine, bool isReflect)
{
    scene.objects_.emplace_back(new Triangle(v1, v2, v3));
    addObject(scene.objects_.back().get(), position, ambient, diffuse, specular, shine, isReflect);
}

static void addLight(Scene &scene, const vec3 &position, const vec3 &color)
{
    scene.lights_.emplace_back();
    scene.lights_.back().position_ = position;
    scene.lights_.back().color_    = color;
}

static vec3 createFloatRgb(uint8 r, uint8 g, uint8 b)
{
    return vec3(static_cast<float>(r) / 255.f, static_cast<float>(g) / 255.f, static_cast<float>(b) / 255.f);
}

static void createExampleScene(Scene &scene, const vec2ui& viewPort)
{
    addSphere(scene, 2.f, vec3(0), createFloatRgb(3, 3, 3), createFloatRgb(204, 3, 3), createFloatRgb(204, 204, 204),
              20, false);

    addSphere(scene, 1.f, vec3(2.f, 2.f, 1.f), createFloatRgb(3, 3, 3), createFloatRgb(3, 204, 3),
              createFloatRgb(3, 3, 3), 20, false);

    addTriangle(scene, vec3(-5, -4, -5), vec3(-5, -4, 5), vec3(5, -4, 5), vec3(0), createFloatRgb(3, 3, 3),
                createFloatRgb(3, 3, 153), createFloatRgb(3, 3, 3), 1, true);

    addTriangle(scene, vec3(5, -4, 5), vec3(5, -4, -5), vec3(-5, -4, -5), vec3(0), createFloatRgb(3, 3, 3),
                createFloatRgb(3, 3, 153), createFloatRgb(3, 3, 3), 1, true);

    addLight(scene, vec3(-4, 4, -2), createFloatRgb(255, 255, 255));
    addLight(scene, vec3(1, 1, -10), createFloatRgb(255, 255, 255));

    scene.camera_.reset(new Camera(viewPort, 50.f * static_cast<float>(M_PI) / 180, vec3(0, 1, 0),
                                   vec3(0, 0, 0), vec3(3, 15, -16)));
}
