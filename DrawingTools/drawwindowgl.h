#ifndef DRAWWINDOWGL_H
#define DRAWWINDOWGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <GL/gl.h>
#include <GL/glu.h>
#include "scene.h"


class DrawWindowGL : public QOpenGLWidget
{
public:
    DrawWindowGL(QWidget *parent, Scene *newScene, Camera *newCamera);
    ~DrawWindowGL();
    void initializeGL() override;
    void resizeGL(int nWidth, int nHeight) override;
    void paintGL() override;
    void repaint();

private:
    Scene *scene;
    Camera *camera;
};

#endif // DRAWWINDOWGL_H
