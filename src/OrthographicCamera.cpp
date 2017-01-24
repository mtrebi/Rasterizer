#include "OrthographicCamera.h"
#include <limits>
OrthographicCamera::OrthographicCamera()
  : Camera() {

}

OrthographicCamera::OrthographicCamera(const Point3D& position, const Vector3D& forward, const Vector3D& up, const uint32_t near, const uint32_t far, const float zoom)
  : Camera(position, forward, up, near, far, zoom) {

}

OrthographicCamera::~OrthographicCamera() {

}

const Point3D OrthographicCamera::viewTransform(const Point3D& point_world) const {
  const Point3D point_camera = {
    point_world.x * m_left.x + point_world.y * m_up.x + point_world.z * m_forward.x + m_position.x,
    point_world.x * m_left.y + point_world.y * m_up.y + point_world.z * m_forward.y + m_position.y,
    point_world.x * m_left.z + point_world.y * m_up.z + point_world.z * m_forward.z + m_position.z
  };
  return point_camera;
}



const Vector3D OrthographicCamera::viewDirection(const Point3D point) const {
  return m_forward;
}
/*

const Point3D OrthographicCamera::imageSpaceToWorldSpace(const uint16_t image_width, const uint16_t image_height, const uint16_t pixel_image_x, const uint16_t pixel_image_y) const {
  const float x_norm = (float) pixel_image_x / image_width;
  const float y_norm = (float) pixel_image_y / image_height;

  
  const float x = image_width * x_norm - image_width / 2.0;
  const float y = image_height * y_norm - image_height / 2.0;

  return Point3D(x, y, m_near);
  
}

const Point2D OrthographicCamera::cameraToScreen(const uint16_t image_width, const uint16_t image_height, const Point2D& point_camera) const {
  const float x = point_camera.x + image_width / 2;
  const float y = point_camera.y + image_height / 2;

  return Point2D(x, y);
}

const Triangle2D OrthographicCamera::worldSpaceToScreenSpace(const Triangle3D& triangle3D) const {
  // Because is an orthographic projection, we just get x and y 
  return Triangle2D{
    Point2D(triangle3D.v1.x, triangle3D.v1.y),
    Point2D(triangle3D.v2.x, triangle3D.v2.y),
    Point2D(triangle3D.v3.x, triangle3D.v3.y)
  };
}*/