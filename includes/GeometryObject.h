#ifndef GEOMETRYOBJECT_H
#define GEOMETRYOBJECT_H

#include "Point3D.h"
#include "Point2D.h"
#include <vector>
#include <cstdint>

class GeometryObject {
private:
	std::vector<Point3D> m_vertices;
	std::vector<uint8_t> m_indices;
	// TODO: Normals
	// TODO: Textures

public:
    GeometryObject();
    GeometryObject(const std::vector<Point3D>& vertices, const std::vector<uint8_t>& indices = std::vector<uint8_t>());
    
    // TODO: Some kind of projection
	//const std::vector<Point2D> Project();
    
    ~GeometryObject();
};


#endif /* GEOMETRYOBJECT_H */

