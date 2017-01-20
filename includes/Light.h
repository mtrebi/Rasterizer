#ifndef LIGHT_H
#define LIGHT_H

#include "Point3D.h"
#include "Vector3D.h"
#include "RGBColor.h"

class Light {
private:
  RGBColor m_color;
public:
  Light();
  Light(const RGBColor& color);
  ~Light();

  virtual const Vector3D getDirectionToPoint(const Point3D& position) const = 0;
  const RGBColor& getColor();
};


#endif /* LIGHT_H */

