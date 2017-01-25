#ifndef CAMERA_H
#define CAMERA_H

#include <cstdint>

#include "Point2D.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Triangle.h"

class Camera {
protected:
  const Vector3D 
    m_forward = { 0, 0, 1 },
    m_up = { 0, 1, 0 },
    m_left = { 1, 0, 0 };
  const uint32_t 
    m_near = 10, 
    m_far = 1000;

  Point3D m_position;
  uint32_t m_image_height,
    m_image_width;
public:
    Camera();
    Camera(const Point3D& position, const uint32_t image_height, const uint32_t image_width);
    ~Camera();

    virtual const Vector3D viewDirection(const Point3D point) const = 0;
    virtual const Point3D viewTransform(const Point3D& point_world) const = 0;
    virtual const Point2D projectTransform(const Point3D& point_camera) const = 0;
};

#endif /* CAMERA_H */

