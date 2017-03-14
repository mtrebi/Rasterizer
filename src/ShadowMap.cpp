#include "ShadowMap.h"
#include "ORTHOGRAPHICCAMERA.H"
#include "ForwardRasterizer.h"
ShadowMap::ShadowMap() {
}

//TODO: Directional or Perspective shadows
ShadowMap::ShadowMap(const World * world, const Light * light) {
  m_light = light;
  m_rasterizer = new ForwardRasterizer(world);
  m_camera = new OrthographicCamera(m_light->getPosition(), Point3D(0, 0, 0), SHADOW_MAP_HEIGHT, SHADOW_MAP_WIDTH, m_rasterizer, 2, 1000000.0 * 2);
}

void ShadowMap::render() {
  // Render without shadow maps and shading: only depth
  m_rasterizer->render(false, false);

  // Shadow map from light's POV
  m_shadow_map = m_rasterizer->get_depth_buffer();
  m_rasterizer->exportDepthBuffer(m_shadow_map, "shadow_map.bmp", SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);
}


const double ShadowMap::pointInShadow(const Point3D& point_world) const {
  double shadow = 0;
  // Find coordinates of point in light space
  Point2D point_light_space = m_rasterizer->rasterize(point_world);

#ifdef _PCF_SHADOWS
  for (int x = point_light_space.x - 1; x < point_light_space.x + 1; ++x) {
    for (int y = point_light_space.y - 1; y < point_light_space.y + 1; ++y) {
      const uint32_t index = round(y) * SHADOW_MAP_WIDTH + x + 1;
      // Get depths
      const double closest_depth = m_shadow_map[index];
      const double current_depth = (m_light->getPosition() - point_world).length();
      // Test light shadow map against real distance
      //shadow += (current_depth > closest_depth + SHADOW_MAP_BIAS) ? 0.20 : 0.0;
      shadow += (current_depth > closest_depth + SHADOW_MAP_BIAS) ? 0.045 : 0.0;

    }
  }
  //return shadow / 9.0;
#endif 
  shadow = 0;
  const uint32_t index = round(point_light_space.y) * SHADOW_MAP_WIDTH + point_light_space.x + 1;
  // Get depths
  const double closest_depth = m_shadow_map[index];
  const double current_depth = (m_light->getPosition() - point_world).length();
  // Test light shadow map against real distance
  shadow += (current_depth > closest_depth + SHADOW_MAP_BIAS) ? 0.05 : 0.0;
  return shadow;
  
}

ShadowMap::~ShadowMap() {
}
