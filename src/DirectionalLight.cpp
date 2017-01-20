#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
  : Light() {

}

DirectionalLight::DirectionalLight(const RGBColor & color, const Vector3D & direction)
  : Light(color) {

  Vector3D direction_norm = direction;
  direction_norm.normalize();
  m_direction = direction;
}


const Vector3D DirectionalLight::getDirectionToPoint(const Point3D & point) const {
  return m_direction;
}

DirectionalLight::~DirectionalLight()
{
}
