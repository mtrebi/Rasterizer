#ifndef RGBCOLOR_H
#define RGBCOLOR_H

#include <algorithm> //min

class RGBColor  {
public:
  float r, g, b;

public:
  RGBColor();
  RGBColor(const float rgb);
  RGBColor(const float red, const float green, const float blue);

  RGBColor operator+(const RGBColor& color) const {
    RGBColor new_color;
    new_color.r = std::min(this->r + color.r, 1.0f);
    new_color.g = std::min(this->g + color.g, 1.0f);
    new_color.b = std::min(this->b + color.b, 1.0f);

    return new_color;
  }

  RGBColor operator*(const RGBColor& color) const {
    RGBColor new_color;
    new_color.r = this->r * color.r;
    new_color.g = this->g * color.g;
    new_color.b = this->b * color.b;

    return new_color;
  }

  RGBColor operator*(const double factor) const {
    RGBColor new_color;
    new_color.r = std::min(this->r * factor, 1.0);
    new_color.g = std::min(this->g * factor, 1.0);
    new_color.b = std::min(this->b * factor, 1.0);
    return new_color;
  }

  RGBColor& operator=(const RGBColor& color) {
    if (this == &color) {
      return *this;
    }

    r = color.r;
    g = color.g;
    b = color.b;

    return *this;
  }

  RGBColor& operator+=(const RGBColor& color) {
    if (this == &color) {
      return *this;
    }

    r += color.r;
    g += color.g;
    b += color.b;
  }

  ~RGBColor();
};

#endif /* RGBCOLOR_H */

