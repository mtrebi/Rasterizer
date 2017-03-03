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

// Forward declaration utils functions
void buildAlignedBox(std::vector<Point3D>& vertices, std::vector<Vector2D>& texture_coords, std::vector<uint32_t>& indices, const float side);
GeometryObject* buildPlainBox(Material* material, const RGBColor& color, const Point3D& center, const float side);
GeometryObject* buildTexturedBox(Material* material, const Point3D& center, const float side);

void buildHorizontalPlane(std::vector<Point3D>& vertices, std::vector<Vector2D>& texture_coords, std::vector<uint32_t>& indices, const float side);
GeometryObject* buildTexturedPlane(Material* material, const Point3D& center, const float side);
GeometryObject* buildPlainPlane(Material* material, const RGBColor& color, const Point3D& center, const float side);
GeometryObject* buildMultiColorBox(Material* material, const Point3D& center, const float side);

const std::vector<GeometryObject*> setupFlatScene();
const std::vector<GeometryObject*> setupTexturedScene();

Camera * camera;
Renderer * renderer;
int main (){
  std::vector<Light*> lights = {
    new DirectionalLight(Colors::WHITE, Vector3D(-1, -1, -1))
  };
  const std::vector<GeometryObject*> objects_flat = setupFlatScene();
  const std::vector<GeometryObject*> objects_textured = setupTexturedScene();


  World * world = new World(objects_textured, lights, camera);
#ifdef _FORWARD
  renderer = new DeferredRasterizer(world);
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
  renderer->render();
  renderer->export_output(IMAGE_NAME);
  return 0;
}


const std::vector<GeometryObject*> setupFlatScene() {
  std::vector<GeometryObject*> objects;

  // Objects
  /**/
  GeometryObject* ground = buildPlainPlane(Materials::FLAT_PLASTIC, Colors::GREY, Point3D(0, 0, 0), 500);
  objects.push_back(ground);

  GeometryObject* flat_box = buildPlainBox(Materials::FLAT_PLASTIC, Colors::RED, Point3D(0, 0, 0), 100);
  flat_box->translate(Vector3D(150, 50, 100));
  flat_box->rotate(0, 45, 0);
  objects.push_back(flat_box);

  //GeometryObject* ground2 = buildPlainPlane(Materials::FLAT_PLASTIC, Colors::YELLOW, Point3D(247, 0.29, -249), 10);
  //objects.push_back(ground2);

  /*
  GeometryObject* flat_box2 = buildPlainBox(Materials::FLAT_PLASTIC, Colors::BLUE, Point3D(150, 125, 100), 50);
  objects.push_back(flat_box2);

  GeometryObject* flying_box = buildPlainBox(Materials::FLAT_PLASTIC, Colors::GREEN, Point3D(-100, 80, 75), 50);
  flying_box->rotate(45, -45, 45);
  objects.push_back(flying_box);

  GeometryObject* multicolor_box = buildMultiColorBox(Materials::FLAT_PLASTIC, Point3D(-100, 50, -90), 100);
  objects.push_back(multicolor_box);
  
  GeometryObject* small_box1 = buildPlainBox(Materials::FLAT_PLASTIC, Colors::YELLOW, Point3D(150, 40, -100), 20);
  objects.push_back(small_box1);
  GeometryObject* small_box2 = buildPlainBox(Materials::FLAT_PLASTIC, Colors::YELLOW, Point3D(150, 60, -100), 20);
  objects.push_back(small_box2);
  GeometryObject* small_box3 = buildPlainBox(Materials::FLAT_PLASTIC, Colors::YELLOW, Point3D(130, 40, -100), 20);
  objects.push_back(small_box3);
  GeometryObject* small_box4 = buildPlainBox(Materials::FLAT_PLASTIC, Colors::YELLOW, Point3D(150, 40, -120), 20);
  objects.push_back(small_box4);
  GeometryObject* small_box5 = buildPlainBox(Materials::FLAT_PLASTIC, Colors::YELLOW, Point3D(125, 40, -125), 20);
  small_box5->rotate(0, 45, 0);
  objects.push_back(small_box5);
  */
  return objects;
}

