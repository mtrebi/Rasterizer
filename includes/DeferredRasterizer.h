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
  DeferredRasterizer(const World* world);
  ~DeferredRasterizer();

  void render(const bool use_shade = true, const bool use_shadow_maps = true) override;
  void export_output(const std::string output_path) const override;

private:

};