#include "GeometryObject.h"

GeometryObject::GeometryObject() {
  m_color = RGBColor(1, 0, 0);

}

GeometryObject::GeometryObject(const std::vector<Point3D>& vertices, const std::vector<uint8_t>& indices)
  : m_vertices(vertices), m_indices(indices){
  m_color = RGBColor(1, 0, 0);
}

GeometryObject::~GeometryObject() {

}

const std::vector<Triangle3D> GeometryObject::tessellate() const {
  //TODO: actual tessellation using vertices and indices

  return std::vector<Triangle3D> {
    Triangle3D(
      Point3D(-25.0f, 0.0f, 20.0f),
      Point3D(0.0f, 25.0f, 20.0f),
      Point3D(25.0f, 0.0f, 20.0f)
    )
  };
}