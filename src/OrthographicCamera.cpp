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

const Point3D OrthographicCamera::imageSpaceToWorldSpace(const uint16_t pixel_image_x, const uint16_t pixel_image_y) const {
  //TODO: anctual conversion
  return Point3D();
}


const Triangle2D OrthographicCamera::worldSpaceToScreenSpace(const Triangle3D& triangle3D) const {
  //Because is an orthographic projection, we just get x and y 
  return Triangle2D{
    Point2D(triangle3D.v1.x, triangle3D.v1.y),
    Point2D(triangle3D.v2.x, triangle3D.v2.y),
    Point2D(triangle3D.v3.x, triangle3D.v3.y)
  };
}

const float OrthographicCamera::getDepth(const Point3D& pixel_world, const Triangle3D& triangle) const {
  //TODO: Get Z coordinate
  
  bool out_hit;
  const Point3D intersection_point = triangle.intersect(out_hit, pixel_world, this->m_forward);
  if (!out_hit) {
    return std::numeric_limits<float>::max();
  }

  return pixel_world.distance(intersection_point);
}
