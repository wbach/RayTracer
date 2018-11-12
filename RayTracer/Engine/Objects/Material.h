#pragma once
#include "../../Utils/Types.h"

namespace RayTracer
{
struct Material
{
    std::string name_;

    vec3 ambient_  = vec3(0);
    vec3 diffuse_  = vec3(0.8);
    vec3 specular_ = vec3(0);

    float shineDamper_ = 0.f;
    bool isReflect     = false;

    float absorption_ = 0.1f;

    // Texture* diffuseTexture  = nullptr;
    // Texture* ambientTexture  = nullptr;
    // Texture* specularTexture = nullptr;
    // Texture* normalTexture   = nullptr;
};
}  // namespace RayTracer
