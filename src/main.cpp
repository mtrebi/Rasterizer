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
void buildAlignedBox(std::vector<Point3D>& vertices, std::vector<Vector2D>& texture_coords, std::vector<uint32_t>& indices, const Point3D& center, const float side);
GeometryObject* buildPlainBox(Material* material, const RGBColor& color, const Point3D& center, const float side);
GeometryObject* buildTexturedBox(Material* material, const Point3D& center, const float side);

void buildHorizontalPlane(std::vector<Point3D>& vertices, std::vector<Vector2D>& texture_coords, std::vector<uint32_t>& indices, const Point3D& center, const float side);
GeometryObject* buildTexturedPlane(Material* material, const Point3D& center, const float side);
GeometryObject* buildPlainPlane(Material* material, const RGBColor& color, const Point3D& center, const float side);


Camera * camera;
Renderer * renderer;
// TODO: Build two scenes: flat and textured
int main (){
  std::vector<Light*> lights;
  std::vector<GeometryObject*> objects;

  // Objects
  GeometryObject* ground = buildTexturedPlane(Materials::DEFAULT, Point3D(0, 0, 1000), 500);
  //objects.push_back(ground);

  GeometryObject* flat_box = buildPlainBox(Materials::FLAT_PLASTIC, Colors::RED, Point3D(200, -200, 0), 100);
  //flat_box->rotate(45, 60, 0);
  objects.push_back(flat_box);
  
  GeometryObject* textured_box = buildTexturedBox(Materials::DEFAULT, Point3D(0, 200, 0), 100);
  textured_box->rotate(45, 45, 45);
  objects.push_back(textured_box);

  GeometryObject* textured_default_box = buildTexturedBox(Materials::DEFAULT, Point3D(0, 0, 600), 100);
  //textured_default_box->rotate(45, 45, 45);
  //objects.push_back(textured_default_box);


  // Lights
  Light * point_light = new PointLight(Colors::WHITE, Point3D(0, 2000, -2000));
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



void buildAlignedBox(std::vector<Point3D>& vertices, std::vector<Vector2D>& texture_coords, std::vector<uint32_t>& indices, const Point3D& center, const float side) {
  const float half_diagonal = (side / 2) / sin(PI / 2); // Distance to center
                                                        // Front
  const Point3D v1(center.x - half_diagonal, center.y - half_diagonal, center.z - half_diagonal);
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
    v1, v5, v2, v6,

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
    // Bottom face
    Vector2D(0, 0),
    Vector2D(0, 1),
    Vector2D(1, 1),
    Vector2D(1, 0),
    // Left face
    Vector2D(1, 0),
    Vector2D(0, 0),
    Vector2D(1, 1),
    Vector2D(0, 1),
    // Right face
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
    4, 5, 6,
    6, 7, 4,

    // Top face
    8, 9, 10,
    //10, 9, 8,
    10, 11, 8,

    // Bottom face
    12, 13, 14,
    14, 15, 12,

    // Left face
    18, 17, 16,
    18, 19, 17,

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
  buildAlignedBox(vertices, texture_coords, indices, center, side);
  GeometryObject* box = new GeometryObject(material, vertices, colors, texture_coords, indices);

  return box;
}

GeometryObject* buildTexturedBox(Material* material, const Point3D& center, const float side) {
  std::vector<Point3D> vertices;
  std::vector<Vector2D> texture_coords;
  std::vector<uint32_t> indices;
  buildAlignedBox(vertices, texture_coords, indices, center, side);
  GeometryObject* box = new GeometryObject(material, vertices, std::vector<RGBColor>(), texture_coords, indices);
  return box;
}

void buildHorizontalPlane(std::vector<Point3D>& vertices, std::vector<Vector2D>& texture_coords, std::vector<uint32_t>& indices, const Point3D& center, const float side) {
  const float half_diagonal = (side / 2) / sin(PI / 2); // Distance to center

  const Point3D v1(center.x - half_diagonal, center.y, center.z - half_diagonal);
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
    Vector2D(0, 4),
    Vector2D(4, 0),
    Vector2D(4, 4)
  };

  indices = {
    // Indices
    0, 1, 2,
    2, 3, 1
  };
}

GeometryObject* buildPlainPlane(Material* material, const RGBColor& color, const Point3D& center, const float side) {
  const std::vector<RGBColor> colors = std::vector<RGBColor>(4, color);
  std::vector<Point3D> vertices;
  std::vector<Vector2D> texture_coords;
  std::vector<uint32_t> indices;
  buildHorizontalPlane(vertices, texture_coords, indices, center, side);
  GeometryObject* box = new GeometryObject(material, vertices, colors, texture_coords, indices);
  return box;
}

GeometryObject* buildTexturedPlane(Material* material, const Point3D& center, const float side) {
  std::vector<Point3D> vertices;
  std::vector<Vector2D> texture_coords;
  std::vector<uint32_t> indices;
  buildHorizontalPlane(vertices, texture_coords, indices, center, side);
  GeometryObject* box = new GeometryObject(material, vertices, std::vector<RGBColor>(), texture_coords, indices);
  return box;
}