#ifndef GEOMETRYSTACKTESTS_H
#define GEOMETRYSTACKTESTS_H

#include <QTest>
#include "model.h"
#include "tranformationsformodel.h"

class GeometryStackTests : public QObject
{
    Q_OBJECT
public:
    explicit GeometryStackTests(QObject *parent = 0);

private slots:
    void testTriangulationTriangle();
    void testTriangulationQuadrangle();
    void testTriangulationPentagon();
    void testTriangulationHexagon();
    void testTriangulationHeptagon();
    void testTriangulationSet();
    void testCalculateNormalsForVertices();
    //void testConcavePolygon();
};

#endif // GEOMETRYSTACKTESTS_H
