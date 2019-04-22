#ifndef TRANFORMATIONSFORMODEL_H
#define TRANFORMATIONSFORMODEL_H

#include <QVector3D>
#include <QVector2D>
#include <QVector>


namespace TranformationsForModel {

bool triangulate(
        QVector<int> &triangledFaceTextureVertexIndices, QVector<int> &triangledFaceVertexIndices,
        const QVector<int> &polygonOffsets, const QVector<int> &faceVertexIndices,
        const QVector<int> &faceTextureVertexIndices);
void addVertexTriangle(
        QVector<int> &triangledFaceVertexIndices,
        const QVector<int> &faceVertexIndices, const int firstIndex,
        const int secondIndex, const int thirdIndex);
void addTextureVertexTriangle(
        QVector<int> &triangledFaceTextureVertexIndices,
        const QVector<int> &faceVertexTextureIndices, const int firstIndex,
        const int secondIndex, const int thirdIndex);

void calculateNormals(
        QVector<QVector3D> &newNormalsForVertices,
        const QVector<int> &triangledFaceVertexIndices, const QVector<QVector3D> &vertices,
        const QVector<int> &faceVertexIndices);
void calculateNormalsForVertices(
        QVector<QVector3D> &newNormalsForVertices,
        const QVector<int> &triangledFaceVertexIndices, const QVector<QVector3D> &vertices,
        const QVector<QVector3D> &normalForTriangledPolygons);
bool calculateNormalsForTriangulatedPolygons(
        QVector<QVector3D> &normalsForTriangledPolygons,
        const QVector<int> &triangledFaceVertexIndices, const QVector<QVector3D> &vertices,
        const QVector<int> &faceVertexIndices);
void vectorsFromPoints(
        QVector3D &firstVector, QVector3D &secondVector,
        const QVector<QVector3D> vertices, const QVector<int> faceVertexIndices,
        const int vertexIndex);
}

#endif // TRANFORMATIONSFORMODEL_H
