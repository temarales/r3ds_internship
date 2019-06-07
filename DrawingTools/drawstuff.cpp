#include "drawstuff.h"

DrawStuff::DrawStuff()
{
}

DrawStuff::DrawStuff(
        const Camera &inCamera, const Scene &inSceneForDrawing,
        const int inScreenWidth, const int inScreenHeight)
{
    camera = inCamera;
    sceneForDrawing = inSceneForDrawing;
    screenHeight = inScreenHeight;
    screenWidth = inScreenWidth;
}

void DrawStuff::drawAll(QPainter &painter)
{
    for (int i = 0; i < sceneForDrawing.models.count(); i++)
        drawTriangulatedModel(painter, sceneForDrawing.models[i]);
        //drawModel(painter, sceneForDrawing.models[i]);

}

void DrawStuff::drawModel(QPainter &painter, const Model &model)
{
    QVector<QPointF> pointsToDraw = Matrix_Oper::pointsForDrawing(
                Matrix_Oper::verticesForDrawing(model.vertices, camera,
                                                  screenWidth, screenHeight, 90, 0, 1));
    QPointF *arrayPointsToDraw = pointsToDraw.data();
    painter.drawPoints(arrayPointsToDraw, pointsToDraw.count());

    for(int polygonIndex = 0; polygonIndex < model.startPolygonOffsets.count() - 1; polygonIndex++) {
        for (int vertexInPolygonIndex = model.startPolygonOffsets[polygonIndex]; vertexInPolygonIndex < model.startPolygonOffsets[polygonIndex+1]; vertexInPolygonIndex++) {
            if(vertexInPolygonIndex == model.startPolygonOffsets[polygonIndex+1] - 1) {
                const QLineF lineToDraw = QLineF(arrayPointsToDraw[model.faceVertexIndices[vertexInPolygonIndex] - 1],
                        arrayPointsToDraw[model.faceVertexIndices[model.startPolygonOffsets[polygonIndex]] - 1]);
                painter.drawLine(lineToDraw);
            }
            else {
                const QLineF lineToDraw  = QLineF(arrayPointsToDraw[model.faceVertexIndices[vertexInPolygonIndex] - 1],
                        arrayPointsToDraw[model.faceVertexIndices[vertexInPolygonIndex+1] - 1]);
                painter.drawLine(lineToDraw);
            }
        }
    }
}

void DrawStuff::drawTriangulatedModel(QPainter &painter, const Model &model)
{
    QVector<QPointF> pointsToDraw = Matrix_Oper::pointsForDrawing(
                Matrix_Oper::verticesForDrawing(model.vertices, camera,
                                                  screenWidth, screenHeight, 90, 0, 1));
    QPointF *arrayPointsToDraw = pointsToDraw.data();
    painter.drawPoints(arrayPointsToDraw, pointsToDraw.count());

    for(int polygonIndex = 0; polygonIndex < model.triangledFaceVertexIndices.count(); polygonIndex += 3) {
        QLineF lineToDraw = QLineF(arrayPointsToDraw[model.triangledFaceVertexIndices[polygonIndex] - 1],
                arrayPointsToDraw[model.triangledFaceVertexIndices[polygonIndex + 1] - 1]);
        painter.drawLine(lineToDraw);
        lineToDraw = QLineF(arrayPointsToDraw[model.triangledFaceVertexIndices[polygonIndex + 1] - 1],
                arrayPointsToDraw[model.triangledFaceVertexIndices[polygonIndex + 2] - 1]);
        painter.drawLine(lineToDraw);
        lineToDraw = QLineF(arrayPointsToDraw[model.triangledFaceVertexIndices[polygonIndex] - 1],
                arrayPointsToDraw[model.triangledFaceVertexIndices[polygonIndex + 2] - 1]);
        painter.drawLine(lineToDraw);
        }

}
