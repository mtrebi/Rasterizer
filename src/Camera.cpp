#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(const Point3D& position, const uint32_t image_height, const uint32_t image_width)
  : m_position(position), m_image_height(image_height), m_image_width(image_width) {

}

Camera::~Camera(){

}

const bool Camera::insideFrustrum(const Point2D& point_raster, const float depth) const {
  const float half_w = m_image_width / 2;
  const float half_h = m_image_height / 2;
  return (point_raster.x < half_w && point_raster.x > -half_w &&
    point_raster.y < half_h && point_raster.y > -half_h &&
    depth > m_near && depth < m_far);
}