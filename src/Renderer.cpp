#include "Renderer.h"
#include <fstream>

Renderer::Renderer()
    : m_world(nullptr),m_pixels(std::vector<RGBColor>()) {
    
}

Renderer::Renderer(World* world, const uint16_t image_width, const uint16_t image_height)
  : m_world(world), m_image_width(image_width), m_image_height(image_height), m_pixels(std::vector<RGBColor>(image_width * image_height, RGBColor(BACKGROUND_COLOR))) {

}



Renderer::~Renderer(){
    m_world = nullptr;
    m_pixels.clear();
}

void Renderer::exportImage(const std::string export_path) const {
    const int image_size = m_image_height * m_image_width * 4;
    const int headers_size = 14 + 40;
    const int filesize = image_size + headers_size;
    const int pixelsPerMeter = 2835;
    
    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
    //size of the file in bytes
    bmpfileheader[ 2] = (unsigned char)(filesize);
    bmpfileheader[ 3] = (unsigned char)(filesize>>8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);
            
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};
    //width of the image in bytes
    bmpinfoheader[ 4] = (unsigned char)(m_image_width);
    bmpinfoheader[ 5] = (unsigned char)(m_image_width>>8);
    bmpinfoheader[ 6] = (unsigned char)(m_image_width>>16);
    bmpinfoheader[ 7] = (unsigned char)(m_image_width>>24);
    
    //height of the image in bytes
    bmpinfoheader[ 8] = (unsigned char)(m_image_height);
    bmpinfoheader[ 9] = (unsigned char)(m_image_height>>8);
    bmpinfoheader[10] = (unsigned char)(m_image_height>>16);
    bmpinfoheader[11] = (unsigned char)(m_image_height>>24);

    // Size image in bytes
    bmpinfoheader[21] = (unsigned char)(image_size);
    bmpinfoheader[22] = (unsigned char)(image_size>>8);
    bmpinfoheader[23] = (unsigned char)(image_size>>16);
    bmpinfoheader[24] = (unsigned char)(image_size>>24);

    bmpinfoheader[25] = (unsigned char)(pixelsPerMeter);
    bmpinfoheader[26] = (unsigned char)(pixelsPerMeter>>8);
    bmpinfoheader[27] = (unsigned char)(pixelsPerMeter>>16);
    bmpinfoheader[28] = (unsigned char)(pixelsPerMeter>>24);

    bmpinfoheader[29] = (unsigned char)(pixelsPerMeter);
    bmpinfoheader[30] = (unsigned char)(pixelsPerMeter>>8);
    bmpinfoheader[31] = (unsigned char)(pixelsPerMeter>>16);
    bmpinfoheader[32] = (unsigned char)(pixelsPerMeter>>24);

    FILE *file = fopen(export_path.c_str(), "wb");//write-binary
    
    fwrite(bmpfileheader,1,14, file);
    fwrite(bmpinfoheader,1,40, file);
    
    for (int i = 0; i < m_pixels.size(); ++i){
        const RGBColor pixel = m_pixels[i];
        unsigned char color[3] = {
            (int) (pixel.b * 255), 
            (int) (pixel.g * 255), 
            (int) (pixel.r * 255)
        };
        fwrite(color, 1, 3, file);
    }
    fclose(file);
}
