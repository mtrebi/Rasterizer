#pragma once

#include "RASTERIZER.H"

class ForwardRasterizer : public Rasterizer {
public:
  ForwardRasterizer();
  ForwardRasterizer(World* world);
  ~ForwardRasterizer();

  void render(const std::string output_path, const uint16_t image_width, const uint16_t image_height) override;
};

