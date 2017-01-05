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
public:
    Camera();
    Camera(const Point3D& position, const Vector3D& forward = Vector3D(.0f, .0f, 1.0f), const Vector3D& up = Vector3D(.0f, 1.0f, .0f), const uint32_t near = 10, const uint32_t far = 1000);
    ~Camera();
    
    virtual const Triangle2D projectToScreen(const Triangle3D& triangle3D) const = 0;
    virtual const float getDepth(const Point3D& pixel_world) const = 0;
    virtual const Point3D getPixelPosition(const Point3D& pixel_world) const = 0;

};

#endif /* CAMERA_H */

