#ifndef MATRIX_OPER_H
#define MATRIX_OPER_H
#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include <QVector4D>
#include <QMatrix4x4>
#include "camera.h"

class Matrix_Oper
{
public:
    Matrix_Oper();

    QMatrix4x4 identity_matrix();
    QVector<QVector2D> world_to_screen(QVector<QVector3D> &vertices, const int &xSize, const int &ySize, const int &dist);
    QVector<QVector4D> project_vertices_to_4d(const QVector<QVector3D> &vertices);
    QVector<QVector3D> retro_project_vertices_to3d(const float c, const QVector<QVector4D> &vertices4d);

    QMatrix4x4 view_matrix(const Camera camera);
    QMatrix4x4 create_model_view_projection_matrix();
};

#endif // MATRIX_OPER_H
