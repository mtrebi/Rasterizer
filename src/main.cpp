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

Camera * camera;
Renderer * renderer;
// TODO: Build two scenes: flat and textured
int main (){
  std::vector<Light*> lights;
  std::vector<GeometryObject*> objects;

  // Objects
  GeometryObject* ground = buildTexturedPlane(Materials::DEFAULT, Point3D(0, 0, 1000), 500);
  //objects.push_back(ground);

  GeometryObject* flat_box = buildPlainBox(Materials::FLAT_PLASTIC, Colors::RED, Point3D(0, 0, 0), 200);
  //flat_box->rotate(45, 60, 0);
  objects.push_back(flat_box);
  
  GeometryObject* textured_box = buildTexturedBox(Materials::BOX, Point3D(0, 0, 0), 200);
  //textured_box->rotate(45, 45, 45);
  //objects.push_back(textured_box);

  GeometryObject* textured_default_box = buildTexturedBox(Materials::DEFAULT, Point3D(0, 0, 600), 200);
  //textured_default_box->rotate(45, 45, 45);
  //objects.push_back(textured_default_box);


  // Lights
  Light * point_light = new PointLight(Colors::WHITE, Point3D(0, 2000, 0));
  lights.push_back(point_light);

  World * world = new World(objects, lights, camera);
#ifdef _FORWARD
  renderer = new ForwardRasterizer(world);
#endif 

#ifdef _DEFERRED
  renderer = new DeferredRasterizer(world);
#endif 

#ifdef _ORTHOGRAPHIC
  camera = new OrthographicCamera(CAMERA_POS, CAMERA_TARGET, IMAGE_HEIGHT, IMAGE_WIDTH, renderer);
#endif 

#ifdef _PERSPECTIVE
  camera = new PerspectiveCamera(CAMERA_POS, CAMERA_TARGET, IMAGE_HEIGHT, IMAGE_WIDTH, renderer);
#endif 
  world->m_camera = camera;
  //camera->rotate(45, 0, 0);
  camera->render();
  renderer->export_output(IMAGE_NAME);
  return 0;
}