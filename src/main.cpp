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

const Point3D   CAMERA_POS  = Point3D(.0f, .0f, -10.0f);
const Vector3D  CAMERA_FWD  = Vector3D(.0f, .0f, 1.0f); // Points into the screen
const Vector3D  CAMERA_UP   = Vector3D(.0f, 1.0f, .0f);

const int IMAGE_WIDTH         = 500;
const int IMAGE_HEIGHT        = 500;
const std::string IMAGE_NAME  = "output.bmp";

//const Material plastic = Material(0.4, 0.4, 2);

const std::vector<GeometryObject*> OBJECTS {
  new GeometryObject()
};

const std::vector<Light*> LIGHTS {
  new PointLight(RGBColor(1.0f), Point3D(0.0f, 100.0f, -50.0f))
};

int main (){
    Camera * camera = new OrthographicCamera(CAMERA_POS, CAMERA_FWD, CAMERA_UP);
    World * world = new World(OBJECTS, LIGHTS, camera);
    Renderer * renderer = new Rasterizer(world, IMAGE_WIDTH, IMAGE_HEIGHT);
    renderer->render(IMAGE_NAME);
    
    return 0;
}