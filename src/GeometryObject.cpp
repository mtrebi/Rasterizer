#include "GeometryObject.h"
#include <cassert>
GeometryObject::GeometryObject() {

}

GeometryObject::GeometryObject(const RGBColor& color, const Material& material, const std::vector<Point3D>& vertices, const std::vector<uint32_t>& indices)
  : m_vertices(vertices), m_indices(indices), m_material(material), m_color(color) {
}

GeometryObject::~GeometryObject() {

}

const std::vector<Triangle3D> GeometryObject::triangulate() const { 
  assert(m_indices.size() % 3 == 0 && "Indices array must be made up of triangles");
  std::vector<Triangle3D> triangles;
  for (int i = 0; i < m_indices.size(); i+=3) {
    const Triangle3D triangle = {
      m_vertices[m_indices[i]],
      m_vertices[m_indices[i+1]],
      m_vertices[m_indices[i+2]],
    };
    triangles.push_back(triangle);
  }
  
  return triangles;
}