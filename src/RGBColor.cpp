#include "RGBColor.h"

RGBColor::RGBColor()
  : r(.0f), g(.0f), b(.0f) {

}

RGBColor::RGBColor(const float rgb)
  : r(rgb), g(rgb), b (rgb) {

}

RGBColor::RGBColor(const float red, const float green, const float blue)
  : r(red), g(green), b(blue) {

}

RGBColor::~RGBColor() {
  r = .0f;
  g = .0f;
  b = .0f;
}