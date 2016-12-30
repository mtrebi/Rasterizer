# CMake entry point
cmake_minimum_required (VERSION 3.5)
project (rasterizer)

## Add headers files
include_directories (
	includes/
)


set(SOURCES src/Point2D.cpp
            src/Point3D.cpp
            src/Vector3D.cpp
            src/Matrix.cpp
            src/GeometryObject.cpp
            src/Camera.cpp
            src/Light.cpp
            src/Renderer.cpp
            src/Rasterizer.cpp
            src/World.cpp
            src/main.cpp)

add_compile_options(
  -std=c++11
  -G
) 

# main.cpp
add_executable(main ${SOURCES})
target_link_libraries(main)