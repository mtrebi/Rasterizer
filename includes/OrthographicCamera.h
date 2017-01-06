#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "Camera.h"

class OrthographicCamera : public Camera {
public:
  OrthographicCamera();
  OrthographicCamera(const Point3D& position, const Vector3D& forward = Vector3D(.0f, .0f, 1.0f), const Vector3D& up = Vector3D(.0f, 1.0f, .0f), const uint32_t near = 10, const uint32_t far = 1000);
  ~OrthographicCamera();

  virtual const Triangle2D getScreenCoordinates(const Triangle3D& triangle3D) const override;
  virtual const float getDepth(const Point3D& pixel_world, const Triangle3D& triangle) const override;
};

#endif // !ORTHOGRAPHICCAMERA_H
