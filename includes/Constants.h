#pragma once

#include <string>
#include "POINT3D.H"
#include "VECTOR3D.H"
#include "Material.h"
#include "RGBCOLOR.H"
#include <math.h>       /* sin */

#define PI 3.14159265

const Point3D   CAMERA_POS = Point3D(.0f, .0f, -1.0f);
const Vector3D  CAMERA_FWD = Vector3D(.0f, .0f, 1.0f); // Points into the screen
const Vector3D  CAMERA_UP = Vector3D(.0f, 1.0f, .0f);

const int IMAGE_WIDTH = 800;
const int IMAGE_HEIGHT = 600;
const std::string IMAGE_NAME = "output.bmp";

namespace Colors {
  const RGBColor WHITE = RGBColor(1.0, 1.0, 1.0);
  const RGBColor BLACK = RGBColor(0.0, 0.0, 0.0);
  const RGBColor RED = RGBColor(1.0, 0.0, 0.0);
  const RGBColor GREEN = RGBColor(0.0, 1.0, 0.0);
  const RGBColor BLUE = RGBColor(0.0, 0.0, 1.0);
  const RGBColor GREY = RGBColor(0.5, 0.5, 0.5);
  const RGBColor YELLOW = RGBColor(1.0, 1.0, 0.0);
  const RGBColor PURPLE = RGBColor(1.0, 0.0, 1.0);
  const RGBColor CYAN = RGBColor(0.0, 1.0, 1.0);
}

namespace Materials {
  Material* PLASTIC = new FlatMaterial(RGBColor(0.4), 0.4, 2);
  Material* WALL = new FlatMaterial(RGBColor(0.6), 0.2, 1);

  //const Material* BRICK = new TexturedMaterial();
   Material* BOX = new TexturedMaterial(
    "../assets/box.bmp",
    "../assets/box_specular.bmp",
    "../assets/box_NRM.bmp",
    5.0
  );
   Material* GROUND = new TexturedMaterial(
     "../assets/brick_wall.bmp",
     "../assets/brick_wall_SPEC.bmp",
     "../assets/brick_wall_NRM.bmp",
     5.0
   );

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

namespace Objects {
    GeometryObject* box = new GeometryObject(Materials::BOX,
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
      Point3D(500, -500, 10),
      Point3D(500, 500, 5),
      Point3D(500, 500, 10),

        
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
      Vector2D(0, 0),
      Vector2D(1, 1),
      Vector2D(0, 1),
          
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
            18, 17, 16,
            18, 19, 17,

            // Right face
            20, 21, 22,
            22, 23, 20
        });

  GeometryObject* ground = new GeometryObject(Materials::GROUND,
    std::vector<Point3D> {
      // Vertices positions
      Point3D(-3000., -1000., 1.),
      Point3D(-3000., -1000., 50.),
      Point3D(3000., -1000., 1.),
      Point3D(3000., -1000., 50.)
    },
    std::vector<RGBColor> {
      // Vertices colors
    },
    std::vector<Vector2D> {
      // Texture coordinates
      Vector2D(0, 0),
      Vector2D(0, 5),
      Vector2D(5, 0),
      Vector2D(5, 5)
    },

    std::vector<uint32_t> {
      // Indices
      0, 1, 2,
      1, 3, 2
    });

  GeometryObject* textured_rectangle = new GeometryObject(Materials::WALL,
    std::vector<Point3D> {
      // Vertices positions
      Point3D(-1500, -250, 15.),
      Point3D(-1500, 2348, 15.),
      Point3D(1500, -250, 15.),
      Point3D(1500, 2348, 15.),
    },
    std::vector<RGBColor> {
        // Vertices colors
    },
    std::vector<Vector2D> {
      // Texture coordinates
      Vector2D(0, 0),
      Vector2D(0, 1),
      Vector2D(1, 0),
      Vector2D(1, 1)
    },
    std::vector<uint32_t> {
        // Indices
      0, 1, 2,
      1, 3, 2
    });

  GeometryObject* rainbow_triangle = new GeometryObject(Materials::WALL,
    std::vector<Point3D> {
      // Vertices positions
      Point3D(-500, 500, 500),
      Point3D(0, 1300, 500),
      Point3D(500, 500, 500),
    },
    std::vector<RGBColor> {
      // Vertices colors
      Colors::GREEN,
      Colors::RED,
      Colors::BLUE,
    },
    std::vector<Vector2D> {
      // Texture coordinates
      Vector2D(0, 0),
      Vector2D(.5, 1),
      Vector2D(1, 0)
    },
    std::vector<uint32_t> {
      // Indices
      0, 1, 2,
    });
}



