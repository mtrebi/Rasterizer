#ifndef GEOMETRYOBJECT_H
#define GEOMETRYOBJECT_H

#include "Point3D.h"
#include "Point2D.h"
#include "Triangle.h"
#include "RGBColor.h"
#include "Material.h"
#include <vector>
#include <cstdint>

class GeometryObject {
public:
	std::vector<Point3D> m_vertices;
	std::vector<uint32_t> m_indices;
  Material m_material;
  RGBColor m_color;
	// TODO: Normals
	// TODO: Textures

public:
  GeometryObject();
  GeometryObject(const RGBColor& color, const Material& material, const std::vector<Point3D>& vertices, const std::vector<uint32_t>& indices = std::vector<uint32_t>());
  ~GeometryObject();

  const std::vector<Triangle3D> triangulate() const;

};


#endif /* GEOMETRYOBJECT_H */

