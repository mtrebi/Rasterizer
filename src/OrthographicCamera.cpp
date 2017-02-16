#include "OrthographicCamera.h"
#include <limits>
OrthographicCamera::OrthographicCamera()
  : Camera() {

}

OrthographicCamera::OrthographicCamera(const Point3D& position, const Point3D& target, const uint32_t image_height, const uint32_t image_width, Renderer * renderer)
  : Camera(position, target, image_height, image_width, renderer) {

}

OrthographicCamera::~OrthographicCamera() {

}

const Point2D OrthographicCamera::projectTransform(const Point3D& point_camera) const {
  const Point2D point_projected = {
    (point_camera.x * get_aspect()),
    (point_camera.y * get_aspect()),
  };

  return point_projected;
}


const Point3D OrthographicCamera::projectTransformInv(const Point2D& pixel_projected, const double depth) const {
  const Point3D pixel_world = {
    (pixel_projected.x ) / (get_aspect()),
    (pixel_projected.y ) / (get_aspect()),
    depth
  };

  return pixel_world;
}

const Vector3D OrthographicCamera::viewDirection(const Point3D& point) const {
  return m_direction;
}