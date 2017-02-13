#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(const Point3D& position, const uint32_t image_height, const uint32_t image_width, Renderer * renderer)
  : m_position(position), m_image_height(image_height), m_image_width(image_width), m_renderer(renderer) {
  m_renderer->set_camera(this);
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

//TODO: generic
const Point3D Camera::viewTransformInv(const Point3D& point_camera) const {
  const Point3D point_world = {
    (point_camera.x + m_position.x) / m_left.x,
    (point_camera.y + m_position.y) / m_up.y,
    (point_camera.z + m_position.z) / m_forward.z
  };
  return point_world;
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
  const double slopeX = 1.0 / (m_image_width);
  const double slopeY = 1.0 / (m_image_height);

  const Point2D point_ndc = {
    (float)(slopeX * (point_projected.x + m_image_width / 2.0)),
    (float)(slopeY * (point_projected.y + m_image_height / 2.0))
  };
  return point_ndc;
}

const Point2D Camera::ndcTransformInv(const Point2D& point_ndc) const {
  const double slopeX = 1.0 / (m_image_width);
  const double slopeY = 1.0 / (m_image_height);

  const Point2D point_projected = {
    point_ndc.x / slopeX - m_image_width / 2.0,
    point_ndc.y / slopeY - m_image_height / 2.0
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
