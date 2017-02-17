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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {
protected:
  Vector3D
    m_direction,
    m_right,
    m_up;

  glm::mat4
    m_lookat,
    m_lookat_inv,
    m_project,
    m_project_inv;

  const uint32_t 
    m_near = 2, 
    m_far = 5000;

  Point3D m_position;
  uint32_t m_image_height,
    m_image_width;

  Renderer * m_renderer;
public:
    Camera();
    Camera(const Point3D& position, const Point3D& target, const uint32_t image_height, const uint32_t image_width, Renderer * renderer);
    ~Camera();

    inline const uint32_t get_near_plane() const { return m_near; }
    inline const uint32_t get_far_plane() const { return m_far; }

    inline const uint32_t get_width() const { return m_image_width; }
    inline const uint32_t get_height() const { return m_image_height; }


    void rotate(const float roll_degrees, const float pitch_degrees, const float yaw_degrees);
    void render() const;

    const bool insideFrustrum(const Point2D& point_raster, const float depth) const;
    
    // Transformations
    const Point3D viewTransform(const Point3D& point_world) const;
    const Point3D viewTransformInv(const Point3D& point_camera) const;

    const Point2D viewportTransform(const Point2D& point_ndc) const;
    const Point2D viewportTransformInv(const Point2D& point_raster) const;

    const Point2D projectTransform(const Point3D& point_camera) const;
    virtual const Point3D projectTransformInv(const Point2D& point_projected, const double depth) const = 0;

    virtual const Vector3D viewDirection(const Point3D& point) const = 0;
protected:
  inline const double get_aspect() const { return (float) m_image_width / m_image_height; }
  const Point3D rotation_roll(const Point3D& point, const float amount_r) const;
  const Point3D rotation_pitch(const Point3D& point, const float amount_p) const;
  const Point3D rotation_yaw(const Point3D& point, const float amount_y) const;

};

#endif /* CAMERA_H */

