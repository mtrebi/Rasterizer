#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>
#include "Light.h"
#include "GeometryObject.h"
#include "Camera.h"

class World {
public:
    std::vector<GeometryObject*> m_objects;
    std::vector<Light*> m_lights;
    Camera* m_camera;

public:
    World();
    World(const std::vector<GeometryObject*>& objects, const std::vector<Light*>& lights, Camera* camera);
    ~World();
};

#endif /* WORLD_H */

