#include "OrthographicCamera.h"
#include <limits>
OrthographicCamera::OrthographicCamera()
  : Camera() {

}

OrthographicCamera::OrthographicCamera(const Point3D& position, const Point3D& target, const uint32_t image_height, const uint32_t image_width, Renderer * renderer, const uint32_t near, const uint32_t far)
  : Camera(position, target, image_height, image_width, renderer, near, far) {

  const double z_range = m_far - m_near;

  m_project[0][0] = 2.0 / image_width;                     m_project[0][1] = 0;                       m_project[0][2] = 0;                      m_project[0][3] = 0;
  m_project[1][0] = 0;                                     m_project[1][1] = 2.0 / image_height;      m_project[1][2] = 0;                      m_project[1][3] = 0;
  m_project[2][0] = 0;                                     m_project[2][1] = 0;                       m_project[2][2] = 1.0 / z_range;          m_project[2][3] = 0;
  m_project[3][0] = 0;                                     m_project[3][1] = 0;                       m_project[3][2] = m_near / z_range;       m_project[3][3] = 1;

  m_project = glm::transpose(m_project);
  m_project_inv = glm::inverse(m_project);

}

OrthographicCamera::~OrthographicCamera() {

}

// NDC [-1,1] to Camera space
const Point3D OrthographicCamera::projectTransformInv(const Point2D& point_projected, const double depth) const {
  const glm::vec4 point = glm::vec4(point_projected.x, point_projected.y, depth, 1);
  const glm::vec4 r = point * m_project_inv;
  return Point3D(r.x, r.y, depth);
}




const Vector3D OrthographicCamera::viewDirection(const Point3D& point) const {
  return m_direction;
}