#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>
#include "Light.h"
#include "GeometryObject.h"
#include "Camera.h"
#include "Renderer.h"

class World {
    friend class Renderer;
private:
    std::vector<GeometryObject*> m_objects;
    std::vector<Light*> m_lights;
    Camera m_camera;

public:
    World();
    World(const std::vector<GeometryObject*>& objects, const std::vector<Light*>& lights, const Camera& camera);
    ~World();
};

#endif /* WORLD_H */

