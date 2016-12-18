#ifndef GEOMETRYOBJECT_H
#define GEOMETRYOBJECT_H

#include "Point3D.h"

class GeometryObject {
protected:
    Point3D m_position;
public:
    GeometryObject();
    GeometryObject(const Point3D position);  
    
    // TODO: Some kind of projection
    
    ~GeometryObject();
};


#endif /* GEOMETRYOBJECT_H */

