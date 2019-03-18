#ifndef MODEL_H
#define MODEL_H

#include <QVector3D>
#include <QVector2D>
#include <QVector>


class Model
{
public:
    Model(QVector<QVector3D> in_vertices, QVector<QVector2D> in_texture_vertices,
          QVector<int> in_faces, QVector<int> in_texture_faces);
    QVector<QVector3D> vertices;
    QVector<QVector2D> texture_vertices;
    QVector<int> faces;
    QVector<int> texture_faces;

};

#endif // MODEL_H
