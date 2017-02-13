#include "GeometryObject.h"
#include <cassert>
#include <math.h>       /* fmod */
#define _USE_MATH_DEFINES
#include <math.h>       /* sin */
GeometryObject::GeometryObject() {

}

GeometryObject::GeometryObject(Material* material, const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<Vector2D>& texture_coords, const std::vector<uint32_t>& indices)
  : m_material(material), m_vertices(vertices), m_colors(colors), m_texture_coords(texture_coords), m_indices(indices) {
  
}

GeometryObject::~GeometryObject() {

}

const Vertex3D GeometryObject::build_vertex(const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<Vector2D>& texture_coords, const uint32_t vertex_index) const {
  Vertex3D v;
  
  v.position = vertices[vertex_index];
  v.color = (colors.size() > 1) ? colors[vertex_index] : RGBColor();
  v.texture_coords = (texture_coords.size() > 1) ? texture_coords[vertex_index] : Vector2D();

  return v;
}

void GeometryObject::rotate(const float roll_degrees, const float pitch_degrees, const float yaw_degrees) {
  const float roll_radians = ((roll_degrees / 180.0) * M_PI);
  const float pitch_radians = ((pitch_degrees / 180.0) * M_PI);
  const float yaw_radians = ((yaw_degrees / 180.0) * M_PI);
  for (auto& point : m_vertices) {
    point = rotation_roll(point, roll_radians);
    point = rotation_yaw(point, yaw_radians);
    point = rotation_pitch(point, pitch_radians);
  }
}

const Point3D GeometryObject::rotation_roll(const Point3D& point, const float amount_r) const {
  const Point3D rotated_point(
    point.x,
    point.y * cos(amount_r) + point.z * -sin(amount_r),
    point.y * sin(amount_r) + point.z * cos(amount_r)
  );
  return rotated_point;
}
const Point3D GeometryObject::rotation_pitch(const Point3D& point, const float amount_p) const { 
  const Point3D rotated_point(
    point.x * cos(amount_p) + point.z * -sin(amount_p),
    point.y,
    point.x * sin(amount_p) + point.z * cos(amount_p)
  );
  
  return rotated_point;
}
const Point3D GeometryObject::rotation_yaw(const Point3D& point, const float amount_y) const {
  const Point3D rotated_point(
    point.x * cos(amount_y) + point.y * -sin(amount_y),
    point.x * sin(amount_y) + point.y * cos(amount_y),
    point.z
  );

  return rotated_point;
}

const std::vector<Triangle3D> GeometryObject::triangles() const { 
  assert(m_indices.size() % 3 == 0 && "Indices array must be made up of triangles");
  assert((m_colors.size() == 0 || m_vertices.size() == m_colors.size()) && "Vertices size and colors size should match");
  assert((m_texture_coords.size() == 0 || m_vertices.size() == m_texture_coords.size()) && "Vertices size and texture coordinates size should match");

  std::vector<Triangle3D> triangles;
  for (int i = 0; i < m_indices.size(); i += 3) {
    Triangle3D triangle = Triangle3D(
      build_vertex(m_vertices, m_colors, m_texture_coords, m_indices[i]),
      build_vertex(m_vertices, m_colors, m_texture_coords, m_indices[i + 1]),
      build_vertex(m_vertices, m_colors, m_texture_coords, m_indices[i + 2])
    );
    triangle.v1.normal = triangle.normal;
    triangle.v2.normal = triangle.normal;
    triangle.v3.normal = triangle.normal;

    triangles.push_back(triangle);
  }

  return triangles;
}
const Material* GeometryObject::material() const { 
  return m_material; 
}