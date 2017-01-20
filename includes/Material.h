#pragma once

#include "RGBColor.h"

class Material {
public:
  RGBColor k_d,
    k_s;
  float k_shininess;

  Material();
  Material(const RGBColor& d, const RGBColor& s, float shininess);
  ~Material();
};

