#include "DirectionalLight.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"
#include "RASTERIZER.H"
#include "ForwardRasterizer.H"

DirectionalLight::DirectionalLight()
  : Light() {

}

DirectionalLight::DirectionalLight(const RGBColor & color, const Vector3D & direction)
  : Light(color) {

  Vector3D direction_norm = direction;
  direction_norm.normalize();
  m_direction = direction_norm;
}

DirectionalLight::~DirectionalLight(){

}

const Point3D DirectionalLight::getPosition() const {
  Point3D light_pos(
    m_direction.x * DIRECTIONAL_LIGHT_DISTANCE,
    m_direction.y * DIRECTIONAL_LIGHT_DISTANCE,
    m_direction.z * DIRECTIONAL_LIGHT_DISTANCE
  );

  return light_pos;
}

const Vector3D DirectionalLight::getDirectionToPoint(const Point3D & point) const {
  return m_direction;
}