#ifndef MODEL_H
#define MODEL_H

#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include <QPointF>
#include "objparser.h"

class Model
{
public:
    Model();
    Model(QVector<QVector3D> in_vertices, QVector<QVector2D> in_texture_vertices,
                 QVector<int> in_face_v_indices, QVector<int> in_face_vt_indices, QVector<int> in_face_normal_indices,
                 QVector<int> in_start_pointers);

    QVector<QVector3D> vertices;
    QVector<QVector2D> texture_vertices;
    QVector<int> face_v_indices;
    QVector<int> face_vt_indices;
    QVector<int> face_normal_indices;
    QVector<int> start_pointers;

    static Model model_from_file(const QString &filename);

};

#endif // MODEL_H
