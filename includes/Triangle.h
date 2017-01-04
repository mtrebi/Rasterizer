#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point2D.h"
#include "Point3D.h"

struct Triangle2D {
  Point2D v1, v2, v3;
};

struct Triangle3D {
  Point3D v1, v2, v3;
};

#endif // !TRIANGLE_H
