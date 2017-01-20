#pragma once
#include "LIGHT.H"

#include "RGBColor.h"
#include "Vector3D.h"
#include "Point3D.h"

class PointLight : public Light {
private:
  Vector3D m_position;
public:
  PointLight();
  PointLight(const RGBColor& color, const Point3D& position);
  ~PointLight();

  const Vector3D getDirectionToPoint(const Point3D& point) const override;
};

