#include "Types.h"

std::string wb::to_string(const vec2i & v)
{
	return std::to_string(v.x) + " " + std::to_string(v.y);
}

std::string wb::to_string(const vec3i & v)
{
	return std::to_string(v.x) + " " + std::to_string(v.y) + " " + std::to_string(v.z);
}

vec3ui8 convertColor(const vec3& color)
{
    //auto normalized = glm::normalize(color);

    auto r = static_cast<uint8>(color.x * 255.f);
    auto g = static_cast<uint8>(color.y * 255.f);
    auto b = static_cast<uint8>(color.z * 255.f);

    return vec3ui8(r, g, b);
}
