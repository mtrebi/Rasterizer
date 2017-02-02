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
	std::vector<Vector2D> m_texture_coords;
	std::vector<RGBColor> m_texture;
	int m_texture_width,
		m_texture_height;

	Material m_material;
	// TODO: Normals
	// TODO: Textures

public:
	GeometryObject();
	GeometryObject(const Material& material, const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<Vector2D>& texture_coords, const std::string texture_file, const std::vector<uint32_t>& indices);
	~GeometryObject();


  inline const bool hasTexture() const { return m_texture.size() > 0; }
  inline const bool hasColor() const { return m_colors.size() > 0; }

	const std::vector<Triangle3D> triangulate() const;
	const RGBColor getTextureColor(const Vector2D& text_coords) const;
private:
	void loadTexture(const std::string import_path);
};


#endif /* GEOMETRYOBJECT_H */

