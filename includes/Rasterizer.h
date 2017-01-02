#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <string>

#include "Renderer.h"

class Rasterizer : public Renderer {
public:
    Rasterizer();
    Rasterizer(World* world);
    ~Rasterizer();
    
    void render(const uint16_t image_width, const uint16_t image_height, const std::string output_path) const override;
};

#endif /* RASTERIZER_H */

