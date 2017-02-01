#include "GeometryObject.h"
#include <cassert>
GeometryObject::GeometryObject() {

}

GeometryObject::GeometryObject(const Material & material, const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<Vector2D>& texture_coords, const std::vector<uint32_t>& indices)
  : m_material(material), m_vertices(vertices), m_indices(indices), m_colors(colors), m_texture(texture_coords){
}

GeometryObject::~GeometryObject() {

}

const std::vector<Triangle3D> GeometryObject::triangulate() const { 
  assert(m_indices.size() % 3 == 0 && "Indices array must be made up of triangles");
  std::vector<Triangle3D> triangles;
  for (int i = 0; i < m_indices.size(); i+=3) {
    const Vertex3D v1 = {
      m_vertices[m_indices[i]],
      m_colors[m_indices[i]],
      m_texture[m_indices[i]]
    };
    const Vertex3D v2 = {
      m_vertices[m_indices[i+1]],
      m_colors[m_indices[i+1]],
      m_texture[m_indices[i+1]]
    };
    const Vertex3D v3 = {
      m_vertices[m_indices[i+2]],
      m_colors[m_indices[i+2]],
      m_texture[m_indices[i+2]]
    };
    const Triangle3D triangle ( v1, v2, v3 );
    triangles.push_back(triangle);
  }
  
  return triangles;
}