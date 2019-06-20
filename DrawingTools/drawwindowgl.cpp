#include "drawwindowgl.h"
#include "matrix_oper.h"

DrawWindowGL::DrawWindowGL(QWidget *parent, Scene *newScene, Camera *newCamera)
    : QOpenGLWidget(parent)
{
    scene = newScene;
    camera = newCamera;
    m_backgroundcolor = Qt::red;
}

DrawWindowGL::~DrawWindowGL()
{

}


void DrawWindowGL::initializeGL()
{
    glClearColor(m_backgroundcolor.redF(),m_backgroundcolor.greenF(), m_backgroundcolor.blueF(),1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_position[] = { 7.0, 7.0, 7.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void DrawWindowGL::resizeGL(int nWidth, int nHeight)
{
    glViewport(0,0,nWidth,nHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)nWidth/nHeight, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DrawWindowGL::paintGL()
{
    QMatrix4x4 translate;
    QMatrix4x4 rotate;
    QMatrix4x4 modelViewM;
    translate.translate(0, 0, -50);
    rotate.rotate(90, 0, 1, 0);
    modelViewM = translate * rotate;
    glClearColor(m_backgroundcolor.redF(),m_backgroundcolor.greenF(), m_backgroundcolor.blueF(),1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glMultMatrixf(modelViewM.constData());
    glMultMatrixf(camera->view_matrix().constData());
    scene->draw(this);

}

void DrawWindowGL::setBackgroundcolor(const QColor &backgroundcolor)
{
    m_backgroundcolor = backgroundcolor;
}
