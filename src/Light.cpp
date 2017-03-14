#include "Light.h"

Light::Light() {

}

Light::Light(const RGBColor& color)
  : m_color(color) {
}

Light::~Light() {

}

const RGBColor & Light::getColor() {
  return m_color;
}
