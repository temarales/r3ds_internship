#include "matrix_oper.h"

Matrix_Oper::Matrix_Oper()
{

}

QVector<QVector2D>* world_to_screen(QVector<QVector3D> &vertices, const int &xSize, const int &ySize, const int &dist)
{
    QVector<QVector2D> *screen_vertices = new QVector<QVector2D>();
    QVector2D screen_vertex;
    for (QVector3D vertex : vertices)
    {
        screen_vertex = QVector2D((xSize/2+vertex.x()*dist/(vertex.z()+dist)), (ySize/2-vertex.y()*dist/(vertex.z()+dist)));
        screen_vertices->push_back(screen_vertex);
    }

    return screen_vertices;
}
