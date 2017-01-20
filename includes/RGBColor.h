#ifndef RGBCOLOR_H
#define RGBCOLOR_H

class RGBColor  {
public:
  float r, g, b;

public:
  RGBColor();
  RGBColor(const float red, const float green, const float blue);

  //TODO: COlor operations (add, substract...)

  RGBColor operator+(const RGBColor& color) const {
    RGBColor new_color;
    new_color.r = this->r + color.r;
    new_color.g = this->g + color.g;
    new_color.b = this->b + color.b;
  }


  ~RGBColor();
};

#endif /* RGBCOLOR_H */

