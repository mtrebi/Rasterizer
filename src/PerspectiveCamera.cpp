#include "PerspectiveCamera.h"
#define _USE_MATH_DEFINES

#include <cmath>
PerspectiveCamera::PerspectiveCamera()
  : Camera() {
}

PerspectiveCamera::PerspectiveCamera(const Point3D& position, const Point3D& target, const uint32_t image_height, const uint32_t image_width, Renderer * renderer, const float fov)
  : Camera(position, target, image_height, image_width, renderer), m_fov(fov) {
  m_zoom = 1 / tan((fov/ 2) * 3.1415926535897 / 180);
}

PerspectiveCamera::~PerspectiveCamera() {

}

const Vector3D PerspectiveCamera::viewDirection(const Point3D& point) const {
  Vector3D view = point - m_position;
  view.normalize();
  return view;
}

// TODO: generic
const Point2D PerspectiveCamera::projectTransform(const Point3D& point_camera) const {
  // Perspective divide
  const double z_norm = ((m_far + m_near) / (m_far - m_near)) + 
                      (1 / point_camera.z) * ((2.0 * m_near*m_far) / (m_far - m_near));

  const Point2D point_projected = {
    (point_camera.x  * m_zoom) / (z_norm ),
    (point_camera.y  * m_zoom) / (z_norm )
  };

  return point_projected;
}

const Point3D PerspectiveCamera::projectTransformInv(const Point2D& point_projected, const double depth) const {
  const double z_norm = ((m_far + m_near) / (m_far - m_near)) + 
                      (1 / depth) * ((2 * m_near*m_far) / (m_far - m_near));

  const Point3D point_world = {
    (point_projected.x * z_norm ) / (m_zoom),
    (point_projected.y * z_norm ) / (m_zoom),
    depth
  };

  return point_world;
}