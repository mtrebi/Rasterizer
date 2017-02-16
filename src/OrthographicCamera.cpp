#include "OrthographicCamera.h"
#include <limits>
OrthographicCamera::OrthographicCamera()
  : Camera() {

}

OrthographicCamera::OrthographicCamera(const Point3D& position, const Point3D& target, const uint32_t image_height, const uint32_t image_width, Renderer * renderer)
  : Camera(position, target, image_height, image_width, renderer) {

  const float z_range = m_near - m_far;
  const float tan_half_fov = tan((90 / 2) * 3.1415926535897 / 180);

  m_project[0][0] = 1 / get_aspect();                                      m_project[0][1] = 0;                                     m_project[0][2] = 0;                                     m_project[0][3] = 0;
  m_project[1][0] = 0;                                     m_project[1][1] = 1;                                     m_project[1][2] = 0;                                     m_project[1][3] = 0;
  m_project[2][0] = 0;                                     m_project[2][1] = 0;                                     m_project[2][2] = 2 / z_range;                   m_project[2][3] = 1;
  m_project[3][0] = 0;                                     m_project[3][1] = 0;                                     m_project[3][2] = -(m_far + m_near) / z_range;       m_project[3][3] = 0;

  m_project_inv = glm::inverse(m_project);

}

OrthographicCamera::~OrthographicCamera() {

}


const Vector3D OrthographicCamera::viewDirection(const Point3D& point) const {
  return m_direction;
}