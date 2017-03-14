# CMake entry point
cmake_minimum_required (VERSION 3.5)
project (rasterizer)

# Compile lib dependencies 
add_subdirectory (lib)

## Add headers files
include_directories (
	includes/
)

find_package(glm REQUIRED)

include_directories(${GLM_INCLUDE_DIRS})

set(SOURCES src/RGBColor.cpp
						src/Point2D.cpp
						src/Vector2D.cpp
						src/Point3D.cpp
						src/Vector3D.cpp
						src/Material.cpp
						src/GeometryObject.cpp
						src/Camera.cpp
						src/OrthographicCamera.cpp
						src/PerspectiveCamera.cpp
						src/Light.cpp
						src/DirectionalLight.cpp
						src/PointLight.cpp
						src/Renderer.cpp
						src/Rasterizer.cpp
            src/ForwardRasterizer.cpp
            src/DeferredRasterizer.cpp
            src/ShadowMap.cpp
						src/World.cpp
						src/main.cpp)

add_compile_options(
	-std=c++11
	-g
) 
# renderer
add_definitions(-D_FORWARD=1)
#add_definitions(-D_DEFERRED=1)

# shading
#add_definitions(-D_FLAT=1)
add_definitions(-D_BLINN_PHONG=1)
#add_definitions(-D_PHONG=1)

# shadows
add_definitions(-D_PCF_SHADOWS=1)

# camera
#add_definitions(-D_ORTHOGRAPHIC=1)
add_definitions(-D_PERSPECTIVE=1)

# texture mapping
#add_definitions(-D_AFFINE_TEXTURES=1)
add_definitions(-D_PERSPECTIVE_TEXTURES=1)

# main.cpp
add_executable(main ${SOURCES})
target_link_libraries(main EASY_BMP)
