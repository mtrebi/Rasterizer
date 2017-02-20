#include "GeometryObject.h"
#include <cassert>
#include <math.h>       /* fmod */
#define _USE_MATH_DEFINES
#include <math.h>       /* sin */
GeometryObject::GeometryObject() {

}

GeometryObject::GeometryObject(Material* material, const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<Vector2D>& texture_coords, const std::vector<uint32_t>& indices, const Point3D& center)
  : m_material(material), m_vertices(vertices), m_colors(colors), m_texture_coords(texture_coords), m_indices(indices), m_center(center.x, center.y, center.z) {
  
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
  const float roll_r = ((roll_degrees / 180.0) * M_PI);
  const float pitch_r = ((pitch_degrees / 180.0) * M_PI);
  const float yaw_r = ((yaw_degrees / 180.0) * M_PI);

  // Model transformation (Local object space to World)
  glm::mat4 mat_roll, mat_pitch, mat_yaw, mat_rotation, mat_translation;
  mat_roll = glm::rotate(glm::mat4(1.0f), roll_r, glm::vec3(1.0f, 0.0f, 0.0f));
  mat_pitch = glm::rotate(glm::mat4(1.0f), pitch_r, glm::vec3(0.0f, 1.0f, 0.0f));
  mat_yaw = glm::rotate(glm::mat4(1.0f), yaw_r, glm::vec3(0.0f, 0.0f, 1.0f));

  mat_rotation = mat_yaw * mat_pitch * mat_roll;
  mat_translation = glm::translate(mat_translation, m_center);

  for (auto& point : m_vertices) {
    glm::vec4 p(point.x, point.y, point.z, 1);
    glm::vec4 r = mat_translation * mat_rotation  * p;
    point = Point3D(r.x, r.y, r.z);
  }
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