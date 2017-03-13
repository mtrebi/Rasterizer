#ifndef RENDERER_H
#define RENDERER_H

#include <cstdint>
#include <vector>
#include <string>

#include "RGBColor.h"
class World;

#include "World.h"
const RGBColor BACKGROUND_COLOR = RGBColor(1.0f, 1.0f, 1.0f);

class Renderer {
protected:
  const World* m_world;
  std::vector<RGBColor> m_pixels;
  Camera * m_camera;

public:
  Renderer();
  Renderer(const World* world);
  ~Renderer();
   
  void set_camera(Camera * camera) { m_camera = camera;  }
  Camera * get_camera() { return m_camera;  }
  virtual void render(const bool use_shade = true, const bool use_shadow_maps = true) = 0;
  virtual void export_output(const std::string output_path) const = 0;
protected:
  void exportImage(const std::vector<RGBColor> pixels, const std::string export_path, const uint16_t image_width, const uint16_t image_height) const;
};


#endif /* RENDERER_H */

