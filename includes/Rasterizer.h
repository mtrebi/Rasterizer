#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <string>

#include "Renderer.h"

class Rasterizer : public Renderer {
private:
  const float k_a = 0.1;
  const RGBColor AMBIENT_COLOR = RGBColor(1.0f, 1.0f, 1.0f);
public:
  Rasterizer();
  Rasterizer(World* world, const uint16_t image_width, const uint16_t image_height);
  ~Rasterizer();
  
  const RGBColor shade(const GeometryObject& object, const Triangle3D& triangle, const Point3D point_in_triangle) const override;
  void render(const std::string output_path) override;
private:
  const RGBColor phongShading(const Material& material, const RGBColor& base_color, const Triangle3D& triangle, const Point3D& point_in_triangle) const;
  const RGBColor blinnPhongShading(const Material& material, const RGBColor& base_color, const Triangle3D& triangle, const Point3D& point_in_triangle) const;
  const float getDepth(const Triangle3D& triangle_world, const Triangle2D& triangle_raster, const Point2D& pixel_raster) const;

  // Transformations
  const Point2D toRaster(const Point3D& point) const;
  const Triangle2D toRaster(const Triangle3D& triangle_world) const;
  const Point2D viewportTransform(const Point2D& point_ndc) const;
};

#endif /* RASTERIZER_H */

