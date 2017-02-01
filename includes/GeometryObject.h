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
  std::vector<RGBColor> m_colors;

  Material m_material;
	// TODO: Normals
	// TODO: Textures

public:
  GeometryObject();
  GeometryObject(const Material& material, const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<uint32_t>& indices);
  ~GeometryObject();

  const std::vector<Triangle3D> triangulate() const;

};


#endif /* GEOMETRYOBJECT_H */

