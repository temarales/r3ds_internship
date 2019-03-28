#include "scene.h"

Scene::Scene()
{
    QVector<Model> models();
}

Scene::Scene(const QVector<Model> &in_models)
{
    models = in_models;
}

void Scene::add_new_model(const Model &new_model)
{
    models.push_back(new_model);
}

