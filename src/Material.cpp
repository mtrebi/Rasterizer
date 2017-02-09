#include "Material.h"
#include "../lib/EasyBMP_1.06/EasyBMP.h"

/******************************** Material ********************************/

Material::Material(){
}

Material::Material(const float shininess)
  : k_shininess(shininess) {
}

Material::~Material() {
}

const RGBColor Material::shade(const std::vector<Light*>& lights, const Camera& camera, const Fragment& fragment) {
#ifdef _FLAT
  return fragment.color;
#endif // _FLAT

#ifdef _PHONG
  return phongEquation(lights, fragment.normal, -camera.viewDirection(fragment.position), fragment.position, fragment.color, fragment.diffuse, fragment.specular, 5.0);
#endif // _PHONG

#ifdef _BLINN_PHONG
  return blinnPhongEquation(lights, fragment.normal, -camera.viewDirection(fragment.position), fragment.position, fragment.color, fragment.diffuse, fragment.specular, 5.0);
#endif // _BLINN-PHONG
}

const RGBColor Material::blinnPhongEquation(const std::vector<Light*>& lights, const Vector3D& N, const Vector3D& V, const Point3D vertex_position,
                                    const RGBColor& vertex_color, const RGBColor& diffuse_color, const RGBColor& specular_color, const float shininess) {
  const RGBColor ambient(0.1);
  RGBColor diffuse, specular;
  for (auto& light : lights) {
    const Vector3D L = -(light->getDirectionToPoint(vertex_position));
    Vector3D H = V + L;
    H.normalize();

    diffuse = light->getColor() * diffuse_color * std::max((L * N), 0.0);
    specular = light->getColor() *  specular_color * pow(std::max((H * V), 0.0), shininess);
  }

  const RGBColor result = (ambient + diffuse + specular) * vertex_color;
  return result;
}

const RGBColor Material::phongEquation(const std::vector<Light*>& lights, const Vector3D& N, const Vector3D& V, const Point3D vertex_position,
  const RGBColor& vertex_color, const RGBColor& diffuse_color, const RGBColor& specular_color, const float shininess) {
  const RGBColor ambient(0.1);
  RGBColor diffuse, specular;
  for (auto& light : lights) {
    const Vector3D L = -(light->getDirectionToPoint(vertex_position));
    const Vector3D R = 2 * (N * L) * N - L;

    diffuse = light->getColor() * diffuse_color * std::max((L * N), 0.0);
    specular = light->getColor() *  specular_color * pow(std::max((R * V), 0.0), shininess);
  }

  const RGBColor phong_result = (ambient + diffuse + specular) * vertex_color;
  return phong_result;
}


/******************************** FlatMaterial ********************************/

FlatMaterial::FlatMaterial() {
}

FlatMaterial::FlatMaterial(const RGBColor& d, const RGBColor& s, float shininess)
  : k_d(d), k_s(s), Material(shininess) {
}

FlatMaterial::~FlatMaterial() {
}

const RGBColor FlatMaterial::getDiffuseColor(const Vector2D& text_coords) const {
  return k_d;
}

const RGBColor FlatMaterial::getSpecularColor(const Vector2D& text_coords) const {
  return k_s;
}

const Vector3D FlatMaterial::getNormal(const Triangle3D& triangle_world, const Vector2D& text_coords) const {
  return triangle_world.normal;
}
/******************************** TexturedMaterial ********************************/

TexturedMaterial::TexturedMaterial() {
}

TexturedMaterial::TexturedMaterial(const std::string texture_diffuse_file, const std::string texture_specular_file, const std::string texture_normal_file, const float shininess) 
  : Material(shininess) {

  m_texture_diffuse = loadTexture(m_texture_diffuse_width, m_texture_diffuse_height, texture_diffuse_file);
  m_texture_specular = loadTexture(m_texture_specular_width, m_texture_specular_height, texture_specular_file);
  m_texture_normal = loadTexture(m_texture_normal_width, m_texture_normal_height, texture_normal_file);

}

TexturedMaterial::~TexturedMaterial() {
}

