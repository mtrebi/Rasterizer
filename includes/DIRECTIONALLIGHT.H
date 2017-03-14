#pragma once
#include "LIGHT.H"

class DirectionalLight : public Light {
public:
  const double DIRECTIONAL_LIGHT_DISTANCE = 1000000.0;
private:
  Vector3D m_direction;
public:
  DirectionalLight();
  DirectionalLight(const RGBColor& color, const Vector3D& direction);
  ~DirectionalLight();

  const Point3D getPosition() const override;
  const Vector3D getDirectionToPoint(const Point3D& point) const override;
};

