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
#include "Constants.h"
/*
GeometryObject* cube = new GeometryObject(Colors::RED, Materials::PLASTIC, 
  std::vector<Point3D> {
    Point3D(500, -500, 1),
    Point3D(500, 500, 1),
    Point3D(1000, 500, 1),
    Point3D(1000, -500, 1),

    Point3D(500, -500, 20),
    Point3D(500, 500, 20),
    Point3D(1000, 500, 20),
    Point3D(1000, -500, 20),
  }, 
  std::vector<uint32_t> {
      0, 1, 2,
      2, 3, 0,

      3, 2, 6,
      6, 7, 3,

      6, 5, 4,
      4, 7, 6,

      1, 5, 4,
      4, 0, 1,

      1, 2, 6,
      6, 5, 1
  });
  */

GeometryObject* ground = new GeometryObject(Materials::WALL,
  std::vector<Point3D> {
    Point3D(-3000., -1000., 1.),
    Point3D(-3000., -1000., 50.),
    Point3D(3000., -1000., 1.),
    Point3D(3000., -1000., 50.)
  },
  std::vector<RGBColor> {

  },
      std::vector<Vector2D> {
    Vector2D(0, 0),
      Vector2D(0, 5),
      Vector2D(5, 0),
      Vector2D(5, 5)

  },

    std::vector<uint32_t> {
      0, 1, 2,
        1, 3, 2
    },
      "../assets/brick_wall.bmp");

GeometryObject* textured_rectangle = new GeometryObject(Materials::WALL,
  std::vector<Point3D> {
  Point3D(-1500, -250, 15.),
    Point3D(-1500, 2348, 15.),
    Point3D(1500, -250, 15.),
    Point3D(1500, 2348, 15.),

},
std::vector<RGBColor> {
    Colors::GREEN,
      Colors::RED,
      Colors::BLUE,
      Colors::BLUE
  },
  std::vector<Vector2D> {
    Vector2D(0, 0),
      Vector2D(0, 1),
      Vector2D(1, 0),
      Vector2D(1, 1)

  },
    
  std::vector<uint32_t> {
  0, 1, 2,
    1, 3, 2
  },
  "../assets/brick_wall.bmp");


GeometryObject* triangle = new GeometryObject(Materials::WALL,
  std::vector<Point3D> {
    Point3D(-1500, -250, 15.),
    Point3D(0, 2348, 15.),
    Point3D(1500, -250, 15.),
},
  std::vector<RGBColor> {
    Colors::GREEN,
    Colors::RED,
    Colors::BLUE,
  },
  std::vector<Vector2D> {
    Vector2D(0, 0),
    Vector2D(.5, 1),
    Vector2D(1, 0)
  },
  std::vector<uint32_t> {
    0, 1, 2,
  });

const std::vector<GeometryObject*> OBJECTS {
  //triangle,
  //textured_rectangle
  //cube, 
 ground
};

const std::vector<Light*> LIGHTS {
  new PointLight(Colors::WHITE, Point3D(0, 0, 105))
};

Camera * camera;

int main (){
    World * world = new World(OBJECTS, LIGHTS, camera);
    Renderer * renderer = new Rasterizer(world);

#ifdef _ORTHOGRAPHIC
    camera = new OrthographicCamera(CAMERA_POS, IMAGE_HEIGHT, IMAGE_WIDTH, renderer);
#endif 

#ifdef _PERSPECTIVE
    camera = new PerspectiveCamera(CAMERA_POS, IMAGE_HEIGHT, IMAGE_WIDTH, renderer);
#endif 
    world->m_camera = camera;
    camera->render(IMAGE_NAME);
    
    return 0;
}