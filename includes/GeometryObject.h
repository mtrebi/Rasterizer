#pragma once

class Material;

#include <vector>
#include "RGBColor.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Triangle.h"
#include "MATERIAL.H"

class GeometryObject {
private:
	std::vector<Triangle3D> m_triangles;
	Material *m_material;

public:
	GeometryObject();
	GeometryObject(Material* material, const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<Vector2D>& texture_coords, const std::vector<uint32_t>& indices);
	~GeometryObject();

	const std::vector<Triangle3D> triangles() const;
	const Material * material() const;
	
private:
	const std::vector<Triangle3D> triangulate(const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<Vector2D>& texture_coords, const std::vector<uint32_t>& indices) const;
	const Vertex3D build_vertex(const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<Vector2D>& texture_coords, const uint32_t vertex_index) const;
};

