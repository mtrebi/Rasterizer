#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "Camera.h"

class OrthographicCamera : public Camera {
public:
  OrthographicCamera();
  OrthographicCamera(const Point3D& position, const Point3D& target, const uint32_t image_height, const uint32_t m_image_width, Renderer * renderer);
  ~OrthographicCamera();

  const Point2D projectTransform(const Point3D& point_camera) const;
  const Point3D projectTransformInv(const Point2D& pixel_projected, const double depth) const;

  const Vector3D viewDirection(const Point3D& point) const;
};

#endif // !ORTHOGRAPHICCAMERA_H
