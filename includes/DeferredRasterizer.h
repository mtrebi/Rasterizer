#pragma once
#include "RASTERIZER.H"

class DeferredRasterizer : public Rasterizer {
private:
  std::vector<RGBColor> m_normal_buffer;
  std::vector<RGBColor> m_color_buffer;
  std::vector<RGBColor> m_diffuse_buffer;
  std::vector<RGBColor> m_specular_buffer;
public:
  DeferredRasterizer();
  DeferredRasterizer(World* world);
  ~DeferredRasterizer();

  void render(const std::string output_path, const uint16_t image_width, const uint16_t image_height) override;

private:

};