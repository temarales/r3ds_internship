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
    if (!triangulate(triangledFaceTextureVertexIndices, triangledFaceVertexIndices, this->startPolygonOffsets)) {
        error = "Triangulation has crashed\n";
        return false;
    }
    this->triangledFaceTextureVertexIndices = triangledFaceTextureVertexIndices;
    this->triangledFaceVertexIndices = triangledFaceVertexIndices;
    return true;
}

bool Model::triangulate(
        QVector<int> &triangledFaceTextureVertexIndices, QVector<int> &triangledFaceVertexIndices,
        QVector<int> &polygonOffsets) const
{
    for(int startPolygonOffsetIndex = 0; startPolygonOffsetIndex < polygonOffsets.count() - 1; startPolygonOffsetIndex++) {
        if (!isPolygonConvex(startPolygonOffsetIndex, polygonOffsets))
            return false;
        const int currentPolygonOffset = polygonOffsets[startPolygonOffsetIndex];
        const int nextPolygonOffset = polygonOffsets[startPolygonOffsetIndex + 1];
        for(int vertexIndex = currentPolygonOffset + 1; vertexIndex < nextPolygonOffset - 1; vertexIndex++) {
            addVertexTriangle(triangledFaceVertexIndices, currentPolygonOffset, vertexIndex, vertexIndex + 1);
            addTextureVertexTriangle(triangledFaceTextureVertexIndices, currentPolygonOffset, vertexIndex, vertexIndex + 1);
        }
    }
    return true;
}

float Model::isPositiveValue(
        const int vertexIndex, const int currentPolygonOffset,
        const int nextPolygonOffset) const
{
    const QVector3D firstPoint = this->vertices[this->faceVertexIndices[vertexIndex] - 1];
    QVector3D secondPoint;
    QVector3D thirdPoint;
    if (vertexIndex + 1 == nextPolygonOffset) {
        secondPoint = this->vertices[this->faceVertexIndices[currentPolygonOffset] - 1];
        thirdPoint = this->vertices[this->faceVertexIndices[currentPolygonOffset  +1] - 1];
    }
    else {
        secondPoint = this->vertices[this->faceVertexIndices[vertexIndex + 1] - 1];
        if (vertexIndex + 2 == nextPolygonOffset)
            thirdPoint = this->vertices[this->faceVertexIndices[currentPolygonOffset] - 1];
        else
            thirdPoint = this->vertices[this->faceVertexIndices[vertexIndex + 2] - 1];
    }
    const QVector3D firstVector = secondPoint - firstPoint;
    const QVector3D secondVector = thirdPoint - secondPoint;
    const QVector3D multiplyFirstVectorsPare = firstVector * secondVector;
    const float cosBetweenVectors = (multiplyFirstVectorsPare.x() + multiplyFirstVectorsPare.y() + multiplyFirstVectorsPare.z()) /
            firstVector.length() / secondVector.length();
    const float sinBetweenVectors = 1 - cosBetweenVectors*cosBetweenVectors;

    return sinBetweenVectors;
}

bool Model::isPolygonConvex(int startOffset, QVector<int> &polygonOffsets) const
{
    const int currentPolygonOffset = polygonOffsets[startOffset];
    const int nextPolygonOffset = polygonOffsets[startOffset + 1];
    for (int vertexIndex = currentPolygonOffset; vertexIndex < nextPolygonOffset - 1; vertexIndex += 2) {
        if (isPositiveValue(vertexIndex, currentPolygonOffset, nextPolygonOffset) *
                isPositiveValue(vertexIndex + 1, currentPolygonOffset, nextPolygonOffset) < 0)
            return false;
    }
    return true;
}

void Model::addVertexTriangle(
        QVector<int> &triangledFaceVertexIndices, const int firstIndex,
        const int secondIndex, const int thirdIndex) const
{
    triangledFaceVertexIndices.append(this->faceVertexIndices[firstIndex]);
    triangledFaceVertexIndices.append(this->faceVertexIndices[secondIndex]);
    triangledFaceVertexIndices.append(this->faceVertexIndices[thirdIndex]);
}

void Model::addTextureVertexTriangle(
            QVector<int> &triangledFaceTextureVertexIndices, const int firstIndex,
            const int secondIndex, const int thirdIndex) const
{
    triangledFaceTextureVertexIndices.append(this->faceVertexTextureIndices[firstIndex]);
    triangledFaceTextureVertexIndices.append(this->faceVertexTextureIndices[secondIndex]);
    triangledFaceTextureVertexIndices.append(this->faceVertexTextureIndices[thirdIndex]);
}


