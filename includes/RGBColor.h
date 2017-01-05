#ifndef RGBCOLOR_H
#define RGBCOLOR_H

class RGBColor  {
public:
  float r, g, b;

public:
  RGBColor();
  RGBColor(const float red, const float green, const float blue);

  //TODO: COlor operations (add, substract...)
  ~RGBColor();
};

#endif /* RGBCOLOR_H */

