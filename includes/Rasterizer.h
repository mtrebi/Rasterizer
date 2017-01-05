#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <string>

#include "Renderer.h"

class Rasterizer : public Renderer {
private:
  std::vector<double> m_depth;
public:
  Rasterizer();
  Rasterizer(World* world, const uint16_t image_width, const uint16_t image_height);
  ~Rasterizer();
    
  void render(const std::string output_path) const override;
};

#endif /* RASTERIZER_H */

