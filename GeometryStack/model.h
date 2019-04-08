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
    QVector<int> startPointers;

    static Model modelFromFile(const QString &filename);
    void triangulate();

};

#endif // MODEL_H
