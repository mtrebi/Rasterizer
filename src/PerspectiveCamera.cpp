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

  m_project[0][0] = 1 / (tan_half_fov * get_aspect());     m_project[0][1] = 0;                                     m_project[0][2] = 0;                                     m_project[0][3] = 0;
  m_project[1][0] = 0;                                     m_project[1][1] = 1 / tan_half_fov;                      m_project[1][2] = 0;                                     m_project[1][3] = 0;
  m_project[2][0] = 0;                                     m_project[2][1] = 0;                                     m_project[2][2] = (m_far + m_near) / z_range;            m_project[2][3] = 1;
  m_project[3][0] = 0;                                     m_project[3][1] = 0;                                     m_project[3][2] = (-2 * m_near * m_far) / z_range;       m_project[3][3] = 0;

  m_project_inv = glm::inverse(m_project);
}

PerspectiveCamera::~PerspectiveCamera() {

}

const Vector3D PerspectiveCamera::viewDirection(const Point3D& point) const {
  Vector3D view = point - m_position;
  view.normalize();
  return view;
}
