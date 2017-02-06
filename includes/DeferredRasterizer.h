#pragma once
#include "RASTERIZER.H"

class DeferredRasterizer : public Rasterizer {
public:
  DeferredRasterizer();
  DeferredRasterizer(World* world);
  ~DeferredRasterizer();

  void render(const std::string output_path, const uint16_t image_width, const uint16_t image_height) override;
};