#ifndef MATRIX_OPER_H
#define MATRIX_OPER_H
#include <QVector3D>
#include <QVector2D>
#include <QVector>

class Matrix_Oper
{
    public:
        Matrix_Oper();
        QVector<QVector2D> world_to_screen(QVector<QVector3D> &vertices, const int &xSize, const int &ySize, const int &dist);
};

#endif // MATRIX_OPER_H
