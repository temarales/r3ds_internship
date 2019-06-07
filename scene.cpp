#include "scene.h"

Scene::Scene()
{
    QVector<Model> models;
}

Scene::Scene(const QVector<Model> &inModels)
{
    models = inModels;
}

void Scene::addNewModel(const Model &newModel)
{
    models.push_back(newModel);
}

void Scene::draw(QOpenGLWidget *widget)
{
    for(int modelIndex = 0; modelIndex < this->models.count(); modelIndex++)
        this->models[modelIndex].draw(widget);
}

void Scene::drawOriginalGrid(QOpenGLWidget *widget)
{
    for(int modelIndex = 0; modelIndex < this->models.count(); modelIndex++)
        this->models[modelIndex].drawOriginalGrid(widget);
}

void Scene::drawTriangledGrid(QOpenGLWidget *widget)
{
    for(int modelIndex = 0; modelIndex < this->models.count(); modelIndex++)
        this->models[modelIndex].drawTriangledGrid(widget);
}

