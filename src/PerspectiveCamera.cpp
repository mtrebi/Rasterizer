#include "PerspectiveCamera.h"
#define _USE_MATH_DEFINES

#include <cmath>
PerspectiveCamera::PerspectiveCamera()
  : Camera() {
}

PerspectiveCamera::PerspectiveCamera(const Point3D& position, const Point3D& target, const uint32_t image_height, const uint32_t image_width, Renderer * renderer, const uint32_t near, const uint32_t far, const float fov)
  : Camera(position, target, image_height, image_width, renderer, near, far), m_fov(fov) {
  m_zoom = 1 / tan((fov/ 2) * 3.1415926535897 / 180);


  const float tan_half_fov = tan((m_fov / 2) * 3.1415926535897 / 180);
  const double z_range = m_far - m_near;
  
  m_project[0][0] = 1 / (tan_half_fov * get_aspect());     m_project[0][1] = 0;                                     m_project[0][2] = 0;                                     m_project[0][3] = 0;
  m_project[1][0] = 0;                                     m_project[1][1] = 1 / tan_half_fov;                      m_project[1][2] = 0;                                     m_project[1][3] = 0;
  m_project[2][0] = 0;                                     m_project[2][1] = 0;                                     m_project[2][2] = m_far / z_range;                        m_project[2][3] = 1;
  m_project[3][0] = 0;                                     m_project[3][1] = 0;                                     m_project[3][2] = (m_far * m_near) / -z_range;       m_project[3][3] = 0;
  
  m_project = glm::transpose(m_project);

  m_project_inv = glm::inverse(m_project);
}

PerspectiveCamera::~PerspectiveCamera() {

}

// NDC [-1,1] to Camera space
const Point3D PerspectiveCamera::projectTransformInv(const Point2D& point_projected, const double depth) const {
  const glm::vec4 point = glm::vec4(point_projected.x * depth, point_projected.y * depth, depth, 1);
  const glm::vec4 r = point * m_project_inv;
  return Point3D(r.x, r.y, r.z * depth);
}


const Vector3D PerspectiveCamera::viewDirection(const Point3D& point) const {
  Vector3D view = point - m_position;
  view.normalize();
  return view;
}
