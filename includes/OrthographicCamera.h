#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "Camera.h"

class OrthographicCamera : public Camera {
public:
  OrthographicCamera();
  OrthographicCamera(const Point3D& position, const Point3D& target, const uint32_t image_height, const uint32_t m_image_width, Renderer * renderer, const uint32_t near = 2, const uint32_t far = 5000);
  ~OrthographicCamera();

  const Point3D projectTransformInv(const Point2D& point_projected, const double depth) const override;

  const Vector3D viewDirection(const Point3D& point) const override;
};

#endif // !ORTHOGRAPHICCAMERA_H
