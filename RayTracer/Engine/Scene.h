#pragma once
#include "../Utils/Types.h"
#include "Objects/IObject.h"
#include "Objects/Light.h"
#include "Camera.h"
#include <vector>

namespace RayTracer
{
struct Scene
{
    vec3 bgColor_;
    std::vector<Light> lights_;
    std::unique_ptr<Camera> camera_;
    std::vector<std::unique_ptr<IObject>> objects_;
};
}  // namespace RayTracer
