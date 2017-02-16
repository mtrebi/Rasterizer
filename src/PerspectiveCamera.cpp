#include "PerspectiveCamera.h"
#define _USE_MATH_DEFINES

#include <cmath>
PerspectiveCamera::PerspectiveCamera()
  : Camera() {
}

PerspectiveCamera::PerspectiveCamera(const Point3D& position, const Point3D& target, const uint32_t image_height, const uint32_t image_width, Renderer * renderer, const float fov)
  : Camera(position, target, image_height, image_width, renderer), m_fov(fov) {
  m_zoom = 1 / tan((fov/ 2) * 3.1415926535897 / 180);


  const float z_range = m_near - m_far;
  const float tan_half_fov = tan((m_fov / 2) * 3.1415926535897 / 180);

  m_perspective[0][0] = 1 / (tan_half_fov * get_aspect());     m_perspective[0][1] = 0;                                     m_perspective[0][2] = 0;                                     m_perspective[0][3] = 0;
  m_perspective[1][0] = 0;                                     m_perspective[1][1] = 1 / tan_half_fov;                      m_perspective[1][2] = 0;                                     m_perspective[1][3] = 0;
  m_perspective[2][0] = 0;                                     m_perspective[2][1] = 0;                                     m_perspective[2][2] = (m_far + m_near) / z_range;            m_perspective[2][3] = 1;
  m_perspective[3][0] = 0;                                     m_perspective[3][1] = 0;                                     m_perspective[3][2] = (-2 * m_near * m_far) / z_range;       m_perspective[3][3] = 0;

  m_perspective_inv = glm::inverse(m_perspective);
}

PerspectiveCamera::~PerspectiveCamera() {

}

const Vector3D PerspectiveCamera::viewDirection(const Point3D& point) const {
  Vector3D view = point - m_position;
  view.normalize();
  return view;
}

const Point2D PerspectiveCamera::projectTransform(const Point3D& point_camera) const {
  // Perspective divide
  const glm::vec4 point = glm::vec4(point_camera.x, point_camera.y, point_camera.z, 1);
  const glm::vec4 r = point * m_perspective;
  const Point3D point_projected(r.x/r.w, r.y/r.w, r.z/r.w);

  return point_projected;
}

const Point3D PerspectiveCamera::projectTransformInv(const Point2D& point_projected, const double depth) const {
  const glm::vec4 point = glm::vec4(point_projected.x, point_projected.y, depth, 1);
  const glm::vec4 r = point * m_perspective_inv;
  const Point3D point_world(r.x * r.w, r.y * r.w, r.z * r.w);

  return point_world;
}