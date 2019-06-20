#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QVector3D>
#include <math.h>


class Camera //https://habr.com/ru/post/327604/
{
public:
    Camera(const QVector3D in_camera_position,
           const QVector3D in_camera_target,
           const QVector3D in_up_vector);
//    static Camera fromSomeThreeVectors();
    Camera();
    QMatrix4x4 view_matrix() const;


    QVector3D camera_position; // Позиция камеры в мировом пространстве
    QVector3D camera_target;   // Указывает куда вы смотрите в мировом пространстве
    QVector3D up_vector; // Вектор, определяющий ориентацию камеры

    void moveVertical(int value);
    void moveHorizontal(int value);
    void changeCameraPositionOn(QVector3D shift);
    void moveCloserOrFurther(int value);
    void RotateView(float angle, float x, float y, float z);

    float xPosition() const;
    float yPosition() const;
    float zPosition() const;

//    //Getter
//    QVector3D xVector() const;
//    //Setter
//    void setXVector(const QVector3D &newXvector);
//private:
//    //Field
//    QVector3D m_xVector;
};

#endif // CAMERA_H
