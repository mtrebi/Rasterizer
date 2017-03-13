#pragma once
#include "LIGHT.H"

class PointLight : public Light {
private:
  Point3D m_position;
public:
  PointLight();
  PointLight(const RGBColor& color, const Point3D& position);
  ~PointLight();

  const Point3D getPosition() const override;
  const Vector3D getDirectionToPoint(const Point3D& point) const override;
  const std::vector<double> getShadowMap(const World* world) const override;
};