const std::vector<GeometryObject*> setupTexturedScene() {
  std::vector<GeometryObject*> objects;

  // Objects
  
  GeometryObject* small_box3 = buildPlainBox(Materials::FLAT_PLASTIC, Colors::RED, Point3D(150, 110, -155), 50);
  small_box3->rotate(0, 0, 0);
  objects.push_back(small_box3);


  GeometryObject* small_box1 = buildPlainBox(Materials::FLAT_PLASTIC, Colors::GREEN, Point3D(150, 50, -155), 50);
  small_box1->rotate(0, 90, 0);
  objects.push_back(small_box1);

  GeometryObject* small_box4 = buildPlainBox(Materials::FLAT_PLASTIC, Colors::BLUE, Point3D(150, -10, -155), 50);
  small_box4->rotate(0, 180, 0);
  objects.push_back(small_box4);

  GeometryObject* small_box2 = buildPlainBox(Materials::FLAT_PLASTIC, Colors::YELLOW, Point3D(150, -70, -155), 50);
  small_box2->rotate(0, -90, 0);
  objects.push_back(small_box2);


  
  /*
  GeometryObject* ground = buildTexturedPlane(Materials::GROUND, Point3D(0, 0, 0), 500);
  objects.push_back(ground);
  
  GeometryObject* flat_box = buildTexturedBox(Materials::BOX, Point3D(0, 0, 0), 100);
  flat_box->translate(Vector3D(150, 50, 100));
  flat_box->rotate(0, 45, 0);
  objects.push_back(flat_box);

  GeometryObject* flat_box2 = buildTexturedBox(Materials::BOX, Point3D(150, 125, 100), 50);
  objects.push_back(flat_box2);

  GeometryObject* flying_box = buildTexturedBox(Materials::BOX, Point3D(-100, 80, 75), 50);
  flying_box->rotate(45, -45, 45);
  objects.push_back(flying_box);

  GeometryObject* multicolor_box = buildTexturedBox(Materials::BOX, Point3D(-100, 50, -90), 100);
  objects.push_back(multicolor_box);

  GeometryObject* small_box1 = buildTexturedBox(Materials::DEFAULT, Point3D(150, 60, -155), 60);
  small_box1->rotate(0, -45, 0);
  objects.push_back(small_box1);
  */
  /*
  GeometryObject* small_box2 = buildTexturedBox(Materials::DEFAULT, Point3D(150, 70, -100), 50);
  objects.push_back(small_box2);
  GeometryObject* small_box3 = buildTexturedBox(Materials::DEFAULT,Point3D(130, 40, -100), 20);
  objects.push_back(small_box3);
  GeometryObject* small_box4 = buildTexturedBox(Materials::DEFAULT, Point3D(150, 40, -120), 20);
  objects.push_back(small_box4);
  GeometryObject* small_box5 = buildTexturedBox(Materials::DEFAULT, Point3D(125, 40, -125), 20);
  small_box5->rotate(0, 45, 0);
  objects.push_back(small_box5);
  */
  return objects;
}


void buildAlignedBox(std::vector<Point3D>& vertices, std::vector<Vector2D>& texture_coords, std::vector<uint32_t>& indices, const float side) {
  const float half_diagonal = (side / 2) / sin(PI / 2); // Distance to center
                                                        // Front
  const Point3D v1(-half_diagonal, -half_diagonal, -half_diagonal);
  const Point3D v2(v1.x, v1.y + side, v1.z);
  const Point3D v3(v1.x + side, v1.y + side, v1.z);
  const Point3D v4(v1.x + side, v1.y, v1.z);
  // Back
  const Point3D v5(v1.x, v1.y, v1.z + side);
  const Point3D v6(v2.x, v2.y, v2.z + side);
  const Point3D v7(v3.x, v3.y, v3.z + side);
  const Point3D v8(v4.x, v4.y, v4.z + side);

  vertices = {
    // Front face
    v1, v2, v3, v4,

    // Back face
    v5, v6, v7, v8,

    // Top face
    v2, v6, v7, v3,

    // Bottom face
    v1, v5, v8, v4,

    // Left face
    v1, v2, v6, v5,

    // Right face
    v4, v3, v7, v8
  };

  texture_coords = {
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
    //// Bottom face
    Vector2D(0, 0),
    Vector2D(0, 1),
    Vector2D(1, 1),
    Vector2D(1, 0),
    //// Left face
    Vector2D(1, 0),
    Vector2D(0, 0),
    Vector2D(1, 1),
    Vector2D(0, 1),
    //// Right face
    Vector2D(0, 0),
    Vector2D(0, 1),
    Vector2D(1, 1),
    Vector2D(1, 0)
  };

  indices = {
    // Vertices indices
    // Front face
    0, 1, 2,
    2, 3, 0,

    // Back face
    6, 5, 4,
    4, 7, 6,

    // Top face
    8, 9, 10,
    10, 11, 8,

    // Bottom face
    14, 13, 12,
    12, 15, 14,

    // Left face
    16, 19, 18,
    18, 17, 16,

    // Right face
    20, 21, 22,
    22, 23, 20
  };
}

