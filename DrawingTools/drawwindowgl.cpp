#include "drawwindowgl.h"
#include "matrix_oper.h"

DrawWindowGL::DrawWindowGL(QWidget *parent, Scene *newScene, Camera *newCamera)
    : QOpenGLWidget(parent)
{
    scene = newScene;
    camera = newCamera;
}

DrawWindowGL::~DrawWindowGL()
{

}

void DrawWindowGL::initializeGL()
{
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

}

void DrawWindowGL::resizeGL(int nWidth, int nHeight)
{
    glViewport(0,0,nWidth,nHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)nWidth/nHeight, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(10, 1.0, 0.0, 0.0);
    //gluLookAt(40,40,10,0,0,0,0,1,0);
    gluLookAt(camera->xPosition(), camera->yPosition(), camera->zPosition(), 0, 0, 0, 0, 1, 0);
}

void DrawWindowGL::paintGL()
{
    GLfloat light_position[] = { 7.0, 7.0, 7.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene->draw(this);
    //scene->drawTriangledGrid(this);
    glDisable(GL_LIGHT0);
}

/*void DrawWindowGL::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_W)
        camera->moveCloserOrFurther(-2);
    if(ev->key() == Qt::Key_S)
        camera->moveCloserOrFurther(2);
    if(ev->key() == Qt::Key_D)
        camera->moveHorizontal(2);
    if (ev->key() == Qt::Key_A)
        camera->moveHorizontal(-2);
    repaint();
}*/

void DrawWindowGL::repaint()
{
    //gluLookAt(camera->xPosition(), camera->yPosition(), camera->zPosition(), 0, 0, 0, 0, 1, 0);
    //scene->draw(this);
}
