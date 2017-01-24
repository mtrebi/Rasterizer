#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "Camera.h"

class OrthographicCamera : public Camera {
public:
  OrthographicCamera();
  OrthographicCamera(const Point3D& position, const Vector3D& forward = Vector3D(.0f, .0f, 1.0f), const Vector3D& up = Vector3D(.0f, 1.0f, .0f), const uint32_t near = 10, const uint32_t far = 1000, const float zoom = 1.0f);
  ~OrthographicCamera();

  const Vector3D viewDirection(const Point3D point) const override;


  const Point3D viewTransform(const Point3D& point_world) const override;

};

#endif // !ORTHOGRAPHICCAMERA_H
