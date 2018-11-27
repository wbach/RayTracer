#include "StepPooler.h"

namespace RayTracer
{
StepPooler::StepPooler(const vec2ui& viewPort)
    : viewPort_(viewPort)
{
}
wb::optional<vec2ui> StepPooler::getNextStep()
{
    vec2ui result;


    if (current_.x < viewPort_.x)
    {
        std::lock_guard<std::mutex> lk(mutex_);
        result.x = current_.x++;
    }
    else
    {
        std::lock_guard<std::mutex> lk(mutex_);
        ++current_.y;
        result.x = current_.x = 0;
    }

    if (current_.y >= viewPort_.y)
    {
        return wb::optional<vec2ui>();
    }

    result.y = current_.y;

    return result;
}
}  // namespace RayTracer
