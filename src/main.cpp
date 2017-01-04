#include <iostream>
#include <vector>

#include "World.h"
#include "Renderer.h"
#include "Rasterizer.h"
#include "Camera.h"
#include "Light.h"
#include "OrthographicCamera.h"

const Point3D   CAMERA_POS  = Point3D(.0f, .0f, -10.0f);
const Vector3D  CAMERA_FWD  = Vector3D(.0f, .0f, 1.0f); // Points into the screen
const Vector3D  CAMERA_UP   = Vector3D(.0f, 1.0f, .0f);

const int IMAGE_WIDTH         = 640;
const int IMAGE_HEIGHT        = 480;
const std::string IMAGE_NAME  = "output.bmp";

const std::vector<GeometryObject*> OBJECTS {

};

const std::vector<Light*> LIGHTS {

};

int main (){
    Camera * camera = new OrthographicCamera(CAMERA_POS, CAMERA_FWD, CAMERA_UP);
    
    World * world = new World(OBJECTS, LIGHTS, camera);
    Renderer * renderer = new Rasterizer(world);
    //TODO IMAGE SIZES INSIDE CAMERA???
    renderer->render(IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_NAME);
    
    return 0;
}