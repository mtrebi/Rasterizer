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

class Triangle3D {
public:
  Point3D v1, v2, v3;
public:
  Triangle3D() { }
  Triangle3D(const Point3D& p1, const Point3D& p2, const Point3D& p3) : v1(p1), v2(p2), v3(p3) { }
  ~Triangle3D() { }

  const bool contains(const Point3D& point) const {
    float u, v, w;
    calculateBarycentricCoords(u, v, w, point);
    return (u > 0 && v > 0 && u + v <= 0);
  }

  const Point3D intersect(bool& hit, const Point3D& ray_origin, const Vector3D& ray_direction) const {
    Vector3D normal_triangle = ((this->v2 - this->v1) ^ (this->v3 - this->v1));
    normal_triangle.normalize();

    Vector3D ray_direction_norm = ray_direction;
    ray_direction_norm.normalize();

    const double t = (this->v1 - ray_origin) * normal_triangle / (ray_direction_norm * normal_triangle);
    const Point3D intersecion_ray_plane = ray_origin + t * ray_direction_norm;
    if (this->contains(intersecion_ray_plane)) {
      hit = true;
      return intersecion_ray_plane;
    }

    hit = false;
    return Point3D();
  }

private:
  void calculateBarycentricCoords(float& u, float& v, float& w, const Point3D& point) const {
    const float area_triangle = ((this->v2 - this->v1) ^ (this->v3 - this->v1)).length() / 2;

    const float area_u = ((point - this->v1) ^ (this->v2 - this->v1)).length() / 2;
    const float area_v = ((point - this->v1) ^ (this->v3 - this->v1)).length() / 2;
    const float area_w = ((point - this->v3) ^ (this->v3 - this->v2)).length() / 2;

    u = area_u / area_triangle;
    v = area_v / area_triangle;
    w = area_w / area_triangle;
  }
};

#endif // !TRIANGLE_H
