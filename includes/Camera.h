#ifndef CAMERA_H
#define CAMERA_H

#include "Point3D.h"

class Camera {
private:
	Point3D m_position;
	Vector3D m_forward,
			m_up,
			m_left;

public:
    Camera();
    Camera(const Point3D& position, const Vector3D& forward = Vector3D(.0f, .0f, 1.0f), const Vector3D& up = Vector3D(.0f, 1.0f, .0f));
    ~Camera();
    //TODO
};

#endif /* CAMERA_H */

