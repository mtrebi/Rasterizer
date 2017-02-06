#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <string>
#include "Renderer.h"

class Rasterizer : public Renderer {
protected:
  std::vector<double> m_depth_buffer;

public:
  Rasterizer();
  Rasterizer(World* world);
  ~Rasterizer();
  
  virtual void render(const std::string output_path, const uint16_t image_width, const uint16_t image_height) = 0;
protected:
  // Interpolations
  const double calculateDepth(const Triangle3D& triangle_world, const Triangle2D& triangle_camera, const Point2D& pixel_camera) const;
  const Vector2D calculateTextureCoords(const Triangle3D& triangle_world, const Point3D& point_world) const;
  const RGBColor calculateColor(const Triangle3D& triangle_world, const Point3D& point_world) const;
  const Vertex3D calculateVertexAttributes(const Triangle3D& triangle_world, const Point3D& point_world) const;

  // Transformations
  const Triangle2D rasterize(const Triangle3D& triangle_world) const;
  const Point2D rasterize(const Point3D& point) const;

  const Triangle2D project(const Triangle3D& triangle_world) const;
  const Point2D project(const Point3D& point_world) const;
  const Point2D unproject(const Point2D& point_raster) const;

  void exportDepthBuffer(const std::vector<double>& depth_buffer, const std::string output_path, const uint16_t image_width, const uint16_t image_height) const;
};

#endif /* RASTERIZER_H */

