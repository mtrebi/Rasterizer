#ifndef RENDERER_H
#define RENDERER_H

#include <cstdint>
#include <vector>
#include <string>

#include "RGBColor.h"
#include "World.h"

const RGBColor BACKGROUND_COLOR = RGBColor(1.0f, 1.0f, 1.0f);

class Renderer {
protected:
  World* m_world;
  std::vector<RGBColor> m_pixels;
  Camera * m_camera;
public:
  Renderer();
  Renderer(World* world);
  ~Renderer();
    
  inline void set_camera(Camera * camera) { m_camera = camera; }

  virtual const RGBColor shade(const Material& material, const RGBColor& color, const Triangle3D& triangle, const Point3D point_in_triangle) const = 0;
  virtual void render(const std::string output_path, const uint16_t image_width, const uint16_t image_height) = 0;
protected:
  void exportImage(const std::vector<RGBColor> pixels, const std::string export_path, const uint16_t image_width, const uint16_t image_height) const;
};


#endif /* RENDERER_H */

