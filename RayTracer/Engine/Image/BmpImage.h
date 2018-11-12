#pragma once
#include "IImage.h"
#include <vector>

namespace RayTracer
{
class BmpImage : public IImage
{
public:
    BmpImage();
    BmpImage(const vec2ui& size, uint8 channelCount);
    virtual void init(const vec2ui& size, uint8 channelCount) final;
    virtual void save(const std::string& filename) const final;
    virtual void setPixel(const vec2ui& position, const vec3ui8& color) final;
    virtual const vec2ui& getSize() const final;

private:
    vec2ui size_;
	uint8 channelCount_;
    std::vector<uint8> data_;
};
}  // namespace RayTracer
