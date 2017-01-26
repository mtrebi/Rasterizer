#pragma once
#include <string>

#include "POINT3D.H"
#include "VECTOR3D.H"
#include "Material.h"
#include "RGBCOLOR.H"

const Point3D   CAMERA_POS = Point3D(.0f, .0f, -1.0f);
const Vector3D  CAMERA_FWD = Vector3D(.0f, .0f, 1.0f); // Points into the screen
const Vector3D  CAMERA_UP = Vector3D(.0f, 1.0f, .0f);

const int IMAGE_WIDTH = 800;
const int IMAGE_HEIGHT = 600;
const std::string IMAGE_NAME = "output.bmp";


namespace Materials {
  const Material PLASTIC = Material(RGBColor(0.4), 0.4, 2);
  const Material WALL = Material(RGBColor(0.6), 0.2, 1);
}

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

