#include "geometrystacktests.h"

GeometryStackTests::GeometryStackTests(QObject *parent) : QObject(parent)
{

}

void GeometryStackTests::testTriangulationTriangle()
{
    const QVector<int> faceVertexIndices = {1, 3, 2};
    const QVector<int> faceTextureVertexIndices = {2, 1, 3};
    const QVector<int> polygonOffests = {0, 3};
    const QVector<int> idealTriangledFaceVertexIndices = {1, 3, 2};
    const QVector<int> idealTriangledFaceTextureVertexIndices = {2, 1, 3};
    QVector<int> triangledFaceVertexIndices, triangledFaceTextureVertexIndices;
    TranformationsForModel::triangulate(triangledFaceTextureVertexIndices, triangledFaceVertexIndices,
                                        polygonOffests, faceVertexIndices, faceTextureVertexIndices);
    QCOMPARE(triangledFaceTextureVertexIndices, idealTriangledFaceTextureVertexIndices);
    QCOMPARE(triangledFaceVertexIndices, idealTriangledFaceVertexIndices);

}

void GeometryStackTests::testTriangulationQuadrangle()
{
    const QVector<int> faceVertexIndices = {1, 3, 2, 4};
    const QVector<int> faceTextureVertexIndices = {2, 1, 3, 4};
    const QVector<int> polygonOffests = {0, 4};
    const QVector<int> idealTriangledFaceVertexIndices = {1, 3, 2, 1, 2, 4};
    const QVector<int> idealTriangledFaceTextureVertexIndices = {2, 1, 3, 2, 3, 4};
    QVector<int> triangledFaceVertexIndices, triangledFaceTextureVertexIndices;
    TranformationsForModel::triangulate(triangledFaceTextureVertexIndices, triangledFaceVertexIndices,
                                        polygonOffests, faceVertexIndices, faceTextureVertexIndices);
    QCOMPARE(triangledFaceTextureVertexIndices, idealTriangledFaceTextureVertexIndices);
    QCOMPARE(triangledFaceVertexIndices, idealTriangledFaceVertexIndices);

}

void GeometryStackTests::testTriangulationPentagon()
{
    const QVector<int> faceVertexIndices = {1, 3, 2, 5, 4};
    const QVector<int> faceTextureVertexIndices = {2, 1, 3, 2, 1};
    const QVector<int> polygonOffests = {0, 5};
    const QVector<int> idealTriangledFaceVertexIndices = {1, 3, 2, 1, 2, 5, 1, 5, 4};
    const QVector<int> idealTriangledFaceTextureVertexIndices = {2, 1, 3, 2, 3, 2, 2, 2, 1};
    QVector<int> triangledFaceVertexIndices, triangledFaceTextureVertexIndices;
    TranformationsForModel::triangulate(triangledFaceTextureVertexIndices, triangledFaceVertexIndices,
                                        polygonOffests, faceVertexIndices, faceTextureVertexIndices);
    QCOMPARE(triangledFaceTextureVertexIndices, idealTriangledFaceTextureVertexIndices);
    QCOMPARE(triangledFaceVertexIndices, idealTriangledFaceVertexIndices);
}

void GeometryStackTests::testTriangulationHexagon()
{
    const QVector<int> faceVertexIndices = {1, 3, 2, 4, 6, 5};
    const QVector<int> faceTextureVertexIndices = {2, 1, 3, 4, 3, 1};
    const QVector<int> polygonOffests = {0, 6};
    const QVector<int> idealTriangledFaceVertexIndices = {1, 3, 2, 1, 2, 4, 1, 4, 6, 1, 6, 5};
    const QVector<int> idealTriangledFaceTextureVertexIndices = {2, 1, 3, 2, 3, 4, 2, 4, 3, 2, 3, 1};
    QVector<int> triangledFaceVertexIndices, triangledFaceTextureVertexIndices;
    TranformationsForModel::triangulate(triangledFaceTextureVertexIndices, triangledFaceVertexIndices,
                                        polygonOffests, faceVertexIndices, faceTextureVertexIndices);
    QCOMPARE(triangledFaceTextureVertexIndices, idealTriangledFaceTextureVertexIndices);
    QCOMPARE(triangledFaceVertexIndices, idealTriangledFaceVertexIndices);

}

void GeometryStackTests::testTriangulationHeptagon()
{
    const QVector<int> faceVertexIndices = {1, 3, 2, 4, 6, 5, 7};
    const QVector<int> faceTextureVertexIndices = {2, 1, 3, 4, 4, 2, 5};
    const QVector<int> polygonOffests = {0, 7};
    const QVector<int> idealTriangledFaceVertexIndices = {1, 3, 2, 1, 2, 4, 1, 4, 6, 1, 6, 5, 1, 5, 7};
    const QVector<int> idealTriangledFaceTextureVertexIndices = {2, 1, 3, 2, 3, 4, 2, 4, 4, 2, 4, 2, 2, 2, 5};
    QVector<int> triangledFaceVertexIndices, triangledFaceTextureVertexIndices;
    TranformationsForModel::triangulate(triangledFaceTextureVertexIndices, triangledFaceVertexIndices,
                                        polygonOffests, faceVertexIndices, faceTextureVertexIndices);
    QCOMPARE(triangledFaceTextureVertexIndices, idealTriangledFaceTextureVertexIndices);
    QCOMPARE(triangledFaceVertexIndices, idealTriangledFaceVertexIndices);

}

void GeometryStackTests::testTriangulationSet()
{
    const QVector<int> faceVertexIndices = {1, 3, 2, 4, 6, 5, 7};
    const QVector<int> faceTextureVertexIndices = {2, 1, 3, 4, 4, 2, 5};
    const QVector<int> polygonOffests = {0, 3, 7};
    const QVector<int> idealTriangledFaceVertexIndices = {1, 3, 2, 4, 6, 5, 4, 5, 7};
    const QVector<int> idealTriangledFaceTextureVertexIndices = {2, 1, 3, 4, 4, 2, 4, 2, 5};
    QVector<int> triangledFaceVertexIndices, triangledFaceTextureVertexIndices;
    TranformationsForModel::triangulate(triangledFaceTextureVertexIndices, triangledFaceVertexIndices,
                                        polygonOffests, faceVertexIndices, faceTextureVertexIndices);
    QCOMPARE(triangledFaceTextureVertexIndices, idealTriangledFaceTextureVertexIndices);
    QCOMPARE(triangledFaceVertexIndices, idealTriangledFaceVertexIndices);

}

void GeometryStackTests::testCalculateNormalsForVertices()
{

}

/*void GeometryStackTests::testConcavePolygon()
{
    Model testModel = Model::modelFromFile("/home/temarales/ShowModel/r3ds/testIsConcave1.obj");
    //QVector<int> triangledVertexIndices = {};
    //QVector<int> triangledTextureVertexIndices = {};
    QString error;
    QVERIFY(!testModel.triangulate(error));
}*/
