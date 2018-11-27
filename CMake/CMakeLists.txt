project(GameEngineCM)
cmake_minimum_required(VERSION 3.0)

include_directories(
${PROJECT_SOURCE_DIR}/../Tools/glm/
)

file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/../RayTracer/*.cpp)

include_directories("./RayTracer/")

add_executable(rayTracerExe ${SRCS})
set_target_properties(rayTracerExe PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
#target_link_libraries(rayTracerExe freeimage)



