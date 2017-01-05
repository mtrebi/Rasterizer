#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera()
  : Camera() {

}

OrthographicCamera::OrthographicCamera(const Point3D& position, const Vector3D& forward, const Vector3D& up, const uint32_t near, const uint32_t far)
  : Camera(position, forward, up, near, far) {

}

OrthographicCamera::~OrthographicCamera() {

}

const Triangle2D OrthographicCamera::projectToScreen(const Triangle3D& triangle3D) const {
  //TODO: actual projection
  return Triangle2D();
}

const float OrthographicCamera::getDepth(const Point3D& pixel_world, const Triangle3D& triangle) const {
  // Create line from camera position in camera_fwd direction
    // return line
  // Calculate intersection between this line and triangle/object
    // return intersection point
  // Calculate distance between two points
    // return distance
}
