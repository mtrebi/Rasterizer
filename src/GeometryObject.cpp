#include "GeometryObject.h"

GeometryObject::GeometryObject() {

}

GeometryObject::GeometryObject(const std::vector<Point3D>& vertices, const std::vector<uint8_t>& indices)
  : m_vertices(vertices), m_indices(indices){
  
}

GeometryObject::~GeometryObject() {

}

const std::vector<Triangle3D> GeometryObject::tessellate() const {
  //TODO: actual tessellation

  return std::vector<Triangle3D>();
}