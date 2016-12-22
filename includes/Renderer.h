#ifndef RENDERER_H
#define RENDERER_H

#include <cstdint>
#include <vector>
#include <string>

#include "RGBColor.h"
#include "World.h"

class Renderer {
protected:
    std::vector<RGBColor> m_pixels;
    World * m_world;
public:
    Renderer();
    Renderer(const World* world);
    ~Renderer();
    
    void render(const uint16_t image_width, const uint16_t image_height, const string& output_path) const = 0;
protected:
    void export(const uint16_t image_width, const uint16_t image_height, const string& export_path) const;
};


#endif /* RENDERER_H */

