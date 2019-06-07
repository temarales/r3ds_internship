#ifndef MODEL_H
#define MODEL_H

#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include <QPointF>
#include "objparser.h"
#include "tranformationsformodel.h"
#include "DrawingTools/ipainter.h"

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
    void triangulate(QString &error);
    void calculateNewNormals();

    void draw(QOpenGLWidget* widget) override;
    void drawOriginalGrid(QOpenGLWidget* widget) override;
    void drawTriangledGrid(QOpenGLWidget* widget) override;
};

#endif // MODEL_H
