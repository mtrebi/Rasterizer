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

//TODO: Move image dimensions to camera
void Rasterizer::render(const std::string output_path) {
  std::vector<double> depth = std::vector<double>(m_image_height * m_image_width, std::numeric_limits<double>::max());
  for (auto& object : m_world->m_objects) {
    const std::vector<Triangle3D> triangles_of_object = object->tessellate();
    for (auto& object_surface : triangles_of_object) {
      const Triangle2D triangle_projected = m_world->m_camera->worldSpaceToScreenSpace(object_surface);

      Point2D bbox_min, bbox_max;
      triangle_projected.calculateBBox(bbox_min, bbox_max);
      const Point2D bbox_min_screen = m_world->m_camera->cameraToScreen(m_image_width, m_image_height, bbox_min);
      const Point2D bbox_max_screen = m_world->m_camera->cameraToScreen(m_image_width, m_image_height, bbox_max);

      for (uint16_t pixel_image_x = bbox_min_screen.x; pixel_image_x < bbox_max_screen.x; ++pixel_image_x) {
        for (uint16_t pixel_image_y = bbox_min_screen.y; pixel_image_y < bbox_max_screen.y; ++pixel_image_y) {
          const Point3D surface_point = m_world->m_camera->imageSpaceToWorldSpace(m_image_width, m_image_height, pixel_image_x, pixel_image_y);
          const Point2D pixel_screen = (Point2D) surface_point;
          
          if (triangle_projected.contains(pixel_screen)) {
            const uint32_t i = Utils::convert2DIndexto1DIndex(pixel_image_x, pixel_image_y, m_image_width, m_image_height);
            const double pixel_depth = m_world->m_camera->getDepth(object_surface, triangle_projected, pixel_screen);
            if (pixel_depth < depth[i]) {
              depth[i] = pixel_depth;
              m_pixels[i] = shade(*object, object_surface, surface_point);
            }
          }
        }
      }
    }
  }

  exportImage(output_path);
};

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
    const Vector3D V = m_world->m_camera->viewDirection(point_in_triangle);
    Vector3D H = L + V;
    H.normalize();

    diffuse += material.k_d * light->getColor() * std::max((L * N), 0.0);
    specular += material.k_s * light->getColor() * pow(std::max((H * -V), 0.0), material.k_shininess);
  }
  const RGBColor phong_result = (ambient + diffuse + specular) * base_color;
  return phong_result;
}

