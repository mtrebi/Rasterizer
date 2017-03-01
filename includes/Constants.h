#pragma once

#include <string>
#include "POINT3D.H"
#include "VECTOR3D.H"
#include "Material.h"
#include "RGBCOLOR.H"
#include <math.h>       /* sin */

#define PI 3.14159265

const Point3D   CAMERA_POS = Point3D(0, 200, -400);
const Point3D   CAMERA_TARGET = Point3D(0, 0, 0);

const int IMAGE_WIDTH = 1280;
const int IMAGE_HEIGHT = 720;
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
  Material* FLAT_PLASTIC = new FlatMaterial(RGBColor(0.4), 0.4, 1);

  Material* DEFAULT = new TexturedMaterial(
    "../assets/default_DIFF.bmp",
    "../assets/default_SPEC.bmp",
    "../assets/default_NRM.bmp",
    10.0
  );

  Material* BOX = new TexturedMaterial(
    "../assets/box_DIFF.bmp",
    "../assets/box_SPEC.bmp",
    "../assets/box_NRM.bmp",
    5.0
  );

  Material* GROUND = new TexturedMaterial(
    "../assets/brick_wall_DIFF.bmp",
    "../assets/brick_wall_SPEC.bmp",
    "../assets/brick_wall_NRM.bmp",
    3.0
  );

}


