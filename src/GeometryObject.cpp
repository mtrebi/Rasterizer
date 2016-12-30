#include "GeometryObject.h"

GeometryObject::GeometryObject() {

}

GeometryObject::GeometryObject(const std::vector<Point3D>& vertices, const std::vector<uint8_t>& indices)
  : m_vertices(vertices), m_indices(indices){
  
}

GeometryObject::~GeometryObject() {

}