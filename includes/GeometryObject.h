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
	Material *m_material;
  std::vector<Point3D> m_vertices;
  std::vector<RGBColor> m_colors;
  std::vector<Vector2D> m_texture_coords;
  std::vector<uint32_t> m_indices;
public:
	GeometryObject();
	GeometryObject(Material* material, const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<Vector2D>& texture_coords, const std::vector<uint32_t>& indices);
	~GeometryObject();

  void rotate(const float roll, const float pitch, const float yaw);
	const std::vector<Triangle3D> triangles() const;
	const Material * material() const;
	
private:
	const Vertex3D build_vertex(const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<Vector2D>& texture_coords, const uint32_t vertex_index) const;
};

