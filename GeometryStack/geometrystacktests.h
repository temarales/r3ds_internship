#ifndef GEOMETRYSTACKTESTS_H
#define GEOMETRYSTACKTESTS_H

#include <QTest>
#include "model.h"
class GeometryStackTests : public QObject
{
    Q_OBJECT
public:
    explicit GeometryStackTests(QObject *parent = 0);
    bool vectorFuzzyCompare(const QVector<int> a, const QVector<int> b);

private slots:
    void testStandartTriangulation();
    void testConcavePolygon();
};

#endif // GEOMETRYSTACKTESTS_H
