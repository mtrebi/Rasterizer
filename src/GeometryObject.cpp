#include "GeometryObject.h"
#include <cassert>
#include <math.h>       /* fmod */
GeometryObject::GeometryObject() {

}

GeometryObject::GeometryObject(Material* material, const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<Vector2D>& texture_coords, const std::vector<uint32_t>& indices)
  : m_material(material), m_triangles(triangulate(vertices, colors, texture_coords, indices)) {
  
}

GeometryObject::~GeometryObject() {

}

const std::vector<Triangle3D> GeometryObject::triangulate(const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<Vector2D>& texture_coords, const std::vector<uint32_t>& indices) const {
  assert(indices.size() % 3 == 0 && "Indices array must be made up of triangles");
  assert((colors.size() == 0 || vertices.size() == colors.size()) && "Vertices size and colors size should match");
  assert((texture_coords.size() == 0 || vertices.size() == texture_coords.size()) && "Vertices size and texture coordinates size should match");

  std::vector<Triangle3D> triangles;
  for (int i = 0; i < indices.size(); i+=3) {
    Triangle3D triangle = Triangle3D(
      build_vertex(vertices, colors, texture_coords, indices[i]),
      build_vertex(vertices, colors, texture_coords, indices[i + 1]),
      build_vertex(vertices, colors, texture_coords, indices[i + 2])
    );
    triangle.v1.normal = triangle.normal;
    triangle.v2.normal = triangle.normal;
    triangle.v3.normal = triangle.normal;

    triangles.push_back(triangle);
  }
  
  return triangles;
}

const Vertex3D GeometryObject::build_vertex(const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<Vector2D>& texture_coords, const uint32_t vertex_index) const {
  Vertex3D v;
  
  v.position = vertices[vertex_index];
  v.color = (colors.size() > 1) ? colors[vertex_index] : RGBColor();
  v.texture_coords = (texture_coords.size() > 1) ? texture_coords[vertex_index] : Vector2D();

  return v;
}

const std::vector<Triangle3D> GeometryObject::triangles() const { 
  return m_triangles; 
}
const Material* GeometryObject::material() const { 
  return m_material; 
}