GeometryObject* buildPlainBox(Material* material, const RGBColor& color, const Point3D& center, const float side) {
  const std::vector<RGBColor> colors = std::vector<RGBColor>(24, color);

  std::vector<Point3D> vertices;
  std::vector<Vector2D> texture_coords;
  std::vector<uint32_t> indices;
  buildAlignedBox(vertices, texture_coords, indices, side);
  GeometryObject* box = new GeometryObject(material, vertices, colors, texture_coords, indices, center);

  return box;
}

GeometryObject* buildMultiColorBox(Material* material, const Point3D& center, const float side) {
  const std::vector<RGBColor> colors = {
    Colors::RED,
    Colors::GREEN,
    Colors::RED,
    Colors::BLUE,

    Colors::RED,
    Colors::GREEN,
    Colors::RED,
    Colors::BLUE,

    Colors::RED,
    Colors::GREEN,
    Colors::RED,
    Colors::BLUE,

    Colors::RED,
    Colors::GREEN,
    Colors::RED,
    Colors::BLUE,

    Colors::RED,
    Colors::GREEN,
    Colors::RED,
    Colors::BLUE,

    Colors::RED,
    Colors::GREEN,
    Colors::RED,
    Colors::BLUE,
  };

  std::vector<Point3D> vertices;
  std::vector<Vector2D> texture_coords;
  std::vector<uint32_t> indices;
  buildAlignedBox(vertices, texture_coords, indices, side);
  GeometryObject* box = new GeometryObject(material, vertices, colors, texture_coords, indices, center);

  return box;
}

GeometryObject* buildTexturedBox(Material* material, const Point3D& center, const float side) {
  std::vector<Point3D> vertices;
  std::vector<Vector2D> texture_coords;
  std::vector<uint32_t> indices;
  buildAlignedBox(vertices, texture_coords, indices, side);
  GeometryObject* box = new GeometryObject(material, vertices, std::vector<RGBColor>(), texture_coords, indices, center);
  return box;
}

void buildHorizontalPlane(std::vector<Point3D>& vertices, std::vector<Vector2D>& texture_coords, std::vector<uint32_t>& indices, const float side) {
  const float half_diagonal = (side / 2) / sin(PI / 2); // Distance to center

  const Point3D v1(-half_diagonal, 0, -half_diagonal);
  const Point3D v2(v1.x, v1.y, v1.z + side);
  const Point3D v3(v1.x + side, v1.y, v1.z);
  const Point3D v4(v1.x + side, v1.y, v1.z + side);

  vertices = {
    // Vertices positions
    v1, v2, v3, v4
  };

  texture_coords = {
    // Texture coordinates
    Vector2D(0, 0),
    Vector2D(0, 3),
    Vector2D(3, 0),
    Vector2D(3, 3)
  };

  indices = {
    // Indices
    0, 1, 2,
    1, 3, 2
  };
}

GeometryObject* buildPlainPlane(Material* material, const RGBColor& color, const Point3D& center, const float side) {
  const std::vector<RGBColor> colors = std::vector<RGBColor>(4, color);
  std::vector<Point3D> vertices;
  std::vector<Vector2D> texture_coords;
  std::vector<uint32_t> indices;
  buildHorizontalPlane(vertices, texture_coords, indices, side);
  GeometryObject* box = new GeometryObject(material, vertices, colors, texture_coords, indices, center);
  return box;
}

GeometryObject* buildTexturedPlane(Material* material, const Point3D& center, const float side) {
  std::vector<Point3D> vertices;
  std::vector<Vector2D> texture_coords;
  std::vector<uint32_t> indices;
  buildHorizontalPlane(vertices, texture_coords, indices, side);
  GeometryObject* box = new GeometryObject(material, vertices, std::vector<RGBColor>(), texture_coords, indices, center);
  return box;
}