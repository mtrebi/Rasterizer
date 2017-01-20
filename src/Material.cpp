#include "Material.h"

Material::Material(){

}

Material::Material(const RGBColor& d, const RGBColor& s, const float shininess)
  : k_d(d), k_s(s), k_shininess(shininess) {
}


Material::~Material() {
}
