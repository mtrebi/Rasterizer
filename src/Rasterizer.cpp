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

//TODO: Move image dimensions to camera
void Rasterizer::render(const std::string output_path) {
  std::vector<double> depth = std::vector<double>(m_image_height * m_image_width, std::numeric_limits<double>::max());
  for (auto& geometry_object : m_world->m_objects) {
    const std::vector<Triangle3D> triangles_of_object = geometry_object->tessellate();
    for (auto& triangle_world : triangles_of_object) {
      const Triangle2D triangle_projected = m_world->m_camera->worldSpaceToScreenSpace(triangle_world);

      Point2D bbox_min, bbox_max;
      triangle_projected.calculateBBox(bbox_min, bbox_max);
      const Point2D bbox_min_screen = m_world->m_camera->cameraToScreen(m_image_width, m_image_height, bbox_min);
      const Point2D bbox_max_screen = m_world->m_camera->cameraToScreen(m_image_width, m_image_height, bbox_max);

      for (uint16_t pixel_image_x = bbox_min_screen.x; pixel_image_x < bbox_max_screen.x; ++pixel_image_x) {
        for (uint16_t pixel_image_y = bbox_min_screen.y; pixel_image_y < bbox_max_screen.y; ++pixel_image_y) {
          const Point2D pixel_screen = (Point2D) m_world->m_camera->imageSpaceToWorldSpace(m_image_width, m_image_height, pixel_image_x, pixel_image_y);
          
          if (triangle_projected.contains(pixel_screen)) {
            const uint32_t i = Utils::convert2DIndexto1DIndex(pixel_image_x, pixel_image_y, m_image_width, m_image_height);
            const double pixel_depth = m_world->m_camera->getDepth(triangle_world, triangle_projected, pixel_screen);
            if (pixel_depth < depth[i]) {
              m_pixels[i] = geometry_object->m_color;
              depth[i] = pixel_depth;
            }
          }
        }
      }
    }
  }

  
  //TODO Calculate illumination (fragment shader)

  exportImage(output_path);
};
