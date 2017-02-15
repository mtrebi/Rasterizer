cmake_minimum_required (VERSION 3.5)
project(EASY_BMP)


include_directories(
    EasyBMP_1.06/
    glm-0.9.8.2/
)

# Source Files
SET(EASYBMP_SRCS 
    EasyBMP_1.06/EasyBMP.cpp

)

add_library( EASY_BMP STATIC ${EASYBMP_SRCS})