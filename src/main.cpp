#include <iostream>
#include <vector>

#include "World.h"
#include "Renderer.h"
#include "Rasterizer.h"
#include "Camera.h"
#include "Light.h"


int main (){
    
    std::vector<GeometryObject*> objects = std::vector<GeometryObject*>() {
        
    };
    
    std::vector<Light*> lights = std::vector<Light*>() {
        
    };
    
    Camera camera = Camera(Point3D(.0f, .0f, -10.0f), Vector3D(.0f, .0f, 1.0f));
    
    World * world = new World(objects, lights, camera);
    Renderer * renderer = new Rasterizer(world);
    renderer->render(640, 480, "output.bmp");

    return 0;
}