const RGBColor TexturedMaterial::getDiffuseColor(const Vector2D& text_coords) const {
  return getTextureColor(m_texture_diffuse, m_texture_diffuse_width, m_texture_diffuse_height, text_coords);
}

const RGBColor TexturedMaterial::getSpecularColor(const Vector2D& text_coords) const {
  return getTextureColor(m_texture_specular, m_texture_specular_width, m_texture_specular_height, text_coords);
}

const Vector3D TexturedMaterial::getNormal(const Triangle3D& triangle_world, const Vector2D& text_coords) const { 
  Vector3D tangent, bitangent;
  calculateTangentSpace(tangent, bitangent, triangle_world);

  const Vector3D normal_tangent = (Vector3D) getTextureColor(m_texture_normal, m_texture_normal_width, m_texture_normal_height, text_coords);
  const Vector3D normal_world = TangentToWorld(normal_tangent, tangent, bitangent, normal_tangent);
  
  return normal_world;
}


const Vector3D TexturedMaterial::TangentToWorld(const Vector3D& v, const Vector3D& tangent, const Vector3D& bitangent, const Vector3D& normal) const {
  const int handness = -1; // Left coordinate system
  // V * TBN
  Vector3D v_world = {
    v.x * tangent.x + v.y * bitangent.x + v.z * normal.x,
    v.x * tangent.y + v.y * bitangent.y + v.z * normal.y,
    v.x * tangent.z + v.y * bitangent.z + v.z * normal.z,
  };
  // V * TBN(-1) = V * TBN(T)
  Vector3D v_world2 = {
    v.x * tangent.x   + v.y * tangent.y   + v.z * tangent.z,
    v.x * bitangent.x + v.y * bitangent.y + v.z * bitangent.z,
    v.x * normal.x    + v.y * normal.y    + v.z * normal.z,
  };

  v_world2.normalize();

  return handness * v_world2;
}

void TexturedMaterial::calculateTangentSpace(Vector3D& tangent, Vector3D& bitangent, const Triangle3D& triangle_world) const {
  const Vector3D q1 = triangle_world.v2.position - triangle_world.v1.position;
  const Vector3D q2 = triangle_world.v3.position - triangle_world.v2.position;

  const double s1 = triangle_world.v2.texture_coords.x - triangle_world.v1.texture_coords.x;
  const double s2 = triangle_world.v3.texture_coords.x - triangle_world.v2.texture_coords.x;

  const double t1 = triangle_world.v2.texture_coords.y - triangle_world.v1.texture_coords.y;
  const double t2 = triangle_world.v3.texture_coords.y - triangle_world.v2.texture_coords.y;


  tangent = t2 * q1 - t1 * q2;
  bitangent = -s2 * q1 + s1 * q2;

  tangent.normalize();
  bitangent.normalize();
}

const RGBColor TexturedMaterial::getTextureColor(const std::vector<RGBColor>& texture, int texture_width, int texture_height, const Vector2D& text_coords) const {
  // Convert from (0,0) at left-bottom to (0,0) at left-top 
  const Vector2D text_coords_image(
    1 - std::min(fmod(text_coords.y, 1), 1.0),
    std::min(fmod(text_coords.x, 1), 1.0)
  );
  // Scale to texture size
  const int x = text_coords_image.x * (texture_width - 1);
  const int y = text_coords_image.y * (texture_height - 1);
  const int index = y * texture_width + x;
  return texture[index];
}

std::vector<RGBColor> TexturedMaterial::loadTexture(int& texture_width, int& texture_height, const std::string import_path) const {
  std::vector<RGBColor> texture;
  if (import_path != "") {
    BMP image;
    image.ReadFromFile(import_path.c_str());

    texture_width = image.TellWidth();
    texture_height = image.TellHeight();

    if (texture_width > 1 && texture_height > 1) {
      texture.reserve(texture_width * texture_height);
      for (int x = 0; x < texture_width; ++x) {
        for (int y = 0; y < texture_height; ++y) {
          RGBApixel pixel = image.GetPixel(x, y);
          RGBColor color(pixel.Red / 255.0, pixel.Green / 255.0, pixel.Blue / 255.0);
          texture.push_back(color);
        }
      }
    }
  }
  return texture;
}