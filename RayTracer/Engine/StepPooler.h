#pragma once
#include "../Utils/Types.h"
#include "../Utils/optional.hpp"

namespace RayTracer
{
class StepPooler
{
public:
    StepPooler(const vec2ui& viewPort);
    wb::optional<vec2ui> getNextStep();

private:
    vec2ui viewPort_;
    vec2ui current_;
    uint32_t progress_;
    uint32_t total_;
};
}  // namespace RayTracer
