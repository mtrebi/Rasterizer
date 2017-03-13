#include "PointLight.h"

PointLight::PointLight() 
  : Light() {
}

PointLight::PointLight(const RGBColor& color, const Point3D& position)
  : Light(color), m_position(position) {

}

PointLight::~PointLight()
{
}

const Point3D PointLight::getPosition() const {
  return m_position;
}

const Vector3D PointLight::getDirectionToPoint(const Point3D& point) const {
  Vector3D light_direction = point - m_position;
  light_direction.normalize();
  return light_direction;
}
// TODO
const std::vector<double> PointLight::getShadowMap(const World* world, const int image_height, const int image_width, Rasterizer * rasterizer_camera) const {
  return std::vector<double>();
}