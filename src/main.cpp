#include <iostream>
#include <vector>

#include "World.h"
#include "Renderer.h"
#include "Rasterizer.h"
#include "Camera.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"

const Point3D   CAMERA_POS  = Point3D(.0f, .0f, -1.0f);
const Vector3D  CAMERA_FWD  = Vector3D(.0f, .0f, 1.0f); // Points into the screen
const Vector3D  CAMERA_UP   = Vector3D(.0f, 1.0f, .0f);

const int IMAGE_WIDTH         = 500;
const int IMAGE_HEIGHT        = 500;
const std::string IMAGE_NAME  = "output.bmp";

const Material M_PLASTIC = Material(0.4, 0.4, 2);
const RGBColor C_RED = RGBColor(1.0, 0.0, 0.0);

const std::vector<Point3D> vertices = {
  Point3D(50, -50, 1),
  Point3D(50, 50, 1),
  Point3D(100, 50, 1),
  Point3D(100, -50, 1),

  Point3D(50, -50, 20),
  Point3D(50, 50, 20),
  Point3D(100, 50, 20),
  Point3D(100, -50, 20),

};

const std::vector<uint32_t> indices = {
  0, 1, 2,
  2, 3, 0,

  3, 2, 6,
  6, 7, 3,

  //6, 5, 4,
  //4, 7, 6,

  1, 5, 4,
  4, 0, 1,

  //1, 2, 6,
  //6, 5, 1
};

const std::vector<GeometryObject*> OBJECTS {
  new GeometryObject(C_RED, M_PLASTIC, vertices, indices)
};

const std::vector<Light*> LIGHTS {
  new PointLight(RGBColor(1.0f), Point3D(0.0f, 100.0f, -50.0f))
};

Camera * camera;

int main (){
#ifdef _ORTHOGRAPHIC
  camera = new OrthographicCamera(CAMERA_POS, IMAGE_HEIGHT, IMAGE_WIDTH);
#endif 

#ifdef _PERSPECTIVE
  camera = new PerspectiveCamera(CAMERA_POS, IMAGE_HEIGHT, IMAGE_WIDTH);
#endif 

    World * world = new World(OBJECTS, LIGHTS, camera);
    Renderer * renderer = new Rasterizer(world, IMAGE_WIDTH, IMAGE_HEIGHT);
    renderer->render(IMAGE_NAME);
    
    return 0;
}