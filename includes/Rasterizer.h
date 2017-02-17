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
  
  inline const std::vector<double> get_depth_buffer() const { return m_depth_buffer; }

  virtual void render() = 0;
  virtual void export_output(const std::string output_path) const = 0;

protected:
  // Interpolations
  const double calculateDepth(const Triangle3D& triangle_world, const Triangle2D& triangle_camera, const Point2D& pixel_camera) const;
  //const Vector2D calculateTextureCoords(const Triangle3D& triangle_world, const Point3D& point_world) const;
  const Vector2D calculateTextureCoords(const Triangle3D& triangle_world, const Point3D& pixel_world, const Triangle2D& triangle_camera, const Point2D& pixel_camera) const;

  const RGBColor calculateColor(const Triangle3D& triangle_world, const Point3D& point_world) const;
  const Fragment calculateFragmentAttributes(const Triangle3D& triangle_world, const Point3D& point_world, const Triangle2D& triangle_screen, const Point2D& pixel_screen, const Material& material) const;

  // Transformations
  const Triangle2D rasterize(const Triangle3D& triangle_world) const;
  const Point2D rasterize(const Point3D& point) const;

  const Point3D unrasterize(const Point2D& point_raster, const double depth_from_camera) const;

  const Triangle2D project(const Triangle3D& triangle_world) const;
  const Point2D project(const Point3D& point_world) const;
  const Point2D unproject(const Point2D& point_raster) const;

  void exportDepthBuffer(const std::vector<double>& depth_buffer, const std::string output_path, const uint16_t image_width, const uint16_t image_height) const;
};

#endif /* RASTERIZER_H */

