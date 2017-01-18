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

const float OrthographicCamera::getDepth(const Triangle3D& triangle_world, const Triangle2D& triangle_screen, const Point2D& pixel_screen) const {
  // Interpolate point in 3D triangle using barycentric coordinates of 2D triangle
  float u, v, w; 
  triangle_screen.calculateBarycentricCoords(u, v, w, pixel_screen);
  const Point3D point_interpolated = triangle_world.v1 * u + triangle_world.v2 * v + triangle_world.v3 * w;

  return point_interpolated.z;
}
