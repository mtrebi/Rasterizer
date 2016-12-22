#include "World.h"

World::World(){
    
}

World::World(const std::vector<GeometryObject>& objects, std::vector<Light>& lights, Camera& camera)
    : m_objects(objects), m_lights(lights), m_camera(camera) {
    
}

World::~World(){
    
}