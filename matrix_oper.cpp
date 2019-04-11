#include "matrix_oper.h"


QVector<QVector2D> Matrix_Oper::verticesForDrawing(
        const QVector<QVector3D> &vertices, const Camera &camera, const int &width, const int &height,
        const qreal angle, const qreal nearPlane, const qreal farPlane)
{
    QVector<QVector4D> vertices_4d = projectVerticesTo4d(vertices);
    const qreal aspect = qreal(width)/height;
    transformVertices(vertices_4d, createModelViewProjectionMatrix(camera, angle, aspect, nearPlane, farPlane));
    QVector<QVector3D> newVertices = projectVerticesTo3d(vertices_4d);
    QVector<QVector2D> drawVertices = worldToScreen(newVertices, width, height);
    return drawVertices;
}



QVector<QPointF> Matrix_Oper::pointsForDrawing(const QVector<QVector2D> &vertices)
{
    QVector<QPointF> points;
    points.reserve(vertices.size());
    for (const QVector2D &vertex : vertices) {
        const QPointF point = vertex.toPointF();
        points.append(point);
    }
    return points;
}

void Matrix_Oper::transformVertices(QVector<QVector4D> &vertices, const QMatrix4x4 mvp)
{
    for (int i = 0; i < vertices.length(); i++)
        vertices[i] = mvp * vertices[i];
}

QVector<QVector2D> Matrix_Oper::worldToScreen(const QVector<QVector3D> &vertices, const int &width, const int &height)
{
    QVector<QVector2D> screenVertices;
    screenVertices.reserve(vertices.size());
    for (const QVector3D &vertex : vertices) {
        const QVector2D screenVertex = QVector2D((vertex.x() + 1) / 2 * width,
                                                 (1 - (vertex.y()+ 1) / 2) * height);
        screenVertices.push_back(screenVertex);
    }
    return screenVertices;
}

QVector<QVector4D> Matrix_Oper::projectVerticesTo4d(const QVector<QVector3D> &vertices)
{
    QVector<QVector4D> homogeneousVertices;
    homogeneousVertices.reserve(vertices.size());
    for (const QVector3D &vertex : vertices) {
        const QVector4D homogeneousVertex(vertex, 1);
        homogeneousVertices.push_back(homogeneousVertex);
    }
    return homogeneousVertices;
}

QVector<QVector3D> Matrix_Oper::projectVerticesTo3d(const QVector<QVector4D> &vertices4d)
{
    QVector<QVector3D> vertices3d; //https://github.com/ssloy/tinyrenderer/wiki/Lesson-4:-Perspective-projection
    vertices3d.reserve(vertices4d.size());
    for (int i = 0; i < vertices4d.size(); i++) {
        const QVector3D vertex3d(vertices4d[i].x()/vertices4d[i].w(),
                                 vertices4d[i].y()/vertices4d[i].w(),
                                 vertices4d[i].z()/vertices4d[i].w());
        vertices3d.push_back(vertex3d);
    }
    return vertices3d;
}

QMatrix4x4 Matrix_Oper::frustumMatrix(const qreal left, const qreal right, const qreal bottom, const qreal top, const qreal nearPlane, const qreal farPlane)
{
    QMatrix4x4 frustumMatrix;
    frustumMatrix.frustum(left, right, bottom, top, nearPlane, farPlane);
    return frustumMatrix;
}

QMatrix4x4 Matrix_Oper::perspectiveMatrix(const qreal angle, const qreal aspect, const qreal nearPlane, const qreal farPlane)
{
    QMatrix4x4 perspectiveMatrix;
    perspectiveMatrix.perspective(angle, aspect, nearPlane, farPlane);
    return perspectiveMatrix;
}

QMatrix4x4 Matrix_Oper::createModelViewProjectionMatrix(const Camera &camera, const qreal angle, const qreal aspect, const qreal nearPlane, const qreal farPlane)
{
    QMatrix4x4 modelMatrix;
    modelMatrix.translate(QVector3D(3, 3, 3));

    const QMatrix4x4 ModelViewProjectionMatrix = perspectiveMatrix(angle, aspect, nearPlane, farPlane) * camera.view_matrix()*modelMatrix;

    return ModelViewProjectionMatrix;
}




