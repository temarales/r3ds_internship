#ifndef MODEL_H
#define MODEL_H

#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include <QPointF>
#include "objparser.h"
#include "tranformationsformodel.h"
#include "ipainter.h"

class Model : public IPainter
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
    QVector<QVector3D> normalsForVertices;
    static Model modelFromFile(const QString &filename);
    bool triangulate(QString &error);
    void calculateNewNormals();
    void draw(QOpenGLWidget* widget, ...) override;


    /*bool isPolygonConvex(int startOffset, QVector<int> &polygonOffsets) const;
    float sinBetweenVectors(const QVector3D firstEdge, const QVector3D secondEdge) const;
    void edgesFromVertices(
            const int vertexIndex, const int currentPolygonOffset, const int nextPolygonOffset,
            QVector3D &firstEdge, QVector3D &secondEdge) const;
    float signOfTurnSin(
            const int vertexIndex, const int currentPolygonOffset,
            const int nextPolygonOffset) const;*/

private:
    //bool vectorsFromPoints(const int vertexIndex, QVector3D &firstVector, QVector3D &secondVector) const;
};

#endif // MODEL_H
