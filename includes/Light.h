#ifndef LIGHT_H
#define LIGHT_H

class World;
#include "Point3D.h"
#include "Vector3D.h"
#include "RGBColor.h"

#include <vector>

class Rasterizer;

class Light {
protected:
  RGBColor m_color;

public:
  Light();
  Light(const RGBColor& color);
  ~Light();

  virtual const Vector3D getDirectionToPoint(const Point3D& position) const = 0;
  virtual const std::vector<double> getShadowMap(const World* world, const int image_height, const int image_width, Rasterizer * rasterizer_camera) const = 0;

  const RGBColor& getColor();
};


#endif /* LIGHT_H */

