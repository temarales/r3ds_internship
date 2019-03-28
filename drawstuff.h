#ifndef DRAWSTUFF_H
#define DRAWSTUFF_H
#include "scene.h"
#include "matrix_oper.h"

#include <QMainWindow>
#include <QPushButton>
#include <QtGui>
#include <QPointF>


class DrawStuff
{
public:
    DrawStuff();
    DrawStuff(const Camera &in_camera, const Scene &in_scene_for_drawing, const int in_width, const int in_height);

    Scene scene_for_drawing;
    Camera camera;
    int screen_width;
    int screen_height;

    void draw_all(QPainter &painter);

};

#endif // DRAWSTUFF_H
