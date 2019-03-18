#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>


class Camera //https://habr.com/ru/post/327604/
{
public:
    Camera(const QVector3D in_camera_position, const QVector3D in_camera_target,
           const QVector3D in_up_vector);
    Camera();
    QVector3D camera_position; // Позиция камеры в мировом пространстве
    QVector3D camera_target;   // Указывает куда вы смотрите в мировом пространстве
    QVector3D up_vector; // Вектор, определяющий ориентацию камеры

    QVector3D x_vector;
    QVector3D y_vector;
    QVector3D z_vector;
};

#endif // CAMERA_H
