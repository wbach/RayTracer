#include "ExampleScene.h"

int main()
{
    Scene scene;
    createExampleScene(scene);
    RayTracerEngine rayTracer(scene, 4);
    rayTracer.saveImage("output.bmp");
}
