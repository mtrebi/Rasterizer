#include "Rasterizer.h"
#include <limits>   //numerics::max
#include "Utils.h"  //

Rasterizer::Rasterizer()
  : Renderer() {

}

Rasterizer::Rasterizer(World* world, const uint16_t image_width, const uint16_t image_height)
  : Renderer(world, image_width, image_height) {

}

Rasterizer::~Rasterizer(){
}
void Rasterizer::render(const std::string output_path) {
  std::vector<double> depth = std::vector<double>(m_image_height * m_image_width, std::numeric_limits<double>::max());
  for (auto& geometry_object : m_world->m_objects) {
    const std::vector<Triangle3D> triangles_of_object = geometry_object->tessellate();
    for (auto& triangle_world : triangles_of_object) {
      const Triangle2D triangle_projected = m_world->m_camera->worldSpaceToScreenSpace(triangle_world);
      //TODO: Bounding box optimization
      for (uint32_t i = 0; i < (m_image_width * m_image_height); ++i) {
        uint16_t c = m_image_width * m_image_height;

        uint16_t pixel_image_x, pixel_image_y;
        Utils::convert1DIndexto2DIndex(pixel_image_x, pixel_image_y, i, m_image_width, m_image_height);

        const Point3D pixel_world = m_world->m_camera->imageSpaceToWorldSpace(m_image_width, m_image_height, pixel_image_x, pixel_image_y);
        const Point2D pixel_screen = Point2D(pixel_world.x, pixel_world.y);

        if (triangle_projected.contains(pixel_screen)) {
          const double current_depth = m_world->m_camera->getDepth(triangle_world, triangle_projected, pixel_screen);
          if (current_depth < depth[i]) {
            m_pixels[i] = geometry_object->m_color;
            depth[i] = current_depth;
          }
        }
      }
    }
  }

  
  //TODO Calculate illumination (fragment shader)

  exportImage(output_path);
};
