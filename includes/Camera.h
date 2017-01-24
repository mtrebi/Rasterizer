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
  float m_height, 
    m_width,
    m_fov;
public:
    Camera();
    Camera(const Point3D& position, const Vector3D& forward = Vector3D(.0f, .0f, 1.0f), const Vector3D& up = Vector3D(.0f, 1.0f, .0f), const uint32_t near = 10, const uint32_t far = 1000, const float fov = 1.0f);
    ~Camera();
    virtual const Vector3D viewDirection(const Point3D point) const = 0;

    virtual const Point3D viewTransform(const Point3D& point_world) const = 0;
};

#endif /* CAMERA_H */

