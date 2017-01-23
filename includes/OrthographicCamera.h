#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "Camera.h"

class OrthographicCamera : public Camera {
public:
  OrthographicCamera();
  OrthographicCamera(const Point3D& position, const Vector3D& forward = Vector3D(.0f, .0f, 1.0f), const Vector3D& up = Vector3D(.0f, 1.0f, .0f), const uint32_t near = 10, const uint32_t far = 1000, const float zoom = 1.0f);
  ~OrthographicCamera();

  virtual const Vector3D viewDirection(const Point3D point) const override;
  virtual const Triangle2D worldSpaceToScreenSpace(const Triangle3D& triangle3D) const override;
  virtual const Point3D imageSpaceToWorldSpace(const uint16_t image_width, const uint16_t image_height, const uint16_t pixel_image_x, const uint16_t pixel_image_y) const override;
  virtual const Point2D OrthographicCamera::cameraToScreen(const uint16_t image_width, const uint16_t image_height, const Point2D& point_camera) const override;
  virtual const float getDepth(const Triangle3D& triangle_world, const Triangle2D& triangle_screen, const Point2D& pixel_screen) const override;
};

#endif // !ORTHOGRAPHICCAMERA_H
