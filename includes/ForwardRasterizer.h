#pragma once

#include "RASTERIZER.H"

class ForwardRasterizer : public Rasterizer {
public:
  ForwardRasterizer();
  ForwardRasterizer(World* world);
  ~ForwardRasterizer();

  void render() override;
  void export_output(const std::string output_path) const override;
};

