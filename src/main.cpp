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

GeometryObject* box = new GeometryObject(Materials::PLASTIC, 
  std::vector<Point3D> {
    // Vertices positions
      // Front face
    Point3D(500, -500, 5),
    Point3D(500, 500, 5),
    Point3D(1500, 500, 5),
    Point3D(1500, -500, 5),
      // Back face
    Point3D(500, -500, 10),
    Point3D(500, 500, 10),
    Point3D(1500, 500, 10),
    Point3D(1500, -500, 10),
      // Top face
    Point3D(500, 500, 5),
    Point3D(500, 500, 10),
    Point3D(1500, 500, 10),
    Point3D(1500, 500, 5),
      // Bottom face
    Point3D(500, -500, 5),
    Point3D(500, -500, 10),
    Point3D(1500, -500, 10),
    Point3D(1500, -500, 5),
      // Left face
    Point3D(500, -500, 5),
    Point3D(500, 500, 5),
    Point3D(500, 500, 10),
    Point3D(500, -500, 10),
      // Right face
    Point3D(1500, -500, 5),
    Point3D(1500, 500, 5),
    Point3D(1500, 500, 10),
    Point3D(1500, -500, 10),

  }, 
  std::vector<RGBColor> {
    // Vertices colors
  },
  std::vector<Vector2D> {
    // Texture coordinates
      // Front face
    Vector2D(0, 0),
    Vector2D(0, 1),
    Vector2D(1, 1),
    Vector2D(1, 0),
      // Back face
    Vector2D(1, 1),
    Vector2D(1, 0),
    Vector2D(0, 0),
    Vector2D(0, 1),
      // Top face
    Vector2D(0, 0),
    Vector2D(0, 1),
    Vector2D(1, 1),
    Vector2D(1, 0),
      // Bottom face
    Vector2D(0, 0),
    Vector2D(0, 1),
    Vector2D(1, 1),
    Vector2D(1, 0),
     // Left face
    Vector2D(1, 0),
    Vector2D(1, 1),
    Vector2D(0, 1),
    Vector2D(0, 0),
     // Right face
    Vector2D(0, 0),
    Vector2D(0, 1),
    Vector2D(1, 1),
    Vector2D(1, 0)
  },
  std::vector<uint32_t> {
    // Vertices indices
      // Front face
      0, 1, 2,
      2, 3, 0,

      // Back face
      4, 5, 6,
      6, 7, 4,
      
      // Top face
      8, 9, 10,
      10, 11, 8,

      // Bottom face
      12, 13, 14,
      14, 15, 12,

      // Left face
      16, 17, 18,
      18, 19, 16,

      // Right face
      20, 21, 22,
      22, 23, 20
  },
  // Texture image location
  "../assets/box.bmp");
  

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
  box
// ground
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