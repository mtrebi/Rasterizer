#include "..\includes\DeferredRasterizer.h"

DeferredRasterizer::DeferredRasterizer() {
}

DeferredRasterizer::DeferredRasterizer(World* world)
  : Rasterizer(world) {

}

DeferredRasterizer::~DeferredRasterizer() {
}


void DeferredRasterizer::render() {
  const uint16_t image_width = m_camera->get_width();
  const uint16_t image_height = m_camera->get_height();

  m_pixels = std::vector<RGBColor>(image_height * image_width, BACKGROUND_COLOR);
  m_depth_buffer = std::vector<double>(image_height * image_width, m_camera->get_far_plane());
  m_normal_buffer = std::vector<RGBColor>(image_height * image_width, BACKGROUND_COLOR);
  m_color_buffer = std::vector<RGBColor>(image_height * image_width, BACKGROUND_COLOR);
  m_diffuse_buffer = std::vector<RGBColor>(image_height * image_width, BACKGROUND_COLOR);
  m_specular_buffer = std::vector<RGBColor>(image_height * image_width, BACKGROUND_COLOR);


  // Render color, depth and normals
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
                const Fragment fragment = calculateFragmentAttributes(triangle_world, pixel_world, triangle_projected, pixel_projected, *object->material());

                //TODO: Use one-single buffer of fragment objects
                m_depth_buffer[i] = depth;
                m_normal_buffer[i] = (RGBColor) fragment.normal;
                m_color_buffer[i] = fragment.color;
                m_diffuse_buffer[i] = fragment.diffuse;
                m_specular_buffer[i] = fragment.specular;
              }
            }
          }
        }
      }
    }
  }

  // Calculate lighting only ONCE in screen space
  for (int x = 0; x < image_width; ++x) {
    for (int y = 0; y < image_height; ++y) {
      const uint32_t i = y * image_width + x;
      const double depth = m_depth_buffer[i];
      if (depth < m_camera->get_far_plane()) {
        const Point2D pixel_raster(x, y);
        const Point2D pixel_projected = this->unproject(pixel_raster);
        const Point3D pixel_view = m_camera->projectTransformInv(pixel_projected, m_depth_buffer[i]);
        const Point3D pixel_world = m_camera->viewTransformInv(pixel_view);

        Fragment fragment{
          pixel_world,
          m_color_buffer[i],
          m_diffuse_buffer[i],
          m_specular_buffer[i],
          (Vector3D)m_normal_buffer[i]
        };
        m_pixels[i] = Material::shade(m_world->m_lights, *m_world->m_camera, fragment);
      }
      else {
        m_pixels[i] = BACKGROUND_COLOR;
      }
    }
  }
}

void DeferredRasterizer::export_output(const std::string output_path) const {
  const uint16_t image_width = m_camera->get_width();
  const uint16_t image_height = m_camera->get_height();

  exportDepthBuffer(m_depth_buffer, "d_depth.bmp", image_width, image_height);
  exportImage(m_normal_buffer, "d_normals.bmp", image_width, image_height);
  exportImage(m_color_buffer, "d_colors.bmp", image_width, image_height);
  exportImage(m_diffuse_buffer, "d_diffuse.bmp", image_width, image_height);
  exportImage(m_specular_buffer, "d_specular.bmp", image_width, image_height);
  exportImage(m_pixels, "d_" + output_path, image_width, image_height);
}