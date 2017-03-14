#include "..\includes\ForwardRasterizer.h"

ForwardRasterizer::ForwardRasterizer(){
}

ForwardRasterizer::ForwardRasterizer(const World* world)
  : Rasterizer(world) {

}

ForwardRasterizer::~ForwardRasterizer() {
}


void ForwardRasterizer::render(const bool use_shade, const bool use_shadow_maps) {
  const uint16_t image_width = m_camera->get_width();
  const uint16_t image_height = m_camera->get_height();
  
  m_pixels = std::vector<RGBColor>(image_height * image_width, BACKGROUND_COLOR);
  m_depth_buffer = std::vector<double>(image_height * image_width, m_camera->get_far_plane());

  if (use_shadow_maps) {
    this->createShadowMaps();
  }

  for (auto& object : m_world->m_objects) {
    const std::vector<Triangle3D> triangles = object->triangles();
    for (auto& triangle_world : triangles) {
      const Triangle2D triangle_raster = this->rasterize(triangle_world);
      const BoundingBox2D bbox_raster = triangle_raster.bbox();
      for (int32_t pixel_raster_x = bbox_raster.min.x; pixel_raster_x <= bbox_raster.max.x; ++pixel_raster_x) {
        for (int32_t pixel_raster_y = bbox_raster.min.y; pixel_raster_y <= bbox_raster.max.y; ++pixel_raster_y) {
          const Point2D pixel_raster = { (double)pixel_raster_x, (double)pixel_raster_y };
          if (triangle_raster.contains(pixel_raster)) {
            const double depth = calculateDepth(triangle_world, triangle_raster, pixel_raster);
            const Point3D pixel_world = unrasterize(pixel_raster, depth);
            if (m_camera->insideFrustrum(pixel_raster, depth)) {
              const uint32_t i = pixel_raster_y * image_width + pixel_raster_x;
              if (depth < m_depth_buffer[i]) {
                const Fragment fragment = calculateFragmentAttributes(triangle_world, pixel_world, triangle_raster, pixel_raster, *object->material());
                m_depth_buffer[i] = depth;
                if (use_shade) {
                  const RGBColor object_color = Material::shade(m_world->m_lights, *m_world->m_camera, fragment);
                  const RGBColor shadow_factor = shadowFactor(pixel_world);
                  m_pixels[i] = object_color * shadow_factor;
                }
              }
            }
          }
        }
      }
    }
  }
}

void ForwardRasterizer::export_output(const std::string output_path) const {
  const uint16_t image_width = m_camera->get_width();
  const uint16_t image_height = m_camera->get_height();
  
  exportDepthBuffer(m_depth_buffer, "f_d_"+output_path, image_width, image_height);
  exportImage(m_pixels, "f_" + output_path, image_width, image_height);
}
