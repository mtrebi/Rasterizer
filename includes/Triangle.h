#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point2D.h"
#include "Point3D.h"

struct Triangle2D {
  Point2D v1, v2, v3;

  const bool contains(const Point2D point) const {
    const float area = 0.5 *(-v2.y*v3.x + v1.y*(-v2.x + v3.x) + v1.x*(v2.y - v3.y) + v2.x*v3.y);

    const float s = 1 / (2 * area)*(v1.y*v3.x - v1.x*v3.y + (v3.y - v1.y)*point.x + (v1.x - v3.x)*point.y);
    const float t = 1 / (2 * area)*(v1.x*v2.y - v1.y*v2.x + (v1.y - v2.y)*point.x + (v2.x - v1.x)*point.y);

    return (s > 0 && t > 0 && 1 - s - t > 0);
  }

};

struct Triangle3D {
  Point3D v1, v2, v3;
};

#endif // !TRIANGLE_H
