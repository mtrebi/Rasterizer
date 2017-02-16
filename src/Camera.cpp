#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>       /* sin */
Camera::Camera() {

}

Camera::Camera(const Point3D& position, const Point3D& target, const uint32_t image_height, const uint32_t image_width, Renderer * renderer)
  : m_position(position), m_image_height(image_height), m_image_width(image_width), m_renderer(renderer) {
  m_renderer->set_camera(this);

  m_direction = (target - position);
  m_direction.normalize();

  m_right = -(m_direction ^ Vector3D(0, 1, 0));
  m_right.normalize();

  m_up = m_direction ^ m_right;
  m_up.normalize();

  glm::mat4 orientation;
  orientation[0][0] = m_right.x;       orientation[0][1] = m_right.y;       orientation[0][2] = m_right.z;       orientation[0][3] = 0;
  orientation[1][0] = m_up.x;          orientation[1][1] = m_up.y;          orientation[1][2] = m_up.z;          orientation[1][3] = 0;
  orientation[2][0] = m_direction.x;   orientation[2][1] = m_direction.y;   orientation[2][2] = m_direction.z;   orientation[2][3] = 0;
  orientation[3][0] = 0;               orientation[3][1] = 0;               orientation[3][2] = 0;               orientation[3][3] = 1;


  glm::mat4 translation;
  translation[0][0] = 1;               translation[0][1] = 0;               translation[0][2] = 0;               translation[0][3] = -m_position.x;
  translation[1][0] = 0;               translation[1][1] = 1;               translation[1][2] = 0;               translation[1][3] = -m_position.y;
  translation[2][0] = 0;               translation[2][1] = 0;               translation[2][2] = 1;               translation[2][3] = -m_position.z;
  translation[3][0] = 0;               translation[3][1] = 0;               translation[3][2] = 0;               translation[3][3] = 1;

  m_lookat = translation * orientation;
  m_lookat_inv = glm::inverse(m_lookat);
}

Camera::~Camera(){

}

const Point3D Camera::viewTransform(const Point3D& point_world) const {
  glm::vec4 p = glm::vec4(point_world.x, point_world.y, point_world.z, 1);
  glm::vec4 r = p * m_lookat;

  return Point3D(r.x, r.y, r.z);
}

const Point3D Camera::viewTransformInv(const Point3D& point_camera) const {
  glm::vec4 p = glm::vec4(point_camera.x, point_camera.y, point_camera.z, 1);
  glm::vec4 r = p * m_lookat_inv;

  return Point3D(r.x, r.y, r.z);;
}

const Point2D Camera::viewportTransform(const Point2D& point_ndc) const {
  const Point2D point_raster = {
    point_ndc.x * m_image_width,
    point_ndc.y * m_image_height,
  };

  return point_raster;
}

const Point2D Camera::viewportTransformInv(const Point2D& point_raster) const {
  const Point2D point_ndc = {
    point_raster.x / m_image_width,
    point_raster.y / m_image_height,
  };

  return point_ndc;
}

const Point2D Camera::ndcTransform(const Point2D& point_projected) const { 
  double slope = 1.0 / (1 - -1);

  const Point2D point_ndc = {
    (float)(slope * (point_projected.x - -1)),
    (float)(slope * (point_projected.y - -1))
  };

  return point_ndc;
}

const Point2D Camera::ndcTransformInv(const Point2D& point_ndc) const {
  const double slope = 1.0 * (1 - -1);;

  const Point2D point_projected = {
    (float)(-1 + slope * (point_ndc.x)),
    (float)(-1 + slope * (point_ndc.y))
  };

  return point_projected;
}


const bool Camera::insideFrustrum(const Point2D& point_raster, const float depth) const {
  return (point_raster.x < m_image_width && point_raster.x >= 0 &&
    point_raster.y < m_image_height && point_raster.y >= 0 &&
    depth >= m_near && depth <= m_far);
}

void Camera::render() const {
  m_renderer->render();
}