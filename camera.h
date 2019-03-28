#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>


class Camera //https://habr.com/ru/post/327604/
{
public:
    Camera(const QVector3D in_camera_position,
           const QVector3D in_camera_target,
           const QVector3D in_up_vector);
//    static Camera fromSomeThreeVectors();
    Camera();
    QMatrix4x4 view_matrix();


    QVector3D camera_position; // Позиция камеры в мировом пространстве
    QVector3D camera_target;   // Указывает куда вы смотрите в мировом пространстве
    QVector3D up_vector; // Вектор, определяющий ориентацию камеры

    /*QVector3D x_vector;
    QVector3D y_vector;
    QVector3D z_vector;*/

//    //Getter
//    QVector3D xVector() const;
//    //Setter
//    void setXVector(const QVector3D &newXvector);
//private:
//    //Field
//    QVector3D m_xVector;
};

#endif // CAMERA_H
