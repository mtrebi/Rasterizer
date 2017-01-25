#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(const Point3D& position, const uint32_t image_height, const uint32_t image_width)
  : m_position(position), m_image_height(image_height), m_image_width(image_width) {

}

Camera::~Camera(){

}

const bool Camera::insideFrustrum(const Point2D& point_raster, const float depth) const {
  return (point_raster.x < m_image_width && point_raster.x >= 0 &&
    point_raster.y < m_image_height && point_raster.y >= 0 &&
    depth >= m_near && depth <= m_far);
}