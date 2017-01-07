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

void Rasterizer::render(const std::string output_path) const {
  std::vector<double> depth = std::vector<double>(m_image_height * m_image_width, std::numeric_limits<double>::max());

  for (auto& geometry_object : m_world->m_objects) {
    const std::vector<Triangle3D> triangles_of_object = geometry_object->tessellate();
    for (auto& object_triangle : triangles_of_object) {
      const Triangle2D object_triangle_in_screen = m_world->m_camera->worldSpaceToScreenSpace(object_triangle);
      //TODO: Bounding box optimization
      for (uint16_t i = 0; i < m_image_width * m_image_height; ++i) {
        uint16_t pixel_image_x, pixel_image_y;
        Utils::convert1DIndexto2DIndex(pixel_image_x, pixel_image_y, i, m_image_width, m_image_height);
        RGBColor pixel = m_pixels[i];

        const Point3D pixel_world = m_world->m_camera->imageSpaceToWorldSpace(pixel_image_x, pixel_image_y);
        const Point2D pixel_screen = Point2D(pixel_world.x, pixel_world.y);

        if (object_triangle_in_screen.contains(pixel_screen)) {
          const double distance_to_camera = m_world->m_camera->getDepth(pixel_world, object_triangle);
          if (distance_to_camera < depth[i]) {
            pixel = geometry_object->m_color;
            depth[i] = distance_to_camera;
          }
        }
      }
    }
  }

  exportImage(output_path);
};
