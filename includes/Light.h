#ifndef LIGHT_H
#define LIGHT_H

#include "Point3D.h"
#include "Vector3D.h"
#include "RGBColor.h"
#include "Camera.h"
#include <vector>

class Light {
protected:
  RGBColor m_color;
public:
  Light();
  Light(const RGBColor& color);
  ~Light();

  virtual const Point3D getPosition() const = 0;
  virtual const Vector3D getDirectionToPoint(const Point3D& position) const = 0;
  const RGBColor& getColor();
};


#endif /* LIGHT_H */

