#ifndef MATRIX_OPER_H
#define MATRIX_OPER_H
#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include <QVector4D>
#include <QMatrix4x4>
#include <QPointF>
#include "camera.h"

namespace Matrix_Oper {
QVector<QVector2D> vertices_for_drawing(
        const QVector<QVector3D> &vertices, Camera &camera, const int &width, const int &height,
        const qreal angle, const qreal nearPlane, const qreal farPlane);
QVector<QPointF> points_for_drawing(const QVector<QVector2D> &vertices);
QVector<QVector2D> world_to_screen(const QVector<QVector3D> &vertices, const int &width, const int &height);
QVector<QVector4D> project_vertices_to_4d(const QVector<QVector3D> &vertices);
QVector<QVector3D> retro_project_vertices_to3d(const QVector<QVector4D> &vertices4d);
void transform_vertices(QVector<QVector4D> &vertices, const QMatrix4x4 mvp);
QMatrix4x4 frustum_matrix(const qreal left, const qreal right, const qreal bottom, const qreal top, const qreal nearPlane, const qreal farPlane);
QMatrix4x4 perspective_matrix(const qreal angle, const qreal aspect, const qreal nearPlane, const qreal farPlane);
QMatrix4x4 create_model_view_projection_matrix(Camera &camera, const qreal angle, const qreal aspect, const qreal nearPlane, const qreal farPlane);
}

#endif // MATRIX_OPER_H
