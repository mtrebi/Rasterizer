#ifndef CAMERA_H
#define CAMERA_H

#include <cstdint>

#include "Point2D.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Triangle.h"

class Camera {
protected:
	Point3D m_position;
	Vector3D m_forward,
			m_up,
			m_left;
  uint32_t m_near, m_far;
  float m_zoom;
public:
    Camera();
    Camera(const Point3D& position, const Vector3D& forward = Vector3D(.0f, .0f, 1.0f), const Vector3D& up = Vector3D(.0f, 1.0f, .0f), const uint32_t near = 10, const uint32_t far = 1000, const float zoom = 1.0f);
    ~Camera();
      
    virtual const Triangle2D worldSpaceToScreenSpace(const Triangle3D& triangle3D) const = 0;
    virtual const Point3D imageSpaceToWorldSpace(const uint16_t image_width, const uint16_t image_height, const uint16_t pixel_image_x, const uint16_t pixel_image_y) const = 0;
    virtual const float getDepth(const Triangle3D& triangle_world, const Triangle2D& triangle_screen, const Point2D& pixel_screen) const = 0;
};

#endif /* CAMERA_H */

