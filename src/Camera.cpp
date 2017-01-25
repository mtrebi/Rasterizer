#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(const Point3D& position, const uint32_t image_height, const uint32_t image_width)
  : m_position(position), m_image_height(image_height), m_image_width(image_width) {

}

Camera::~Camera(){

}