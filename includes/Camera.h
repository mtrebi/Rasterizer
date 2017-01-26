#ifndef CAMERA_H
#define CAMERA_H

class Renderer;
class World;
#include <cstdint>

#include "Point2D.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Triangle.h"
#include "Renderer.h"

class Camera {
protected:
  const Vector3D 
    m_forward = { 0, 0, 1 },
    m_up = { 0, 1, 0 },
    m_left = { 1, 0, 0 };
  const uint32_t 
    m_near = 1, 
    m_far = 100;

  Point3D m_position;
  uint32_t m_image_height,
    m_image_width;

  Renderer * m_renderer;
public:
    Camera();
    Camera(const Point3D& position, const uint32_t image_height, const uint32_t image_width, Renderer * renderer);
    ~Camera();

    inline const uint32_t get_near_plane() const { return m_near; }
    inline const uint32_t get_far_plane() const { return m_far; }

    void render(const std::string output_name) const;

    const bool insideFrustrum(const Point2D& point_raster, const float depth) const;
    const Point3D viewTransform(const Point3D& point_world) const;
    const Point2D viewportTransform(const Point2D& point_ndc) const;
     virtual const Vector3D viewDirection(const Point3D point) const = 0;
    virtual const Point2D projectTransform(const Point3D& point_camera) const = 0;
};

#endif /* CAMERA_H */

