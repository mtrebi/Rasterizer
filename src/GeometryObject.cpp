#include "GeometryObject.h"

GeometryObject::GeometryObject() {
  m_color = RGBColor(1.0f, 0.1f, 0.1f);
  m_material = Material(RGBColor(0.4f), RGBColor(0.4f), 0.5f);
}

GeometryObject::GeometryObject(const RGBColor& color, const Material& material, const std::vector<Point3D>& vertices, const std::vector<uint8_t>& indices)
  : m_vertices(vertices), m_indices(indices), m_material(material), m_color(color) {
  m_color = RGBColor(1.0f, 0.0f, 0.0f);

}

GeometryObject::~GeometryObject() {

}

const std::vector<Triangle3D> GeometryObject::tessellate() const {
  //TODO: actual tessellation using vertices and indices

  return std::vector<Triangle3D> {
    Triangle3D(
      Point3D(-225.0f, 0.0f, 20.0f),
      Point3D(0.0f, 225.0f, 20.0f),
      Point3D(225.0f, 0.0f, 20.0f)
    )

  };
}