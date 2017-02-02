#include "GeometryObject.h"
#include <cassert>
#include "../lib/EasyBMP_1.06/EasyBMP.h"

GeometryObject::GeometryObject() {

}

GeometryObject::GeometryObject(const Material & material, const std::vector<Point3D>& vertices, const std::vector<RGBColor>& colors, const std::vector<Vector2D>& texture_coords, const std::string texture_file, const std::vector<uint32_t>& indices)
  : m_material(material), m_vertices(vertices), m_indices(indices), m_colors(colors), m_texture_coords(texture_coords){
  loadTexture(texture_file);
}

GeometryObject::~GeometryObject() {

}

const std::vector<Triangle3D> GeometryObject::triangulate() const { 
  assert(m_indices.size() % 3 == 0 && "Indices array must be made up of triangles");
  std::vector<Triangle3D> triangles;
  for (int i = 0; i < m_indices.size(); i+=3) {
    const Vertex3D v1 = {
      m_vertices[m_indices[i]],
      m_colors[m_indices[i]],
      m_texture_coords[m_indices[i]]
    };
    const Vertex3D v2 = {
      m_vertices[m_indices[i+1]],
      m_colors[m_indices[i+1]],
      m_texture_coords[m_indices[i+1]]
    };
    const Vertex3D v3 = {
      m_vertices[m_indices[i+2]],
      m_colors[m_indices[i+2]],
      m_texture_coords[m_indices[i+2]]
    };
    const Triangle3D triangle ( v1, v2, v3 );
    triangles.push_back(triangle);
  }
  
  return triangles;
}

typedef struct bitmap
{
  unsigned int width, height;
  unsigned char *pixels;
};

void GeometryObject::loadTexture(const std::string import_path) {
  BMP image;
  image.ReadFromFile(import_path.c_str());

  m_texture_width = image.TellWidth();
  m_texture_height = image.TellHeight();

  m_texture.reserve(m_texture_width * m_texture_height);
  for (int x = 0; x < m_texture_width; ++x) {
    for (int y = 0; y < m_texture_height; ++y) {
      RGBApixel pixel = image.GetPixel(x, y);
      RGBColor color(pixel.Red / 255.0, pixel.Green / 255.0, pixel.Blue / 255.0);
      
      
      
      m_texture.push_back(color);
    }
  }
}

const RGBColor GeometryObject::getTextureColor(const Vector2D& text_coords) const {
  // Convert from (0,0) at left-bottom to (0,0) at left-top 
  const Vector2D text_coords_image (
    1 - std::min(text_coords.y, 1.0),
    std::min(text_coords.x, 1.0)
  );
  // Scale to texture size
  const int x = text_coords_image.x * (m_texture_width - 1);
  const int y = text_coords_image.y * (m_texture_height - 1);
  const int index = y * m_texture_width + x;
  return m_texture[index];
}
