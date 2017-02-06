#include "Rasterizer.h"

Rasterizer::Rasterizer()
  : Renderer() {

}

Rasterizer::Rasterizer(World* world)
  : Renderer(world) {

}

Rasterizer::~Rasterizer() {
}


void Rasterizer::render(const std::string output_path, const uint16_t image_width, const uint16_t image_height) {
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
          const Point2D pixel_raster = { (double) pixel_raster_x, (double) pixel_raster_y };
          if (triangle_raster.contains(pixel_raster)) {
            const Point2D pixel_projected = this->unproject(pixel_raster);
            const double depth = calculateDepth(triangle_world, triangle_projected, pixel_projected);
            const Point3D pixel_view = m_camera->projectTransformInv(pixel_projected, depth);
            const Point3D pixel_world = m_camera->viewTransformInv(pixel_view);
            if (m_camera->insideFrustrum(pixel_raster, depth)) {
              const uint32_t i = pixel_raster_y * image_width + pixel_raster_x;
              if (depth < m_depth_buffer[i]) {
                const Vertex3D vertex = calculateVertexAttributes(triangle_world, pixel_world);
                m_pixels[i] = object->material()->shade(m_world->m_lights, *m_world->m_camera, vertex);
                m_depth_buffer[i] = depth;
              }
            }
          }
        }
      }
    }
  }

  exportDepthBuffer(m_depth_buffer, "depth.bmp", image_width, image_height);
  exportImage(m_pixels, output_path, image_width, image_height);
}

const Vertex3D Rasterizer::calculateVertexAttributes(const Triangle3D& triangle_world, const Point3D& point_world) const {
  const Vertex3D v {
    point_world,
    calculateColor(triangle_world, point_world),
    calculateTextureCoords(triangle_world, point_world),
    triangle_world.normal // TODO: Use normal maps
  };

  return v;
}

const double Rasterizer::calculateDepth(const Triangle3D& triangle_world, const Triangle2D& triangle_screen, const Point2D& pixel_screen) const {
  const Triangle3D triangle_camera = Triangle3D(
    Vertex3D (m_camera->viewTransform(triangle_world.v1.position), triangle_world.v1.color, triangle_world.v1.texture_coords, triangle_world.v1.normal),
    Vertex3D(m_camera->viewTransform(triangle_world.v2.position), triangle_world.v2.color, triangle_world.v2.texture_coords, triangle_world.v1.normal),
    Vertex3D(m_camera->viewTransform(triangle_world.v3.position), triangle_world.v3.color, triangle_world.v3.texture_coords, triangle_world.v1.normal)
  );

  // Calculate barycentric coords in camera space
  double u, v, w;
  triangle_screen.calculateBarycentricCoords(u, v, w, pixel_screen);
  // Interpolate Z in 3D using inverse function and barycentric coordinates in 2D
  const float depth = 1 / ((1 / triangle_camera.v1.position.z) * u + (1 / triangle_camera.v2.position.z) * v + (1 / triangle_camera.v3.position.z) * w);
  return depth;
}

const Vector2D Rasterizer::calculateTextureCoords(const Triangle3D& triangle_world, const Point3D& point_world) const {
  // Calculate barycentric coords in camera space
  double u, v, w;
  triangle_world.calculateBarycentricCoords(u, v, w, point_world);
  const Vector2D texture_coords = triangle_world.v1.texture_coords * u + triangle_world.v2.texture_coords * v + triangle_world.v3.texture_coords * w;
  const Vector2D texture_coords_abs {
    abs(texture_coords.x),
    abs(texture_coords.y)

  };
  return texture_coords_abs;
}

const RGBColor Rasterizer::calculateColor(const Triangle3D& triangle_world, const Point3D& point_world) const {
  // Calculate barycentric coords in camera space
  double u, v, w;
  triangle_world.calculateBarycentricCoords(u, v, w, point_world);
  const RGBColor new_color = triangle_world.v1.color * u + triangle_world.v2.color * v + triangle_world.v3.color * w;
  return new_color;
}

const Point2D Rasterizer::rasterize(const Point3D& point_world) const {
  const Point3D point_camera = m_camera->viewTransform(point_world);
  const Point2D point_projected = m_camera->projectTransform(point_camera);
  const Point2D point_ndc = m_camera->ndcTransform(point_projected);
  const Point2D point_raster = m_camera->viewportTransform(point_ndc);
  return point_raster;
}

const Triangle2D Rasterizer::rasterize(const Triangle3D& triangle_world) const {
  return Triangle2D(
    rasterize(triangle_world.v1.position),
    rasterize(triangle_world.v2.position),
    rasterize(triangle_world.v3.position)
  );
}

const Triangle2D Rasterizer::project(const Triangle3D& triangle_world) const {
  return Triangle2D(
    project(triangle_world.v1.position),
    project(triangle_world.v2.position),
    project(triangle_world.v3.position)
  );
}

const Point2D Rasterizer::project(const Point3D& point_world) const {
  const Point3D point_camera = m_camera->viewTransform(point_world);
  const Point2D point_projected = m_camera->projectTransform(point_camera);
  return point_projected;
}

const Point2D Rasterizer::unproject(const Point2D& point_raster) const {
  const Point2D point_ndc = m_camera->viewportTransformInv(point_raster);
  const Point2D point_projected = m_camera->ndcTransformInv(point_ndc);
  return point_projected;
}

void Rasterizer::exportDepthBuffer(const std::vector<double>& depth_buffer, const std::string output_path, const uint16_t image_width, const uint16_t image_height) const {
  std::vector<RGBColor> depth_buffer_grey(image_height*image_width, RGBColor(1.0));
  for (int i = 0; i < depth_buffer.size(); ++i) {
    const double depth = depth_buffer[i];
    if (depth != m_camera->get_far_plane()) {
      // Convert depth in the range [near, far] to [0,1]
      const double slope = 1.0 / (m_camera->get_far_plane() - m_camera->get_near_plane());
      const double depth_normalized = slope * (depth - m_camera->get_near_plane());
      depth_buffer_grey[i] = RGBColor(depth_normalized);
    }
  }
  exportImage(depth_buffer_grey, output_path, image_width, image_height);
}