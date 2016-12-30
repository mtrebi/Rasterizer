#include "Camera.h"

Camera::Camera()
	: m_position(Point3D()) {
}

Camera::Camera(const Point3D& position, const Vector3D& forward, const Vector3D& up)
	: m_position(position), m_forward(forward), m_up(up), m_left(up^forward) {

}

Camera::~Camera(){

}