project(GameEngineCM)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE RELEASE)

option(BUILD_BENCHMARK "Build benchmark" OFF)
option(BENCHMARK_ENABLE_GTEST_TESTS "Build benchmark test" OFF)

if(BUILD_BENCHMARK)
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../google_benchmark ${CMAKE_CURRENT_BINARY_DIR}/google_benchmark)
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/../Tools/glm/
)

file(GLOB_RECURSE SRCS_ENGINE ${PROJECT_SOURCE_DIR}/../RayTracer/Engine/*.cpp)
file(GLOB_RECURSE SRCS_UTILS ${PROJECT_SOURCE_DIR}/../RayTracer/Utils/*.cpp)

include_directories("./RayTracer/")

add_executable(rayTracerExe ${PROJECT_SOURCE_DIR}/../RayTracer/main.cpp ${SRCS_ENGINE} ${SRCS_UTILS})
set_target_properties(rayTracerExe PROPERTIES COMPILE_FLAGS "-O3" LINK_FLAGS "-static-libgcc -static-libstdc++") #LINK_FLAGS "-m32 -static-libgcc -static-libstdc++"
target_link_libraries(rayTracerExe pthread)

if(BUILD_BENCHMARK)
    add_executable(benchmarkExe ${PROJECT_SOURCE_DIR}/../RayTracer/benchmarkMain.cpp ${SRCS_ENGINE} ${SRCS_UTILS})
    set_target_properties(benchmarkExe PROPERTIES COMPILE_FLAGS "-O3" ) #LINK_FLAGS "-m32"
    target_link_libraries(benchmarkExe pthread benchmark)    
endif()

