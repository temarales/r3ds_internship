#include "model.h"

Model::Model(QVector<QVector3D> in_vertices, QVector<QVector2D> in_texture_vertices,
             QVector<int> in_faces, QVector<int> in_texture_faces)
{
    vertices = in_vertices;
    texture_vertices = in_texture_vertices;
    faces = in_faces;
    texture_faces = in_texture_faces;
}
