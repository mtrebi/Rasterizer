#pragma once
#include "LIGHT.H"

class PointLight : public Light {
private:
  Vector3D m_position;
public:
  PointLight();
  PointLight(const RGBColor& color, const Point3D& position);
  ~PointLight();

  const Vector3D getDirectionToPoint(const Point3D& point) const override;
  const std::vector<double> getShadowMap(const World* world, const int image_height, const int image_width, Rasterizer * rasterizer_camera) const override;
};

