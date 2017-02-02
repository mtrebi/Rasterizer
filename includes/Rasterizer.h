#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <string>

#include "Renderer.h"

class Rasterizer : public Renderer {
private:
  const float k_a = 0.1;
  const RGBColor AMBIENT_COLOR = RGBColor(1.0f, 1.0f, 1.0f);
  std::vector<double> m_depth_buffer;

public:
  Rasterizer();
  Rasterizer(World* world);
  ~Rasterizer();
  
  const RGBColor shade(const Material& material, const RGBColor& color, const Triangle3D& triangle, const Point3D point_in_triangle) const override;
  void render(const std::string output_path, const uint16_t image_width, const uint16_t image_height) override;
private:
  const RGBColor phongShading(const Material& material, const RGBColor& base_color, const Triangle3D& triangle, const Point3D& point_in_triangle) const;
  const RGBColor blinnPhongShading(const Material& material, const RGBColor& base_color, const Triangle3D& triangle, const Point3D& point_in_triangle) const;
  const double getDepth(const Triangle3D& triangle_world, const Triangle2D& triangle_camera, const Point2D& pixel_camera) const;
  const RGBColor getColor(const Triangle3D& triangle_world, const Point3D& point_world) const;
  const Vector2D getTextureCoords(const Triangle3D& triangle_world, const Point3D& point_world) const;

  // Transformations
  const Triangle2D rasterize(const Triangle3D& triangle_world) const;
  const Point2D rasterize(const Point3D& point) const;

  const Triangle2D project(const Triangle3D& triangle_world) const;
  const Point2D project(const Point3D& point_world) const;
 
  const Point2D unproject(const Point2D& point_raster) const;


  const Point2D viewportTransform(const Point2D& point_ndc) const;

  void exportDepthBuffer(const std::vector<double>& depth_buffer, const std::string output_path, const uint16_t image_width, const uint16_t image_height) const;

};

#endif /* RASTERIZER_H */

