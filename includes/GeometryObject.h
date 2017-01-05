#ifndef GEOMETRYOBJECT_H
#define GEOMETRYOBJECT_H

#include "Point3D.h"
#include "Point2D.h"
#include "Triangle.h"
#include <vector>
#include <cstdint>

class GeometryObject {
public:
	std::vector<Point3D> m_vertices;
	std::vector<uint8_t> m_indices;
  RGBColor m_color;
	// TODO: Normals
	// TODO: Textures

public:
  GeometryObject();
  GeometryObject(const std::vector<Point3D>& vertices, const std::vector<uint8_t>& indices = std::vector<uint8_t>());
    
  // TODO: Some kind of projection
  // TODO: local coordinate space ? (Model matrix?)
//const std::vector<Point2D> Project();
    
  ~GeometryObject();

  const std::vector<Triangle3D> tessellate() const;

};


#endif /* GEOMETRYOBJECT_H */

