#include "PointLight.h"

PointLight::PointLight() 
  : Light() {
}

PointLight::PointLight(const RGBColor& color, const Point3D& position)
  : Light(color), m_position(position) {

}

const Vector3D PointLight::getDirectionToPoint(const Point3D& point) const {
  Vector3D light_direction = point - m_position;
  light_direction.normalize();
  return light_direction;
}


PointLight::~PointLight()
{
}
