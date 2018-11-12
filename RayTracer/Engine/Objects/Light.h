#pragma once
#include "../../Utils/Types.h"

namespace RayTracer
{
struct Light
{
    vec3 position_  = vec3(0, 1000, 0);
    //vec3 direction_ = vec3(0, -1, 0);
    vec3 color_     = vec3(1.f);
};
}  // namespace RayTracer
