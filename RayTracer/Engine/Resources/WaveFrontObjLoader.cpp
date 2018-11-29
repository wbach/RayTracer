#include "WaveFrontObjLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

namespace RayTracer
{
void print(const vec2& v)
{
  std::cout << "x: " << v.x << ", y: " << v.y << std::endl;
}

template<class T>
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
        std::istringstream iss(line);
        std::string prefix; float a, b, c;
        if (iss >> prefix)
        { 
            if (prefix[0] == '#')
            {
                //std::cout << "comment: " << line << std::endl;
            }
            else if (prefix == "vt")
            {
                vec2 uv;
                if (!(iss >> uv.x >> uv.y))
                {
                    continue;
                }
                uvs_.push_back(uv);
            }
            else if (prefix == "vn")
            {
                vec3 normal;
                if (!(iss >> normal.x >> normal.y >> normal.z))
                {
                    continue;
                }
                normals_.push_back(normal);
            }
            else if (prefix == "v")
            {
                vec3 vertex;
                if (!(iss >> vertex.x >> vertex.y >> vertex.z))
                {
                    continue;
                }
                vertexes_.push_back(vertex);
            }
            else if (prefix == "f")
            {
                std::replace(line.begin(), line.end(), '/', ' ');
                line.erase(0, 2);
                
                std::istringstream iss2(line);
                TriangleData data;
                for (int i = 0; i < 3; ++i)
                {
                    if ((iss2 >> data.indexes_[i].x >> data.indexes_[i].y >> data.indexes_[i].z))
                    {
 
                    }
                }
                triangleIndexes_.push_back(data);
            }
         }
    }

    std::vector<Triangle> result;
    std::cout << "triangleIndexes_.size :  " << triangleIndexes_.size() << std::endl; 
    for (const auto& data : triangleIndexes_)
    {
        const auto& v1 = vertexes_[data.indexes_[0].x - 1];
        const auto& v2 = vertexes_[data.indexes_[1].x - 1];
        const auto& v3 = vertexes_[data.indexes_[2].x - 1];
        const auto& normal = normals_[data.indexes_[0].z - 1];
        result.emplace_back(v1, v2, v3, normal);
    }

    return result;
}
}  // namespace RayTracer