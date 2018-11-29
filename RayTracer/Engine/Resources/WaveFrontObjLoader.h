#pragma once
#include "../../Utils/Types.h"
#include "../Objects/Triangle.h"
#include <vector>

namespace RayTracer
{
class WaveFrontObjLoader
{
public:
    std::vector<Triangle> loadMesh(const std::string& filename);

private:
    struct TriangleData
    {
        vec3ui indexes_[3];
    };

private:
    std::vector<vec3> vertexes_;
    std::vector<vec3> normals_;
    std::vector<vec2> uvs_;
    std::vector<TriangleData> triangleIndexes_;
};
}  // namespace RayTracer
