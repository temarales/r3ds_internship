#include "camera.h"

Camera::Camera(const QVector3D in_camera_position, const QVector3D in_camera_target,
               const QVector3D in_up_vector)
{
    camera_position = in_camera_position;
    camera_target = in_camera_target;
    up_vector = in_up_vector;
}

Camera::Camera()
{

}

QMatrix4x4 Camera::view_matrix() const
{
    QMatrix4x4 view_m;
    view_m.lookAt(camera_target, camera_position, up_vector);
    return view_m;
}

void Camera::changeCameraPositionOn(QVector3D shift)
{
    camera_position += shift;
}

void Camera::moveVertical(int value)
{
    camera_position.setY(camera_position.y() + value);
}

void Camera::moveHorizontal(int value)
{
    camera_position.setX(camera_position.x() + value);
}

void Camera::moveCloserOrFurther(int value)
{
    camera_position.setZ(camera_position.z() + value);
}
