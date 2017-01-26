#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "Camera.h"

class OrthographicCamera : public Camera {
public:
  OrthographicCamera();
  OrthographicCamera(const Point3D& position, const uint32_t image_height, const uint32_t m_image_width, Renderer * renderer);
  ~OrthographicCamera();

  const Vector3D viewDirection(const Point3D point) const override;
  const Point2D projectTransform(const Point3D& point_camera) const override;
};

#endif // !ORTHOGRAPHICCAMERA_H
