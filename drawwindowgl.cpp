#include "drawwindowgl.h"
#include "matrix_oper.h"

DrawWindowGL::DrawWindowGL(QWidget *parent, Scene *newScene, Camera *newCamera)
    : QOpenGLWidget(parent)
{
    scene = *newScene;
    camera = *newCamera;
}

DrawWindowGL::~DrawWindowGL()
{
    //delete ui;
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
    //glViewport(0,0,nWidth,nHeight);
    //glMatrixMode(GL_PROJECTION);
    //glLoadMatrixd(Matrix_Oper::createModelViewProjectionMatrix(camera, nWidth, nHeight, 0, 1));

    glViewport(0,0,nWidth,nHeight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, (float)nWidth/nHeight, 0.01, 100.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(10, 1.0, 0.0, 0.0 );
        gluLookAt(3,3,7,0,0,0,0,1,0);
}

void DrawWindowGL::paintGL()
{
    //GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    //GLfloat mat_shininess[] = { 30.0 };
    GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);

    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        /*glBegin(GL_TRIANGLES);
         glColor3f(1.0, 0.0, 0.0);
         glVertex3f(-0.5, -0.5, 0);
         glColor3f(0.0, 1.0, 0.0);
         glVertex3f(0.5, -0.5, 0);
         glColor3f(0.0, 0.0, 1.0);
         glVertex3f(0.0, 0.5, 0);
        glEnd();*/

       scene.draw(this);
       glDisable(GL_LIGHT0);
}
