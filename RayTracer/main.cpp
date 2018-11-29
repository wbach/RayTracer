#include "Engine/Resources/WaveFrontObjLoader.h"
#include "ExampleScene.h"
#include <iostream>
#include <unordered_map>

std::unordered_map<char, std::string> getOptions(int argc, char** argv)
{
    if (argc <= 1)
    {
        return {};
    }

    std::unordered_map<char, std::string> result;

    for (int i = 1; i < argc; ++i)
    {
        if ( argv[i][0] == '-' && i + 1 < argc )
        {
            result.insert({argv[i][1], argv[i + 1]});
        }
    }

    return result;
}

void welcomMessage(uint32_t threadsCount, const std::string& outputFileName)
{
    std::cout << "WBach : Rayracer" << std::endl;
    std::cout << "Threads : " << threadsCount << std::endl;
    std::cout << "Output : " << outputFileName << std::endl;
}

int main(int argc, char** argv)
{
    std::string outputFileName = "output";
    uint32_t threadsCount = 4;

    auto arguments = getOptions(argc, argv);

    if (arguments.count('o'))
    {
        outputFileName = arguments.at('o');
    }

    if (arguments.count('t'))
    {
        threadsCount = std::stoi(arguments.at('t'));
    }

    welcomMessage(threadsCount, outputFileName);

    Scene scene;
    createExampleScene(scene);

    WaveFrontObjLoader loader_;
    auto trianglesMesh = loader_.loadMesh("/media/sf_D_DRIVE/m.obj");
    std::cout << "trianglesMesh.size :  " << trianglesMesh.size() << std::endl;
    for (const auto& t : trianglesMesh)
    {
        scene.objects_.emplace_back(new Triangle(t));
    }

    RayTracerEngine rayTracer(scene, threadsCount);

    rayTracer.saveImage(outputFileName);
}
