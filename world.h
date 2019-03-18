#ifndef WORLD_H
#define WORLD_H

#include "camera.h"
#include "model.h"

class World
{
public:
    World();
    Camera camera();
    QVector<Model> models;

};

#endif // WORLD_H
