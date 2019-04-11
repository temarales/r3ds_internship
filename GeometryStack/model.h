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
    Model(
            QVector<QVector3D> inVertices, QVector<QVector2D> inTextureVertices,
            QVector<int> inFaceVertexIndices, QVector<int> inFaceTextureVertexIndices,
            QVector<int> inFaceNormalIndices, QVector<int> inStartPointers);

    QVector<QVector3D> vertices;
    QVector<QVector2D> textureVertices;
    QVector<int> faceVertexIndices;
    QVector<int> faceVertexTextureIndices;
    QVector<int> faceNormalIndices;
    QVector<int> startPolygonOffsets;

    QVector<int> triangledFaceVertexIndices;
    QVector<int> triangledFaceTextureVertexIndices;
    static Model modelFromFile(const QString &filename);
    bool triangulate(
            QVector<int> &triangledFaceTextureVertexIndices, QVector<int> &triangledFaceVertexIndices,
            QVector<int> &polygonOffsets) const;
    bool triangulate(QString &error);
    bool isPolygonConvex(int startOffset, QVector<int> &polygonOffsets) const;
    float isPositiveValue(
            const int vertexIndex, const int currentPolygonOffset,
            const int nextPolygonOffset) const;

private:
    void addVertexTriangle(
            QVector<int> &triangledFaceVertexIndices, const int firstIndex,
            const int secondIndex, const int thirdIndex) const;
    void addTextureVertexTriangle(
            QVector<int> &triangledFaceTextureVertexIndices, const int firstIndex,
            const int secondIndex, const int thirdIndex) const;
};

#endif // MODEL_H
