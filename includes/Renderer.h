#ifndef RENDERER_H
#define RENDERER_H

#include <cstdint>
#include <vector>
#include <string>

#include "RGBColor.h"
#include "World.h"

class Renderer {
protected:
  World* m_world;
  std::vector<RGBColor> m_pixels;
  uint16_t m_image_width,
            m_image_height;

  const RGBColor BACKGROUND_COLOR = RGBColor(1.0f, 1.0f, 1.0f);
public:
  Renderer();
  Renderer(World* world, const uint16_t image_width, const uint16_t image_height);
  ~Renderer();
    
  virtual void render(const std::string output_path) const = 0;
protected:
  void exportImage(const std::string export_path) const;
};


#endif /* RENDERER_H */

