#include "DirectionalLight.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"
#include "RASTERIZER.H"
#include "ForwardRasterizer.H"

DirectionalLight::DirectionalLight()
  : Light() {

}

DirectionalLight::DirectionalLight(const RGBColor & color, const Vector3D & direction)
  : Light(color) {

  Vector3D direction_norm = direction;
  direction_norm.normalize();
  m_direction = direction_norm;
}

DirectionalLight::~DirectionalLight(){

}

const Point3D DirectionalLight::getPosition() const {
  Point3D light_pos(
    m_direction.x * DIRECTIONAL_LIGHT_DISTANCE,
    m_direction.y * DIRECTIONAL_LIGHT_DISTANCE,
    m_direction.z * DIRECTIONAL_LIGHT_DISTANCE
  );

  return light_pos;
}

const Vector3D DirectionalLight::getDirectionToPoint(const Point3D & point) const {
  return m_direction;
}

// Render depths from Light POV
const std::vector<double> DirectionalLight::getShadowMap(const World* world) const  {
  Rasterizer * rasterizer_light = new ForwardRasterizer(world);
  Camera * camera_light = new OrthographicCamera(this->getPosition() , Point3D(0, 0, 0), SHADOW_MAP_HEIGHT, SHADOW_MAP_WIDTH, rasterizer_light, 2, DIRECTIONAL_LIGHT_DISTANCE * 2);

  // Render without shadow maps and shading: only depth
  rasterizer_light->render(false, false); 

  // Shadow map from light's POV
  std::vector<double> shadow_map_light = rasterizer_light->get_depth_buffer();
  rasterizer_light->exportDepthBuffer(shadow_map_light, "shadow_map.bmp", SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);
  
  return shadow_map_light;
}
