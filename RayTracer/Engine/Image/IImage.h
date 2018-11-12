#pragma once
#include <vector>
#include "../../Utils/Types.h"

namespace RayTracer
{
class IImage
{
public:
    virtual ~IImage()
    {
    }
    virtual void init(const vec2ui& size, uint8 channelCount)           = 0;
    virtual void save(const std::string& filename) const                = 0;
    virtual void setPixel(const vec2ui& position, const vec3ui8& color) = 0;
    virtual const vec2ui& getSize() const                               = 0;
};
}  // namespace RayTracer
