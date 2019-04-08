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

QVector<QVector2D> verticesForDrawing(
        const QVector<QVector3D> &vertices, const Camera &camera, const int &width, const int &height,
        const qreal angle, const qreal nearPlane, const qreal farPlane);

QVector<QPointF> pointsForDrawing(const QVector<QVector2D> &vertices);

QVector<QVector2D> worldToScreen(
        const QVector<QVector3D> &vertices,
        const int &screenWidth, const int &sreenHeight);

QVector<QVector4D> projectVerticesTo4d(const QVector<QVector3D> &vertices);

QVector<QVector3D> projectVerticesTo3d(const QVector<QVector4D> &vertices4d);

void transformVertices(QVector<QVector4D> &vertices, const QMatrix4x4 mvp);

QMatrix4x4 frustumMatrix(
        const qreal left, const qreal right, const qreal bottom,
        const qreal top, const qreal nearPlane, const qreal farPlane);

QMatrix4x4 perspectiveMatrix(
        const qreal angle, const qreal aspect,
        const qreal nearPlane, const qreal farPlane);

QMatrix4x4 createModelViewProjectionMatrix(
        const Camera &camera, const qreal angle, const qreal aspect,
        const qreal nearPlane, const qreal farPlane);
}

#endif // MATRIX_OPER_H
