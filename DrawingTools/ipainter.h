#ifndef IPAINTER_H
#define IPAINTER_H

#include <QOpenGLWidget>


class IPainter
{
public:
    IPainter();
    virtual void draw(QOpenGLWidget* widget) = 0;
    virtual void drawOriginalGrid(QOpenGLWidget* widget) = 0;
    virtual void drawTriangledGrid(QOpenGLWidget* widget) = 0;
};

#endif // IPAINTER_H
