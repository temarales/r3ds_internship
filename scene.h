#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "ipainter.h"
#include "GeometryStack/model.h"

class Scene : public IPainter
{
public:
    Scene();
    Scene(const QVector<Model> &inModels);
    QVector<Model> models;

    void addNewModel(const Model &newModel);
    void draw(QOpenGLWidget *widget, ...) override;

};

#endif // SCENE_H
