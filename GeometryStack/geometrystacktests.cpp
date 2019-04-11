#include "geometrystacktests.h"

GeometryStackTests::GeometryStackTests(QObject *parent) : QObject(parent)
{

}

bool GeometryStackTests::vectorFuzzyCompare(const QVector<int> a, const QVector<int> b)
{
    if (a.count() != b.count())
        return false;
    for (int i = 0; i < a.count(); i++)
        if (a[i] != b[i])
            return false;
    return true;
}

void GeometryStackTests::testStandartTriangulation()
{
    Model testModel = Model::modelFromFile("/home/temarales/ShowModel/r3ds/test.obj");
    QVector<int> triangledVertexIndices = {1, 2, 3, 1, 3, 4, 4, 3, 1, 4, 1, 3};
    QVector<int> triangledTextureVertexIndices = {1, 2, 3, 1, 3, 4, 4, 3, 2, 4, 2, 2};
    QString error;
    testModel.triangulate(error);
    //vectorFuzzyCompare(triangledVertexIndices, testModel.triangledFaceVertexIndices);
    //vectorFuzzyCompare(triangledTextureVertexIndices, testModel.triangledFaceTextureVertexIndices);
    QCOMPARE(triangledVertexIndices, testModel.triangledFaceVertexIndices);
    QCOMPARE(triangledTextureVertexIndices, testModel.triangledFaceTextureVertexIndices);
}

void GeometryStackTests::testConcavePolygon()
{
    Model testModel = Model::modelFromFile("/home/temarales/ShowModel/r3ds/test.obj");
    QVector<int> triangledVertexIndices = {};
    QVector<int> triangledTextureVertexIndices = {};
    QString error;
    testModel.triangulate(error);
}
