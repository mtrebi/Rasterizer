#ifndef RGBCOLOR_H
#define RGBCOLOR_H

#include <cstdint>

class RGBColor  {
  uint8_t r, g, b;

public:
  RGBColor();
  RGBColor(const uint8_t red, const uint8_t green, const uint8_t blue);

  //TODO: COlor operations (add, substract...)
  ~RGBColor();
};

#endif /* RGBCOLOR_H */

