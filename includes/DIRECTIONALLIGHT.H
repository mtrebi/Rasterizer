#pragma once
#include "LIGHT.H"
class DirectionalLight : public Light {
private:
  Vector3D m_direction;
public:
  DirectionalLight();
  DirectionalLight(const RGBColor& color, const Vector3D& direction);

  const Vector3D getDirectionToPoint(const Point3D& point) const override;

  ~DirectionalLight();
};

