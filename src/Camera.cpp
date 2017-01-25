#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(const Point3D& position, const uint32_t image_height, const uint32_t image_width)
  : m_position(position), m_image_height(image_height), m_image_width(image_width) {

}

Camera::~Camera(){

}

const Point3D Camera::viewTransform(const Point3D& point_world) const {
  const Point3D point_camera = {
    point_world.x * m_left.x + point_world.y * m_up.x + point_world.z * m_forward.x - m_position.x,
    point_world.x * m_left.y + point_world.y * m_up.y + point_world.z * m_forward.y - m_position.y,
    point_world.x * m_left.z + point_world.y * m_up.z + point_world.z * m_forward.z - m_position.z
  };
  return point_camera;
}

const bool Camera::insideFrustrum(const Point2D& point_raster, const float depth) const {
  return (point_raster.x < m_image_width && point_raster.x >= 0 &&
    point_raster.y < m_image_height && point_raster.y >= 0 &&
    depth >= m_near && depth <= m_far);
}