#include "Rasterizer.h"
#include <limits>   //numerics::max
#include "Utils.h"  //
#include <algorithm> // std::max
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
    const std::vector<Triangle3D> triangles = object->triangulate();
    for (auto& triangle_world : triangles) {
      const Triangle2D triangle_projected = this->project(triangle_world);
      const Triangle2D triangle_raster = this->rasterize(triangle_world);
      const BoundingBox2D bbox_raster = triangle_raster.bbox();
      for (int32_t pixel_raster_x = bbox_raster.min.x; pixel_raster_x <= bbox_raster.max.x; ++pixel_raster_x) {
        for (int32_t pixel_raster_y = bbox_raster.min.y; pixel_raster_y <= bbox_raster.max.y; ++pixel_raster_y) {
          const Point2D pixel_raster = { (double) pixel_raster_x, (double) pixel_raster_y };
          if (triangle_raster.contains(pixel_raster)) {
            const Point2D pixel_projected = this->unproject(pixel_raster);
            const double depth = getDepth(triangle_world, triangle_projected, pixel_projected);
            const Point3D pixel_view = m_camera->projectTransformInv(pixel_projected, depth);
            const Point3D pixel_world = m_camera->viewTransformInv(pixel_view);
            if (m_camera->insideFrustrum(pixel_raster, depth)) {
              const uint32_t i = pixel_raster_y * image_width + pixel_raster_x;
              if (depth < m_depth_buffer[i]) {
                m_depth_buffer[i] = depth;
                m_pixels[i] = shade(*object, triangle_world, pixel_world);
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

const double Rasterizer::getDepth(const Triangle3D& triangle_world, const Triangle2D& triangle_screen, const Point2D& pixel_screen) const {
  const Triangle3D triangle_camera = Triangle3D(
    m_camera->viewTransform(triangle_world.v1),
    m_camera->viewTransform(triangle_world.v2),
    m_camera->viewTransform(triangle_world.v3)
  );

  // Calculate barycentric coords in camera space
  double u, v, w;
  triangle_screen.calculateBarycentricCoords(u, v, w, pixel_screen);
  // Interpolate Z in 3D using inverse function and barycentric coordinates in 2D
  const float depth = 1 / ((1 / triangle_camera.v1.z) * u + (1 / triangle_camera.v2.z) * v + (1 / triangle_camera.v3.z) * w);
  return depth;

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
    rasterize(triangle_world.v1),
    rasterize(triangle_world.v2),
    rasterize(triangle_world.v3)
  );
}

const Triangle2D Rasterizer::project(const Triangle3D& triangle_world) const {
  return Triangle2D(
    project(triangle_world.v1),
    project(triangle_world.v2),
    project(triangle_world.v3)
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


const RGBColor Rasterizer::shade(const GeometryObject& object, const Triangle3D& triangle, const Point3D point_in_triangle) const {
#ifdef _PHONG
  return phongShading(object.m_material, object.m_color, triangle, point_in_triangle);
#endif // _PHONG

#ifdef _BLINN_PHONG
  return blinnPhongShading(object.m_material, object.m_color, triangle, point_in_triangle);
#endif // _BLINN-PHONG
}

const RGBColor Rasterizer::phongShading(const Material& material, const RGBColor& base_color, const Triangle3D& triangle, const Point3D& point_in_triangle) const {
  const RGBColor ambient = AMBIENT_COLOR * k_a;

  RGBColor diffuse, specular;
  for (auto& light : m_world->m_lights) {
    const Vector3D L = -(light->getDirectionToPoint(point_in_triangle));
    const Vector3D N = triangle.normal;
    const Vector3D R = 2 * (N * L) * N - L;
    const Vector3D V = -(m_world->m_camera->viewDirection(point_in_triangle));

    diffuse += light->getColor() * material.k_d * std::max((L * N), 0.0);
    specular += light->getColor() *  material.k_s * pow(std::max((R * V), 0.0), material.k_shininess);
  }
  const RGBColor phong_result = (ambient + diffuse + specular) * base_color;
  return phong_result;
}

const RGBColor Rasterizer::blinnPhongShading(const Material& material, const RGBColor& base_color, const Triangle3D& triangle, const Point3D& point_in_triangle) const {
  const RGBColor ambient = AMBIENT_COLOR * k_a;

  RGBColor diffuse, specular;
  for (auto& light : m_world->m_lights) {
    const Vector3D L = -(light->getDirectionToPoint(point_in_triangle));
    const Vector3D N = triangle.normal;
    const Vector3D V = -(m_world->m_camera->viewDirection(point_in_triangle));
    // Halfway calculation: Can be moved outside to increase performance
    Vector3D H = V + L;
    H.normalize();
    float a = (H * V);
    diffuse += light->getColor() * material.k_d * std::max((L * N), 0.0);
    specular += light->getColor() * material.k_s  * pow(std::max((H * V), 0.0), material.k_shininess);
  }
  const RGBColor phong_result = (ambient + diffuse + specular) * base_color;
  return phong_result;
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