#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point2D.h"
#include "Point3D.h"
#include "RGBCOLOR.H"
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
    return (u >= 0 && v >= 0 && u + v <= 1.0);
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

  const BoundingBox2D bbox() const {
    BoundingBox2D bbox;

    bbox.min.x = std::numeric_limits<double>::max();
    bbox.min.y = std::numeric_limits<double>::max();

    bbox.max.x = std::numeric_limits<double>::min();
    bbox.max.y = std::numeric_limits<double>::min();

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

struct Fragment {
  Point3D position;
  RGBColor color, diffuse, specular;
  Vector3D normal;

  Fragment() { }
  Fragment(const Point3D& p, const RGBColor& c, const RGBColor& d, const RGBColor& s, const Vector3D& n)
    : position(p), color(c), diffuse(d), specular(s), normal(n) { }

};

struct Vertex3D {
  Point3D position;
  RGBColor color;
  Vector2D texture_coords;
  Vector3D normal;

  Vertex3D() { }
  Vertex3D(const Point3D& p, const RGBColor& c, const Vector2D& text, const Vector3D& n)
    : position(p), color(c), texture_coords(text), normal(n) { }
};

class Triangle3D {
public:
  Vertex3D v1, v2, v3;
  Vector3D normal;

public:
  Triangle3D() { 
  }

  Triangle3D(const Vertex3D& p1, const Vertex3D& p2, const Vertex3D& p3) : v1(p1), v2(p2), v3(p3) {
    Vector3D v1v2 = (v2.position - v1.position);
    Vector3D v2v3 = (v3.position - v2.position);

    v1v2.normalize();
    v2v3.normalize();

    normal = v1v2 ^ v2v3;
  }

  ~Triangle3D() { }

  const bool contains(const Point3D& point) const {
    double u, v, w;
    calculateBarycentricCoords(u, v, w, point);
    return (u >= 0 && v >= 0 && u + v <= 1.0);
  }

  void calculateBarycentricCoords(double& u, double& v, double& w, const Point3D& point) const {
    const Vector3D v0 = this->v2.position - this->v1.position, v1 = this->v3.position - this->v1.position, v2 = point - this->v1.position;
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
};

#endif // !TRIANGLE_H
