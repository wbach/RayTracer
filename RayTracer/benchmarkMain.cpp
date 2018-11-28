#include "ExampleScene.h"
#include <benchmark/benchmark.h>

static void BM_QuadCore(benchmark::State& state)
{
    for(auto _ : state)
    {
        Scene scene;
        createExampleScene(scene);
        RayTracerEngine rayTracer(scene, 4);
    }
}

BENCHMARK(BM_QuadCore);

BENCHMARK_MAIN();