#pragma once
#include "CAMERA.H"
class PerspectiveCamera : public Camera {
public:
  float m_fov, m_zoom;
  glm::mat4 m_perspective,
    m_perspective_inv;
public:

  PerspectiveCamera();
  PerspectiveCamera(const Point3D& position, const Point3D& target, const uint32_t image_height, const uint32_t m_image_width, Renderer * renderer, const float fov = 90.0f);
  ~PerspectiveCamera();

  const Point2D projectTransform(const Point3D& point_camera) const;
  const Point3D projectTransformInv(const Point2D& pixel_projected, const double depth) const;

  const Vector3D viewDirection(const Point3D& point) const;
};

