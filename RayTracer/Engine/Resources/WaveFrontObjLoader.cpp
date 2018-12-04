#include "WaveFrontObjLoader.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace RayTracer
{
void print(const vec2& v)
{
    std::cout << "x: " << v.x << ", y: " << v.y << std::endl;
}

template <class T>
void print(const T& v)
{
    std::cout << "x: " << v.x << ", y: " << v.y << ", z: " << v.z << std::endl;
}
std::vector<Triangle> WaveFrontObjLoader::loadMesh(const std::string& filename)
{
    std::ifstream infile(filename);

    std::string line;
    while (std::getline(infile, line))
    {
        readLines((line));
    }

    return createTriangles();
}

std::vector<Triangle> WaveFrontObjLoader::createTriangles() const
{
    std::vector<Triangle> result;

    for (const auto& mesh : meshes_)
    {
        for (const auto& data : mesh.triangleIndexes_)
        {
            const auto& v1 = mesh.vertexes_[data.indexes_[0].vertex - 1];
            const auto& v2 = mesh.vertexes_[data.indexes_[1].vertex - 1];
            const auto& v3 = mesh.vertexes_[data.indexes_[2].vertex - 1];

            result.emplace_back(v1, v2, v3);

            if (!mesh.normals_.empty())
            {
                const auto& vn1 = mesh.normals_[data.indexes_[0].normal - 1];
                const auto& vn2 = mesh.normals_[data.indexes_[1].normal - 1];
                const auto& vn3 = mesh.normals_[data.indexes_[2].normal - 1];
                result.back().setVertexNormals(vn1, vn2, vn3);
                result.back().enableSmoothNormals(true);
            }

            if (!mesh.uvs_.empty())
            {
                const auto& vt1 = mesh.uvs_[data.indexes_[0].uv - 1];
                const auto& vt2 = mesh.uvs_[data.indexes_[1].uv - 1];
                const auto& vt3 = mesh.uvs_[data.indexes_[2].uv - 1];
                result.back().setUVs(vt1, vt2, vt3);
                result.back().enableSmoothNormals(true);
            }
        }
    }

    return result;
}

void WaveFrontObjLoader::readMaterialFile(const std::string& filename)
{
}

void WaveFrontObjLoader::readLines(const std::string& line)
{
    std::string prefix;

    std::istringstream iss(line);
    if (!(iss >> prefix))
    {
        return;
    }

    if (prefix[0] == '#')
    {
        // std::cout << "comment: " << line << std::endl;
    }
    else if (prefix == "mtllib")
    {
        meshes_.emplace_back();
        currentMesh_ = &meshes_.back();

        std::string materialFileName;
        if (iss >> materialFileName)
        {
            readMaterialFile(materialFileName);
        }
    }
    else if (prefix == "vt")
    {
        read(currentMesh_->uvs_, iss);
    }
    else if (prefix == "vn")
    {
        read(currentMesh_->normals_, iss);
    }
    else if (prefix == "v")
    {
        read(currentMesh_->vertexes_, iss);
    }
    else if (prefix == "f")
    {
        std::string b;
        getline(iss, b);
        b.erase(0, 1);
        readFace(b);
    }
}

void WaveFrontObjLoader::read(std::vector<vec2>& output, std::istringstream& iss)
{
    vec2 uv;
    if (iss >> uv.x >> uv.y)
    {
        output.push_back(uv);
    }
}

void WaveFrontObjLoader::read(std::vector<vec3>& output, std::istringstream& iss)
{
    vec3 v;
    if (iss >> v.x >> v.y >> v.z)
    {
        output.push_back(v);
    }
}

void WaveFrontObjLoader::readFace(const std::string& line)
{
    auto vertexes = split(line, ' ');

    if (vertexes.size() == 3)
    {
        createTriangle(vertexes);
    }
    else if (vertexes.size() == 4)
    {
        createQuad(vertexes);
    }
}

std::vector<std::string> WaveFrontObjLoader::split(const std::string& str, char c) const
{
    std::stringstream test(str);
    std::string segment;
    std::vector<std::string> seglist;

    while (std::getline(test, segment, c))
    {
        seglist.push_back(segment);
    }

    return seglist;
}

void WaveFrontObjLoader::createTriangle(const std::vector<std::string>& vertexes)
{
    TriangleData triangle;

    uint8_t vertexNumber = 0;
    for (const auto& v : vertexes)
    {
        auto indexes = split(v, '/');

        uint8_t indexNumber = 0;
        for (const auto& index : indexes)
        {
            if (!index.empty())
            {
                if (indexNumber == 0)
                {
                    triangle.indexes_[vertexNumber].vertex = std::stoi(index);
                }
                else if (indexNumber == 1)
                {
                    triangle.indexes_[vertexNumber].uv = std::stoi(index);
                }
                else if (indexNumber == 2)
                {
                    triangle.indexes_[vertexNumber].normal = std::stoi(index);
                }
            }
            ++indexNumber;
        }
        ++vertexNumber;
    }
    currentMesh_->triangleIndexes_.push_back(triangle);
}

void WaveFrontObjLoader::createQuad(const std::vector<std::string>& vertexes)
{
    for (const auto& v : vertexes)
    {
        std::cout << __FUNCTION__ << v << std::endl;
    }
}
}  // namespace RayTracer
