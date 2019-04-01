#include "drawstuff.h"

DrawStuff::DrawStuff()
{
}

DrawStuff::DrawStuff(const Camera &in_camera, const Scene &in_scene_for_drawing, const int in_width, const int in_height)
{
    camera = in_camera;
    scene_for_drawing = in_scene_for_drawing;
    screen_height = in_height;
    screen_width = in_width;
}

void DrawStuff::draw_all(QPainter &painter)
{
    for (int i = 0; i < scene_for_drawing.models.count(); i++)
        drawModel(painter, scene_for_drawing.models[i]);
    /*QVector<QPointF> points_to_draw;
    for (int i = 0; i < scene_for_drawing.models.count(); i++)
    {
        const QVector<QPointF> points_of_model = Matrix_Oper::points_for_drawing(
                    Matrix_Oper::vertices_for_drawing(scene_for_drawing.models[i].vertices, camera,
                                                      screen_width, screen_height, 140, 0, 30));
        points_to_draw += points_of_model;
    }
    QPointF *array_points_to_draw = points_to_draw.data();
    painter.drawPoints(array_points_to_draw, points_to_draw.count());*/

    /*for (int i = 0; i < scene_for_drawing.models.count(); i++)
        for (int j = 0; j < scene_for_drawing.models[i].start_pointers.count(); j++)
        {

        }*/

}

void DrawStuff::drawModel(QPainter &painter, const Model &model)
{
    QVector<QPointF> pointsToDraw = Matrix_Oper::points_for_drawing(
                Matrix_Oper::vertices_for_drawing(model.vertices, camera,
                                                  screen_width, screen_height, 140, 0, 30));
    QPointF *arrayPointsToDraw = pointsToDraw.data();
    painter.drawPoints(arrayPointsToDraw, pointsToDraw.count());

    for(int polygonIndex = 0; polygonIndex < model.start_pointers.count() - 1; polygonIndex++)
    {
        const int count = model.start_pointers[polygonIndex+1] - model.start_pointers[polygonIndex];
        //QPointF polygon[count];
        //std::copy(arrayPointsToDraw + model.start_pointers[i], arrayPointsToDraw + model.start_pointers[i+1], polygon);

        //painter.drawPolygon(polygon, count);
        for (int vertexInPolygonIndex = model.start_pointers[polygonIndex]; vertexInPolygonIndex < model.start_pointers[polygonIndex+1]; vertexInPolygonIndex++)
        {

            if(vertexInPolygonIndex == model.start_pointers[polygonIndex+1] - 1)
                painter.drawLine(QLineF(arrayPointsToDraw[model.face_v_indices[vertexInPolygonIndex] - 1],
                                 arrayPointsToDraw[model.face_v_indices[model.start_pointers[polygonIndex]] - 1]));
            else
                painter.drawLine(QLineF(arrayPointsToDraw[model.face_v_indices[vertexInPolygonIndex] - 1],
                                 arrayPointsToDraw[model.face_v_indices[vertexInPolygonIndex+1] - 1]));
        }
    }
}
