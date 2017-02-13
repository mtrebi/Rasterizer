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
    point_camera.x * m_near * get_aspect(),
    point_camera.y * m_near * get_aspect(),
  };

  return point_projected;
}


const Point3D OrthographicCamera::projectTransformInv(const Point2D& pixel_projected, const double depth) const {
  const Point3D pixel_world = {
    (pixel_projected.x) / (m_near * get_aspect()),
    (pixel_projected.y) / (m_near * get_aspect()),
    depth
  };

  return pixel_world;
}

const Vector3D OrthographicCamera::viewDirection(const Point3D& point) const {
  return m_forward;
}