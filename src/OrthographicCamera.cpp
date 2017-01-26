#include "OrthographicCamera.h"
#include <limits>
OrthographicCamera::OrthographicCamera()
  : Camera() {

}

OrthographicCamera::OrthographicCamera(const Point3D& position, const uint32_t image_height, const uint32_t image_width, Renderer * renderer)
  : Camera(position, image_height, image_width, renderer) {

}

OrthographicCamera::~OrthographicCamera() {

}

const Point2D OrthographicCamera::projectTransform(const Point3D& point_camera) const {
  const Point2D point_projected = {
    point_camera.x * m_near ,
    point_camera.y * m_near
  };

  const double slopeX = 1.0 / (m_image_width);
  const double slopeY = 1.0 / (m_image_height);

  const Point2D point_ndc = {
    (float) (slopeX * (point_projected.x + m_image_width / 2.0)),
    (float) (slopeY * (point_projected.y + m_image_height / 2.0))
  };
  return point_ndc;
}

const Vector3D OrthographicCamera::viewDirection(const Point3D point) const {
  return m_forward;
}