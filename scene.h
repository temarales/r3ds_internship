#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "GeometryStack/model.h"

class Scene
{
public:
    Scene();
    Scene(const QVector<Model> &inModels);
    QVector<Model> models;

    void addNewModel(const Model &newModel);

};

#endif // SCENE_H
