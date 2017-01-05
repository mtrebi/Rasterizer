#include "Rasterizer.h"
#include <limits>   //numerics::max
#include "Utils.h"  //

Rasterizer::Rasterizer()
    : Renderer(), m_depth(std::vector<double>(m_image_height * m_image_width, std::numeric_limits<double>::max())) {

}

Rasterizer::Rasterizer(World* world, const uint16_t image_width, const uint16_t image_height)
    : Renderer(world, image_width, image_height), m_depth(std::vector<double>(m_image_height * m_image_width, std::numeric_limits<double>::max())) {

}

Rasterizer::~Rasterizer(){
  m_depth.clear();
}

//TODO: render to m_pixels
void Rasterizer::render(const std::string output_path) const {
  
  //TODO: object tessellation, object has color --> tessellation in triangles
  const RGBColor obj_color = RGBColor(255, 0, 0); 
  for (auto& triangle3D : m_world->m_objects) {
    const Triangle2D triangle2D = m_world->m_camera->projectToScreen(triangle3D);

    for (uint16_t i = 0; i < m_image_width * m_image_height; ++i) {
      RGBColor pixel = m_pixels[i];
      uint16_t pixel_x, pixel_y;
      Utils::convert1DIndexto2DIndex(pixel_x, pixel_y, i, m_image_width, m_image_height);

      const Point2D pixel_position = Point2D(pixel_x, pixel_y);

      if (triangle2D.hasInside(pixel_position) {
        const uint16_t pixel_depth = //DISTANCE TO CAMERA? z axis?
        if (pixel_depth < m_depth[i]){
          pixel.color = obj_color;
          m_depth = pixel_depth;
        }
      }
    }
  }

  exportImage(output_path);
};
