#include "Camera.h"

Camera::Camera()
	: m_position(Point3D()) {
}

Camera::Camera(const Point3D& position, const Vector3D& forward, const Vector3D& up, const uint32_t near, const uint32_t far, const float zoom)
	: m_position(position), m_forward(forward), m_up(up), m_left(up^forward), m_near(near), m_far(far), m_zoom(zoom){

}

Camera::~Camera(){

}