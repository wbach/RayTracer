#pragma once
#include <vector>
#include "../../Utils/Types.h"
#include "../Objects/Triangle.h"

namespace RayTracer
{
class WaveFrontObjLoader
{
public:
    std::vector<Triangle> loadMesh(const std::string& filename);

private:
    struct FaceIndex
    {
        uint32_t vertex;
        uint32_t uv;
        uint32_t normal;
    };
    struct TriangleData
    {
        FaceIndex indexes_[3];
    };
    struct Mesh
    {
        Material material;
        std::vector<vec3> vertexes_;
        std::vector<vec3> normals_;
        std::vector<vec2> uvs_;
        std::vector<TriangleData> triangleIndexes_;
    };

private:
    std::vector<Triangle> createTriangles() const;
    void readMaterialFile(const std::string& filename);
    void readLines(const std::string& line);
    void read(std::vector<vec2>&, std::istringstream &);
    void read(std::vector<vec3>&, std::istringstream&);
    void readFace(const std::string&);
    std::vector<std::string> split(const std::string&, char) const;
    void createTriangle(const std::vector<std::string>&);
    void createQuad(const std::vector<std::string>&);

private:
    std::vector<Triangle> outputTriangles_;
    std::vector<Mesh> meshes_;
    Mesh* currentMesh_ = nullptr;
};
}  // namespace RayTracer
