#ifndef UTILS_H
#define UTILS_H

class Utils {
public:
  static void convert1DIndexto2DIndex(uint16_t& pixel_x, uint16_t& pixel_y, const uint32_t i, const uint16_t m_image_width, const uint16_t m_image_height) {
    pixel_x =  i % m_image_width;
    pixel_y =  i / m_image_width;
  }

};
#endif // !UTILS_H




