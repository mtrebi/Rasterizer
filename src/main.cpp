#include <iostream>
#include <vector>

#include "World.h"
#include "Renderer.h"
#include "ForwardRasterizer.h"
#include "DeferredRasterizer.h"
#include "Camera.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"
#include "Constants.h"


// Build two scenes
  // Textured scene
    // Textured boxes
    // Textures walls
  // Flat scene
    // Pyramids
    // Planes

std::vector<GeometryObject*> OBJECTS {
  //triangle,
  //textured_rectangle
  //Objects::box,
  Objects::box,

  //Objects::ground,
  //Objects::ground2,

  //buildPlainBox(Materials::PLASTIC, Colors::RED, Point3D(100, 100, 50), 100),
  //buildTexturedBox(Materials::BOX, Point3D(-500, 0, 3000), 500),
  //Objects::rainbow_triangle
};

const std::vector<Light*> LIGHTS {
  new PointLight(Colors::WHITE, Point3D(1000, 0, -250))
};

Camera * camera;
Renderer * renderer;
int main (){
  World * world = new World(OBJECTS, LIGHTS, camera);


#ifdef _FORWARD
  renderer = new ForwardRasterizer(world);
#endif 

#ifdef _DEFERRED
  renderer = new DeferredRasterizer(world);
#endif 

#ifdef _ORTHOGRAPHIC
  camera = new OrthographicCamera(CAMERA_POS, IMAGE_HEIGHT, IMAGE_WIDTH, renderer);
#endif 

#ifdef _PERSPECTIVE
  camera = new PerspectiveCamera(CAMERA_POS, IMAGE_HEIGHT, IMAGE_WIDTH, renderer);
#endif 
  world->m_camera = camera;
  camera->render();
  renderer->export_output(IMAGE_NAME);
  return 0;
}