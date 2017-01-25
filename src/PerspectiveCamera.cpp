#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera()
  : Camera() {
}

PerspectiveCamera::PerspectiveCamera(const Point3D& position, const uint32_t image_height, const uint32_t image_width, const float fov)
  : Camera(position, image_height, image_width), m_fov(fov) {

}

PerspectiveCamera::~PerspectiveCamera() {

}

const Vector3D PerspectiveCamera::viewDirection(const Point3D point) const {
  Vector3D view = point - m_position;
  view.normalize();
  return view;
}

const Point3D PerspectiveCamera::viewTransform(const Point3D& point_world) const {
  const Point3D point_camera = {
    point_world.x * m_left.x + point_world.y * m_up.x + point_world.z * m_forward.x - m_position.x,
    point_world.x * m_left.y + point_world.y * m_up.y + point_world.z * m_forward.y - m_position.y,
    point_world.x * m_left.z + point_world.y * m_up.z + point_world.z * m_forward.z - m_position.z
  };
  return point_camera;
}

// TODO: generic
const Point2D PerspectiveCamera::projectTransform(const Point3D& point_camera) const {
  //const float n = 10, f = 100;
  //const float r = (f + n) / (f - n);
  //float z = point_camera.z * r + ((2*n*f)/(f-n));
  // Perspective divide
  const Point2D point_projected = {
    (float)((point_camera.x * m_near / point_camera.z)),
    (float)((point_camera.y * m_near / point_camera.z))
  };

  const double slopeX = 1.0 / (m_image_width);
  const double slopeY = 1.0 / (m_image_height);

  const Point2D point_ndc = {
    (float)(slopeX * (point_projected.x + m_image_width / 2.0)),
    (float)(slopeY * (point_projected.y + m_image_height / 2.0))
  };
  return point_ndc;
}
