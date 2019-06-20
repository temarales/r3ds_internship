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
    view_m.lookAt(camera_position, camera_target, up_vector);
    return view_m;
}


void Camera::RotateView(float angle, float x, float y, float z) //rotate round y
{
    QMatrix3x3 m;

    QVector3D vNewView = QVector3D(0,0,0);
    QVector3D vectorView(this->camera_position.x() - this->camera_target.x(),
                   this->camera_position.y() - this->camera_target.y(),
                   this->camera_position.z() - this->camera_target.z());

    float cosTheta = (float)cos(angle*M_PI/180);
    float sinTheta = (float)sin(angle*M_PI/180);
    vNewView.setX(vectorView.x()*cosTheta - vectorView.z()*sinTheta);
    vNewView.setZ(vectorView.x()*sinTheta + vectorView.z()*cosTheta);

    camera_position.setX(vNewView.x() + camera_target.x());
    camera_position.setZ(vNewView.z() + camera_target.z());
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

float Camera::xPosition() const
{
    return camera_position.x();
}

float Camera::yPosition() const
{
    return camera_position.y();
}

float Camera::zPosition() const
{
    return camera_position.z();
}
