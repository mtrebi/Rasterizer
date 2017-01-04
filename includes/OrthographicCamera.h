#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "Camera.h"

class OrthographicCamera : public Camera {
public:
  OrthographicCamera();
  OrthographicCamera(const Point3D& position, const Vector3D& forward = Vector3D(.0f, .0f, 1.0f), const Vector3D& up = Vector3D(.0f, 1.0f, .0f));
  ~OrthographicCamera();

  virtual const Triangle2D projectToScreen(const Triangle3D& triangle3D) const override;

};

#endif // !ORTHOGRAPHICCAMERA_H
