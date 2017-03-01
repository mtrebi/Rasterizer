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
  m_direction = direction;
}

DirectionalLight::~DirectionalLight(){

}

const Vector3D DirectionalLight::getDirectionToPoint(const Point3D & point) const {
  return m_direction;
}

const std::vector<double> DirectionalLight::getShadowMap(const World* world, const int image_height, const int image_width, Rasterizer * rasterizer_camera) const  {
  Camera * camera;
  Rasterizer * rasterizer;
  Point3D light_pos(
    -m_direction.x * 1000,
    -m_direction.y * 1000,
    -m_direction.z * 1000
  );
  //Point3D light_pos = (Point3D) (-m_direction * 1000);
  Point3D light_target = Point3D(0, 0, 0);

  rasterizer = new ForwardRasterizer(world);
  camera = new OrthographicCamera(light_pos, light_target, image_height, image_width, rasterizer);

  // Render withouth shadow maps and shading: only depth
  rasterizer->render(false, false);
  rasterizer->export_output("shadows_light.bmp");

  // Shadow map from light perspective
  const std::vector<double> shadow_map_light = rasterizer->get_depth_buffer();
  std::vector<double> shadow_map_camera = std::vector<double>(image_height * image_width, 2000);

  // Build shadow map from camera (apply transform)
  
  for (int i = 0; i < shadow_map_light.size(); ++i) {
    const int y = i / image_width;
    const int x = i - (y *  image_width);

    const double depth_light = shadow_map_light[i];
    if (depth_light < 2000) {

      const Point2D pixel_raster_light(x, y);
      const Point3D pixel_world = rasterizer->unrasterize(pixel_raster_light, depth_light);
      const Point2D pixel_raster_camera = rasterizer_camera->rasterize(pixel_world);
      const uint32_t index = pixel_raster_camera.y * image_width + pixel_raster_camera.x;
      if (index < shadow_map_camera.size()) {
        shadow_map_camera[index] = depth_light;
      }
    }
  }
  // Pensar que es shadow_map_camera
    // Vista desde la camara de las sombras?
    // VIsta desde la camara de la depth de light?
  // Light position --> Depth normalizada?
  rasterizer->exportDepthBuffer(shadow_map_camera, "shadows_camera.bmp", image_width, image_height);
  return shadow_map_camera;
}
