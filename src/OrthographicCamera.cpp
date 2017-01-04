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
  return Triangle2D();
}
