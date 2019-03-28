#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "model.h"

class Scene
{
public:
    Scene();
    Scene(const QVector<Model> &in_models);
    QVector<Model> models;

    void add_new_model(const Model &new_model);

};

#endif // SCENE_H
