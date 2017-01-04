#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera()
  : Camera() {

}

OrthographicCamera::OrthographicCamera(const Point3D& position, const Vector3D& forward, const Vector3D& up)
  : Camera(position, forward, up) {

}

OrthographicCamera::~OrthographicCamera() {

}

const Triangle2D OrthographicCamera::projectToScreen(const Triangle3D& triangle3D) const {
  return Triangle2D();
}
