#include "RGBColor.h"

RGBColor::RGBColor()
  : r(0), g(0), b(0) {

}

RGBColor::RGBColor(const uint8_t red, const uint8_t green, const uint8_t blue)
  : r(red), g(green), b(blue) {

}

RGBColor::~RGBColor() {
  r = 0;
  g = 0;
  b = 0;
}