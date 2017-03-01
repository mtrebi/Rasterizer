#include "Rasterizer.h"

Rasterizer::Rasterizer()
  : Renderer() {

}

Rasterizer::Rasterizer(const World* world)
  : Renderer(world) {

}

Rasterizer::~Rasterizer() {
}


const Fragment Rasterizer::calculateFragmentAttributes(const Triangle3D& triangle_world, const Point3D& point_world, const Triangle2D& triangle_screen, const Point2D& pixel_screen, const Material& material) const {
  const Vector2D text_coords = calculateTextureCoords(triangle_world, point_world, triangle_screen, pixel_screen);
  const Fragment f {
    point_world,
    calculateColor(triangle_world, point_world),
    material.getDiffuseColor(text_coords), 
    material.getSpecularColor(text_coords),
    material.getNormal(triangle_world, text_coords)
  };
  
  return f;
}

// Calculate depth in screen space and then interpolate using inverse function (1/z) 
const double Rasterizer::calculateDepth(const Triangle3D& triangle_world, const Triangle2D& triangle_raster, const Point2D& pixel_raster) const {
  const Triangle3D triangle_camera = Triangle3D(
    Vertex3D (m_camera->viewTransform(triangle_world.v1.position), triangle_world.v1.color, triangle_world.v1.texture_coords, triangle_world.v1.normal),
    Vertex3D(m_camera->viewTransform(triangle_world.v2.position), triangle_world.v2.color, triangle_world.v2.texture_coords, triangle_world.v1.normal),
    Vertex3D(m_camera->viewTransform(triangle_world.v3.position), triangle_world.v3.color, triangle_world.v3.texture_coords, triangle_world.v1.normal)
  );

  // Calculate barycentric coords in camera space
  double u, v, w;
  triangle_raster.calculateBarycentricCoords(u, v, w, pixel_raster);
  // Interpolate Z in 3D using inverse function and barycentric coordinates in 2D
  const double depth = 1 / 
    (
      (1 / triangle_camera.v1.position.z) * u + 
      (1 / triangle_camera.v2.position.z) * v + 
      (1 / triangle_camera.v3.position.z) * w
    );
  return depth;
}

const Vector2D Rasterizer::calculateTextureCoords(const Triangle3D& triangle_world, const Point3D& pixel_world, const Triangle2D& triangle_camera, const Point2D& pixel_camera) const {
  // Calculate barycentric coords in screen space  (inverse linear)
  double u, v, w;
#ifdef _AFFINE_TEXTURES
  triangle_camera.calculateBarycentricCoords(u, v, w, pixel_camera);
#endif 
#ifdef _PERSPECTIVE_TEXTURES
  triangle_world.calculateBarycentricCoords(u, v, w, pixel_world);
#endif 

  const Vector2D texture_coords = 
    triangle_world.v1.texture_coords * u + 
    triangle_world.v2.texture_coords * v +
    triangle_world.v3.texture_coords * w;

  const Vector2D texture_coords_abs_screen {
    abs(texture_coords.x),
    abs(texture_coords.y)
  };

  return texture_coords_abs_screen;

  /*

  // Divide texture attribute at vertices by their z-coord
  Vector2D v1t = triangle_world.v1.texture_coords / abs(triangle_world.v1.position.z);
  Vector2D v2t = triangle_world.v2.texture_coords / abs(triangle_world.v2.position.z);
  Vector2D v3t = triangle_world.v3.texture_coords / abs(triangle_world.v3.position.z);

  float v1t_ = 1.0 / abs(triangle_world.v1.position.z);
  float v2t_ = 1.0 / abs(triangle_world.v2.position.z);
  float v3t_ = 1.0 / abs(triangle_world.v3.position.z);

  const Vector2D texture_coords2 =
    v1t * u +
    v2t * v +
    v3t * w;

  const float z = 1.0 / 
    (
      v1t_ * u +
      v2t_ * v +
      v3t_ * w
    );

  const Vector2D result = {
    texture_coords2.x * z,
    texture_coords2.y * z
  };

  return result;
  */
}

const RGBColor Rasterizer::calculateColor(const Triangle3D& triangle_world, const Point3D& point_world) const {
  // Calculate barycentric coords in camera space
  double u, v, w;
  triangle_world.calculateBarycentricCoords(u, v, w, point_world);
  const RGBColor new_color = triangle_world.v1.color * u + triangle_world.v2.color * v + triangle_world.v3.color * w;
  return new_color;
}

// World to raster/screen space
const Point2D Rasterizer::rasterize(const Point3D& point_world) const {
  const Point3D point_camera = m_camera->viewTransform(point_world);
  const Point2D point_ndc = m_camera->projectTransform(point_camera);
  //const Point2D point_ = m_camera->ndcTransform(point_ndc);
  const Point2D point_raster = m_camera->viewportTransform(point_ndc);  
  return point_raster;
}

// World to raster/screen space
const Triangle2D Rasterizer::rasterize(const Triangle3D& triangle_world) const {
  return Triangle2D(
    rasterize(triangle_world.v1.position),
    rasterize(triangle_world.v2.position),
    rasterize(triangle_world.v3.position)
  );
}


// Raster/screen space to world
const Point3D Rasterizer::unrasterize(const Point2D& point_raster, const double depth_from_camera) const {
  const Point2D point_ndc = m_camera->viewportTransformInv(point_raster);
  const Point3D point_camera = m_camera->projectTransformInv(point_ndc, depth_from_camera);
  const Point3D point_world= m_camera->viewTransformInv(point_camera);
  return point_world;
}
