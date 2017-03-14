#pragma once

class Rasterizer;

#include <vector>
#include "Camera.h"
#include "Light.h"

class ShadowMap {
protected:
  // Render data
  Rasterizer* m_rasterizer;
  Camera * m_camera;
  // Data
  const Light * m_light;
  std::vector<double> m_shadow_map;
  // Constants
  const int SHADOW_MAP_WIDTH = 800;
  const int SHADOW_MAP_HEIGHT = 600;
  const double SHADOW_MAP_BIAS = 7.5;
public:
  ShadowMap();
  ShadowMap(const World * world, const Light* light);

  void render();
  const double pointInShadow(const Point3D& point_world) const;

  ~ShadowMap();
};

