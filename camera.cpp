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
