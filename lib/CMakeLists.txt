include_directories(
    EasyBMP_1.06/
)

# Source Files
SET(EASYBMP_SRCS
    EasyBMP_1.06/EasyBMP.cpp

)

add_library( EASYBMP STATIC
    ${EASYBMP_SRCS}
)
