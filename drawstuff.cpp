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
    QVector<QPointF> points_to_draw;
    for (int i = 0; i < scene_for_drawing.models.count(); i++)
    {
        const QVector<QPointF> points_of_model = Matrix_Oper::points_for_drawing(
                    Matrix_Oper::vertices_for_drawing(scene_for_drawing.models[i].vertices, camera,
                                                      screen_width, screen_height, 140, 0, 30));
        points_to_draw += points_of_model;
    }
    QPointF *array_points_to_draw = points_to_draw.data();
    painter.drawPoints(array_points_to_draw, points_to_draw.count());
}
