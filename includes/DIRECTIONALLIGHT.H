#pragma once
#include "LIGHT.H"

class DirectionalLight : public Light {
private:
  Vector3D m_direction;
public:
  DirectionalLight();
  DirectionalLight(const RGBColor& color, const Vector3D& direction);
  ~DirectionalLight();

  const Vector3D getDirectionToPoint(const Point3D& point) const override;
  const std::vector<double> getShadowMap(const World* world, const int image_height, const int image_width, Rasterizer * rasterizer_camera) const override;
};

