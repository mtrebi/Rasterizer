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
public:
  Renderer();
  Renderer(World* world);
  ~Renderer();
    
  virtual void render(const uint16_t image_width, const uint16_t image_height, const std::string output_path) const = 0;
protected:
  void exportImage(const uint16_t image_width, const uint16_t image_height, const std::string export_path) const;
};


#endif /* RENDERER_H */

