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
    DrawStuff(
            const Camera &inCamera, const Scene &inSceneForDrawing,
            const int inScreenWidth, const int inScreenHeight);

    Scene sceneForDrawing;
    Camera camera;
    int screenWidth;
    int screenHeight;

    void drawAll(QPainter &painter);
    void drawModel(QPainter &painter, const Model &model);

};

#endif // DRAWSTUFF_H
