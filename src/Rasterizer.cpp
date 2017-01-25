#include "Rasterizer.h"
#include <limits>   //numerics::max
#include "Utils.h"  //
#include <algorithm> // std::max
Rasterizer::Rasterizer()
  : Renderer() {

}

Rasterizer::Rasterizer(World* world, const uint16_t image_width, const uint16_t image_height)
  : Renderer(world, image_width, image_height) {

}

Rasterizer::~Rasterizer(){
}


void Rasterizer::render(const std::string output_path) {
  std::vector<double> depth = std::vector<double>(m_image_height * m_image_width, 1000);
  
  for (auto& object : m_world->m_objects) {
    const std::vector<Triangle3D> triangles = object->triangulate();
    for (auto& triangle : triangles) {
      const Triangle2D triangle_raster = this->toRaster(triangle);
      const BoundingBox2D bbox_raster = triangle_raster.calculateBBox();
      for (uint16_t pixel_x = bbox_raster.min.x; pixel_x < bbox_raster.max.x; ++pixel_x) {
        for (uint16_t pixel_y = bbox_raster.min.y; pixel_y < bbox_raster.max.y; ++pixel_y) {
          const Point2D pixel = { (double) pixel_x, (double) pixel_y };
          if(triangle_raster.contains(pixel)) {
            const Point3D  point_surface_triangle = this->interpolate3DPoint(triangle, triangle_raster, pixel);
            if (m_world->m_camera->insideFrustrum(pixel, point_surface_triangle.z)) {
              const uint32_t i = pixel_y * m_image_width + pixel_x;
              if (point_surface_triangle.z < depth[i]) {
                depth[i] = point_surface_triangle.z;
                m_pixels[i] = shade(*object, triangle, point_surface_triangle);
              }
            }
          }
        }
      }
    }
  }

  exportImage(output_path);
}

const Point2D Rasterizer::viewportTransform(const Point2D& point_ndc) const {
  const Point2D point_raster = {
    point_ndc.x * m_image_width,
    point_ndc.y * m_image_height,
  };

  return point_raster;
}

const Point2D Rasterizer::toRaster(const Point3D& point_world) const {
  const Point3D point_camera = m_world->m_camera->viewTransform(point_world);
  const Point2D point_ndc = m_world->m_camera->projectTransform(point_camera);
  const Point2D point_raster = viewportTransform(point_ndc);
  return point_raster;
}

const Triangle2D Rasterizer::toRaster(const Triangle3D& triangle_world) const {
  return Triangle2D(
    toRaster(triangle_world.v1),
    toRaster(triangle_world.v2),
    toRaster(triangle_world.v3)
  );
}

const Point3D Rasterizer::interpolate3DPoint(const Triangle3D& triangle_world, const Triangle2D& triangle_raster, const Point2D& pixel_raster) const {
  // Interpolate point in 3D triangle using barycentric coordinates of 2D triangle
  double u, v, w;
  triangle_raster.calculateBarycentricCoords(u, v, w, pixel_raster);
  const Point3D point_interpolated = triangle_world.v1 * u + triangle_world.v2 * v + triangle_world.v3 * w;
  const Point3D point_interpolated_camera = m_world->m_camera->viewTransform(point_interpolated);
  return point_interpolated_camera;
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
    const Vector3D V = m_world->m_camera->viewDirection(point_in_triangle);

    diffuse += material.k_d * light->getColor() * std::max((L * N), 0.0);
    specular += material.k_s * light->getColor() * pow(std::max((R * -V),0.0), material.k_shininess);
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
    Vector3D H = L + V;
    H.normalize();

    diffuse += material.k_d * light->getColor() * std::max((L * N), 0.0);
    specular += material.k_s * light->getColor() * pow(std::max((H * V), 0.0), material.k_shininess);
  }
  const RGBColor phong_result = (ambient + diffuse + specular) * base_color;
  return phong_result;
}

