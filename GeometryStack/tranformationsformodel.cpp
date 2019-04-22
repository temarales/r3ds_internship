#include "tranformationsformodel.h"

bool TranformationsForModel::triangulate(
        QVector<int> &triangledFaceTextureVertexIndices, QVector<int> &triangledFaceVertexIndices,
        const QVector<int> &polygonOffsets, const QVector<int> &faceVertexIndices,
        const QVector<int> &faceTextureVertexIndices)
{
    for(int startPolygonOffsetIndex = 0; startPolygonOffsetIndex < polygonOffsets.count() - 1; startPolygonOffsetIndex++) {
        //if (!isPolygonConvex(startPolygonOffsetIndex, polygonOffsets))
          //  return false;
        const int currentPolygonOffset = polygonOffsets[startPolygonOffsetIndex];
        const int nextPolygonOffset = polygonOffsets[startPolygonOffsetIndex + 1];
        for(int vertexIndex = currentPolygonOffset + 1; vertexIndex < nextPolygonOffset - 1; vertexIndex++) {
            addVertexTriangle(triangledFaceVertexIndices, faceVertexIndices, currentPolygonOffset, vertexIndex, vertexIndex + 1);
            addTextureVertexTriangle(triangledFaceTextureVertexIndices, faceTextureVertexIndices, currentPolygonOffset, vertexIndex, vertexIndex + 1);
        }
    }
    return true;
}

void TranformationsForModel::addVertexTriangle(
        QVector<int> &triangledFaceVertexIndices,
        const QVector<int> &faceVertexIndices, const int firstIndex,
        const int secondIndex, const int thirdIndex)
{
    triangledFaceVertexIndices.append(faceVertexIndices[firstIndex]);
    triangledFaceVertexIndices.append(faceVertexIndices[secondIndex]);
    triangledFaceVertexIndices.append(faceVertexIndices[thirdIndex]);
}

void TranformationsForModel::addTextureVertexTriangle(
        QVector<int> &triangledFaceTextureVertexIndices,
        const QVector<int> &faceVertexTextureIndices, const int firstIndex,
        const int secondIndex, const int thirdIndex)
{
    triangledFaceTextureVertexIndices.append(faceVertexTextureIndices[firstIndex]);
    triangledFaceTextureVertexIndices.append(faceVertexTextureIndices[secondIndex]);
    triangledFaceTextureVertexIndices.append(faceVertexTextureIndices[thirdIndex]);
}

void TranformationsForModel::calculateNormals(
        QVector<QVector3D> &newNormalsForVertices,
        const QVector<int> &triangledFaceVertexIndices, const QVector<QVector3D> &vertices,
        const QVector<int> &faceVertexIndices)
{
    QVector<QVector3D> normalsForTriangledPolygons;
    QVector<QVector3D> normalsForVertices;
    calculateNormalsForTriangulatedPolygons(
                normalsForTriangledPolygons, triangledFaceVertexIndices, vertices, faceVertexIndices);
    calculateNormalsForVertices(
                normalsForVertices, triangledFaceVertexIndices, vertices, normalsForTriangledPolygons);
    newNormalsForVertices = normalsForVertices;
}

void TranformationsForModel::calculateNormalsForVertices(
        QVector<QVector3D> &newNormalsForVertices,
        const QVector<int> &triangledFaceVertexIndices, const QVector<QVector3D> &vertices,
        const QVector<QVector3D> &normalForTriangledPolygons)
{
    newNormalsForVertices.resize(vertices.count());
    for (int normalIndex = 0; normalIndex < newNormalsForVertices.count(); normalIndex++)
        newNormalsForVertices[normalIndex] = QVector3D(0, 0, 0);

    for(int i = 0; i < triangledFaceVertexIndices.count(); i++) {
        QVector<QVector3D> normalsOfVertex;
        const int vertexIndexInVertices = triangledFaceVertexIndices[i] - 1;
        const QVector3D vertex = vertices[vertexIndexInVertices];

        if (newNormalsForVertices[vertexIndexInVertices] != QVector3D(0, 0, 0))
            continue;

        for (int currentIndexInTriangled = i; currentIndexInTriangled < triangledFaceVertexIndices.count(); currentIndexInTriangled++)
        {
            const QVector3D currenVertex = vertices[triangledFaceVertexIndices[currentIndexInTriangled] - 1];
            if(currenVertex == vertex)
                normalsOfVertex.append(normalForTriangledPolygons[currentIndexInTriangled/3]);
        }

        QVector3D newNormalForVertice;
        for (int normalIndex = 0; normalIndex < normalsOfVertex.count(); normalIndex++)
            newNormalForVertice += normalsOfVertex[normalIndex];
        newNormalForVertice /= normalsOfVertex.count();
        newNormalsForVertices[vertexIndexInVertices] = newNormalForVertice;
    }
}

bool TranformationsForModel::calculateNormalsForTriangulatedPolygons(
        QVector<QVector3D> &normalsForTriangledPolygons,
        const QVector<int> &triangledFaceVertexIndices, const QVector<QVector3D> &vertices,
        const QVector<int> &faceVertexIndices)
{
    if (triangledFaceVertexIndices.count() == 0)
        return false;
    for(int vertexIndex = 0; vertexIndex < triangledFaceVertexIndices.count()/3; vertexIndex++) {
        QVector3D firstVector, secondVector;
        vectorsFromPoints(firstVector, secondVector, vertices, faceVertexIndices, vertexIndex);
        const QVector3D normal = QVector3D::normal(firstVector, secondVector);
        normalsForTriangledPolygons.append(normal);
    }
    return true;
}

void TranformationsForModel::vectorsFromPoints(
        QVector3D &firstVector, QVector3D &secondVector,
        const QVector<QVector3D> vertices, const QVector<int> faceVertexIndices,
        const int vertexIndex)
{
    const QVector3D firstPoint = vertices[faceVertexIndices[vertexIndex] - 1];
    const QVector3D secondPoint = vertices[faceVertexIndices[vertexIndex + 1] - 1];
    const QVector3D thirdPoint = vertices[faceVertexIndices[vertexIndex + 2] - 1];
    firstVector = secondPoint - firstPoint;
    secondVector = thirdPoint - secondPoint;
}
