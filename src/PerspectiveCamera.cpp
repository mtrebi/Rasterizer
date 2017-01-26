#include "PerspectiveCamera.h"
#define _USE_MATH_DEFINES

#include <cmath>
PerspectiveCamera::PerspectiveCamera()
  : Camera() {
}

PerspectiveCamera::PerspectiveCamera(const Point3D& position, const uint32_t image_height, const uint32_t image_width, Renderer * renderer, const float fov)
  : Camera(position, image_height, image_width, renderer), m_fov(fov) {
  m_zoom = 1 / tan((fov/ 2) * 3.1415926535897 / 180);
}

PerspectiveCamera::~PerspectiveCamera() {

}

const Vector3D PerspectiveCamera::viewDirection(const Point3D point) const {
  Vector3D view = point - m_position;
  view.normalize();
  return view;
}

// TODO: generic
const Point2D PerspectiveCamera::projectTransform(const Point3D& point_camera) const {
  const float r = (m_far + m_near) / (m_far - m_near);
  float z = point_camera.z * r + ((2*m_near*m_far)/(m_far-m_near));
  // Perspective divide
  const Point2D point_projected = {
    (point_camera.x * m_near * m_zoom) / z,
    (point_camera.y * m_near * m_zoom) / z
  };

  const double slopeX = 1.0 / (m_image_width);
  const double slopeY = 1.0 / (m_image_height);

  const Point2D point_ndc = {
    (float)(slopeX * (point_projected.x + m_image_width / 2.0)),
    (float)(slopeY * (point_projected.y + m_image_height / 2.0))
  };
  return point_ndc;
}
