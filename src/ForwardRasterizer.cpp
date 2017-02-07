#include "..\includes\ForwardRasterizer.h"

ForwardRasterizer::ForwardRasterizer(){
}

ForwardRasterizer::ForwardRasterizer(World* world)
  : Rasterizer(world) {

}

ForwardRasterizer::~ForwardRasterizer() {
}


void ForwardRasterizer::render(const std::string output_path, const uint16_t image_width, const uint16_t image_height) {
  m_pixels = std::vector<RGBColor>(image_height * image_width, BACKGROUND_COLOR);
  m_depth_buffer = std::vector<double>(image_height * image_width, m_camera->get_far_plane());

  for (auto& object : m_world->m_objects) {
    const std::vector<Triangle3D> triangles = object->triangles();
    for (auto& triangle_world : triangles) {
      const Triangle2D triangle_projected = this->project(triangle_world);
      const Triangle2D triangle_raster = this->rasterize(triangle_world);
      const BoundingBox2D bbox_raster = triangle_raster.bbox();
      for (int32_t pixel_raster_x = bbox_raster.min.x; pixel_raster_x <= bbox_raster.max.x; ++pixel_raster_x) {
        for (int32_t pixel_raster_y = bbox_raster.min.y; pixel_raster_y <= bbox_raster.max.y; ++pixel_raster_y) {
          const Point2D pixel_raster = { (double)pixel_raster_x, (double)pixel_raster_y };
          if (triangle_raster.contains(pixel_raster)) {
            const Point2D pixel_projected = this->unproject(pixel_raster);
            const double depth = calculateDepth(triangle_world, triangle_projected, pixel_projected);
            const Point3D pixel_view = m_camera->projectTransformInv(pixel_projected, depth);
            const Point3D pixel_world = m_camera->viewTransformInv(pixel_view);
            if (m_camera->insideFrustrum(pixel_raster, depth)) {
              const uint32_t i = pixel_raster_y * image_width + pixel_raster_x;
              if (depth < m_depth_buffer[i]) {
                const Fragment fragment = calculateFragmentAttributes(triangle_world, pixel_world, *object->material());
                m_pixels[i] = object->material()->shade(m_world->m_lights, *m_world->m_camera, fragment);
                m_depth_buffer[i] = depth;
              }
            }
          }
        }
      }
    }
  }

  exportDepthBuffer(m_depth_buffer, "f_depth.bmp", image_width, image_height);
  exportImage(m_pixels, "f_" + output_path, image_width, image_height);
}