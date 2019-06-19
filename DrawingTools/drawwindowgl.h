#ifndef DRAWWINDOWGL_H
#define DRAWWINDOWGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <GL/gl.h>
#include <GL/glu.h>
#include "scene.h"
#include <QColor>


class DrawWindowGL : public QOpenGLWidget
{
public:
    DrawWindowGL(QWidget *parent, Scene *newScene, Camera *newCamera);
    ~DrawWindowGL();
    void initializeGL() override;
    void resizeGL(int nWidth, int nHeight) override;
    void paintGL() override;
    void repaint();

    void setBackgroundcolor(const QColor &backgroundcolor);

private:
    Scene *scene;
    Camera *camera;
    QColor m_backgroundcolor;
};

#endif // DRAWWINDOWGL_H
