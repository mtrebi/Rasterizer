#include "World.h"

World::World(){
    
}
World::World(const std::vector<GeometryObject*>& objects, const std::vector<Light*>& lights, const Camera& camera)
  : m_objects(objects), m_lights(lights), m_camera(camera) {
    
}

World::~World(){
    
}