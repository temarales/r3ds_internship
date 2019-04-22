#include "model.h"

Model::Model()
{

}

Model::Model(QVector<QVector3D> inVertices, QVector<QVector2D> inTextureVertices,
             QVector<int> inFaceVertexIndices, QVector<int> inFaceTextureVertexIndices, QVector<int> inFaceNormalIndices,
             QVector<int> inStartPointers)
{
    vertices = inVertices;
    textureVertices = inTextureVertices;
    faceVertexIndices = inFaceVertexIndices;
    faceVertexTextureIndices = inFaceTextureVertexIndices;
    faceNormalIndices = inFaceNormalIndices;
    startPolygonOffsets = inStartPointers;
}

Model Model::modelFromFile(const QString &filename)
{
    QString error = nullptr;
    QVector<QVector3D> newVertices;
    QVector<QVector2D> newTextureVertices;
    QVector<int> newFaceVertexIndices;
    QVector<int> newFaceVertexTextureIndices;
    QVector<int> newFaceNormalIndices;
    QVector<int> newStartPointers;

    ObjParser::fileImport(filename, newVertices, newTextureVertices, newFaceVertexIndices,
                           newFaceVertexTextureIndices, newFaceNormalIndices, newStartPointers, error);

    Model newModel(newVertices, newTextureVertices, newFaceVertexIndices,
                    newFaceVertexTextureIndices, newFaceNormalIndices, newStartPointers);
    return newModel;
}


bool Model::triangulate(QString &error)
{
    QVector<int> triangledFaceTextureVertexIndices;
    QVector<int> triangledFaceVertexIndices;
    if (this->faceVertexTextureIndices.count() == 0) {
        error = "Triangulation has crashed, there are no texture vertices\n";
        return false;
    }
    if (!TranformationsForModel::triangulate(triangledFaceTextureVertexIndices, triangledFaceVertexIndices,
                     this->startPolygonOffsets, this->faceVertexIndices, this->faceVertexTextureIndices)) {
        error = "Triangulation has crashed\n";
        return false;
    }
    this->triangledFaceTextureVertexIndices = triangledFaceTextureVertexIndices;
    this->triangledFaceVertexIndices = triangledFaceVertexIndices;
    return true;
}

void Model::calculateNewNormals()
{
    TranformationsForModel::calculateNormals(
                this->normalsForVertices, this->triangledFaceVertexIndices, this->vertices, this->faceVertexIndices);
}


/*void Model::edgesFromVertices(
        const int vertexIndex, const int currentPolygonOffset, const int nextPolygonOffset,
        QVector3D &firstEdge, QVector3D &secondEdge) const
{
    const QVector3D firstPoint = this->vertices[this->faceVertexIndices[vertexIndex] - 1];
    QVector3D secondPoint;
    QVector3D thirdPoint;
    if (vertexIndex + 1 == nextPolygonOffset) {
        secondPoint = this->vertices[this->faceVertexIndices[currentPolygonOffset] - 1];
        thirdPoint = this->vertices[this->faceVertexIndices[currentPolygonOffset + 1] - 1];
    }
    else {
        secondPoint = this->vertices[this->faceVertexIndices[vertexIndex + 1] - 1];
        if (vertexIndex + 2 == nextPolygonOffset)
            thirdPoint = this->vertices[this->faceVertexIndices[currentPolygonOffset] - 1];
        else
            thirdPoint = this->vertices[this->faceVertexIndices[vertexIndex + 2] - 1];
    }
    firstEdge = secondPoint - firstPoint;
    secondEdge = thirdPoint - secondPoint;
}


float Model::sinBetweenVectors(const QVector3D firstEdge, const QVector3D secondEdge) const
{
    const QVector3D scalarMultiplicationOfEdges = firstEdge * secondEdge;
    const float cosBetweenVectors = (scalarMultiplicationOfEdges.x() + scalarMultiplicationOfEdges.y() + scalarMultiplicationOfEdges.z())
            / firstEdge.length() / secondEdge.length();
    const float sinBetweenVectors = 1 - cosBetweenVectors * cosBetweenVectors;

    return sinBetweenVectors;
}

float Model::signOfTurnSin(
        const int vertexIndex, const int currentPolygonOffset,
        const int nextPolygonOffset) const
{
    QVector3D firstEdge, secondEdge;
    edgesFromVertices(vertexIndex, currentPolygonOffset, nextPolygonOffset, firstEdge, secondEdge);
    const float sinOfTurn = sinBetweenVectors(firstEdge, secondEdge);
    if (sinOfTurn > 0)
        return 1;
    else if (0 == sinOfTurn)
        return 0;
    else
        return -1;
}

bool Model::isPolygonConvex(int startOffset, QVector<int> &polygonOffsets) const
{
    const int currentPolygonOffset = polygonOffsets[startOffset];
    const int nextPolygonOffset = polygonOffsets[startOffset + 1];
    for (int vertexIndex = currentPolygonOffset; vertexIndex < nextPolygonOffset - 1; vertexIndex += 1) {
        if (signOfTurnSin(vertexIndex, currentPolygonOffset, nextPolygonOffset) *
                signOfTurnSin(vertexIndex + 1, currentPolygonOffset, nextPolygonOffset) < 0)
            return false;
    }
    return true;
}*/

