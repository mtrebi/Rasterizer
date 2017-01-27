#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point2D.h"
#include "Point3D.h"
#include <array>

struct BoundingBox2D {
  Point2D max, min;
};

class Triangle2D {
public:
  Point2D v1, v2, v3;
public:
  Triangle2D() { }
  Triangle2D(const Point2D& p1, const Point2D& p2, const Point2D& p3) : v1(p1), v2(p2), v3(p3) { }
  ~Triangle2D() { }

  const bool contains(const Point2D& point) const {
    double u, v, w;
    calculateBarycentricCoords(u, v, w, point);
    return (u >= 0 && v >= 0 && u + v < 1);
  }

  void calculateBarycentricCoords(double& u, double& v, double& w, const Point2D& point) const {
    const Vector2D v0 = this->v2 - this->v1, v1 = this->v3 - this->v1, v2 = point - this->v1;
    double d00 = v0 * v0;
    double d01 = v0 * v1;
    double d11 = v1 * v1;
    double d20 = v2 * v0;
    double d21 = v2 * v1;
    double denom = d00 * d11 - d01 * d01;
    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1.0f - v - w;
  }

  const BoundingBox2D calculateBBox() const {
    BoundingBox2D bbox;

    bbox.min.x = std::numeric_limits<float>::max();
    bbox.min.y = std::numeric_limits<float>::max();

    bbox.max.x = std::numeric_limits<float>::min();
    bbox.max.y = std::numeric_limits<float>::min();

    std::array<Point2D, 3> vertices{ this->v1, this->v2, this->v3 };

    for (auto& vertex : vertices) {
      if (vertex.x < bbox.min.x) {
        bbox.min.x = vertex.x;
      }
      if (vertex.y < bbox.min.y) {
        bbox.min.y = vertex.y;
      }

      if (vertex.x > bbox.max.x) {
        bbox.max.x = vertex.x;
      }
      if (vertex.y > bbox.max.y) {
        bbox.max.y = vertex.y;
      }
    }
    return bbox;
  }
};

class Triangle3D {
public:
  Point3D v1, v2, v3;
  Vector3D normal;

public:
  Triangle3D() { 
  }

  Triangle3D(const Point3D& p1, const Point3D& p2, const Point3D& p3) : v1(p1), v2(p2), v3(p3) { 
    Vector3D v1v2 = (v2 - v1);
    Vector3D v2v3 = (v3 - v2);

    v1v2.normalize();
    v2v3.normalize();

    normal = v1v2 ^ v2v3;
  }

  ~Triangle3D() { }

  const bool contains(const Point3D& point) const {
    double u, v, w;
    calculateBarycentricCoords(u, v, w, point);
    return (u >= 0 && v >= 0 && u + v < 1);
  }

  void calculateBarycentricCoords(double& u, double& v, double& w, const Point3D& point) const {
    const Vector3D v0 = this->v2 - this->v1, v1 = this->v3 - this->v1, v2 = point - this->v1;
    float d00 = v0 * v0;
    float d01 = v0 * v1;
    float d11 = v1 * v1;
    float d20 = v2 * v0;
    float d21 = v2 * v1;
    float denom = d00 * d11 - d01 * d01;
    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1.0f - v - w;
  }

  const Point3D interpolatePoint(const Triangle2D& triangle_raster, const Point2D& pixel_raster) const {
    // Interpolate point in 3D triangle using barycentric coordinates of 2D triangle
    double u, v, w;
    triangle_raster.calculateBarycentricCoords(u, v, w, pixel_raster);
    const Point3D point_interpolated = v1 * u + v2 * v + v3 * w;
    return point_interpolated;
  }
};

#endif // !TRIANGLE_H
