#include "matrix_oper.h"

Matrix_Oper::Matrix_Oper()
{
}

QVector<QVector2D> Matrix_Oper::world_to_screen(QVector<QVector3D> &vertices, const int &xSize, const int &ySize, const int &dist)
{
    QVector<QVector2D> screen_vertices;
    for (QVector3D vertex : vertices)
    {
        QVector2D screen_vertex = QVector2D((xSize/2+vertex.x()*dist/(vertex.z()+dist)),
                                            (ySize/2-vertex.y()*dist/(vertex.z()+dist)));
        screen_vertices.push_back(screen_vertex);
    }
    return screen_vertices;
}

QVector<QVector4D> Matrix_Oper::project_vertices_to_4d(const QVector<QVector3D> &vertices)
{
    QVector<QVector4D> homogeneous_vertices;
    for (int i = 0; i < vertices.size(); i++)
    {
        QVector4D homogeneous_vertex(vertices[i], 1);
        homogeneous_vertices.push_back(homogeneous_vertex);
    }
    return homogeneous_vertices;
}

QVector<QVector3D> Matrix_Oper::retro_project_vertices_to3d(const float c, const QVector<QVector4D> &vertices4d)
{
    QVector<QVector3D> vertices3d; //https://github.com/ssloy/tinyrenderer/wiki/Lesson-4:-Perspective-projection
    for (int i = 0; i < vertices4d.size(); i++)
    {
        QVector3D vertex3d(vertices4d[i].x()/(1-vertices4d[i].z()/c),
                           vertices4d[i].y()/(1-vertices4d[i].z()/c),
                           vertices4d[i].z()/(1-vertices4d[i].z()/c));
        vertices3d.push_back(vertex3d);
    }
    return vertices3d;
}

QMatrix4x4 Matrix_Oper::identity_matrix()
{
    QMatrix4x4 identity(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    return identity;
}

QMatrix4x4 Matrix_Oper::view_matrix(const Camera camera)
{
    QMatrix4x4 basis_matrix(camera.x_vector.x(), camera.x_vector.y(), camera.x_vector.z(), 0, //https://habr.com/ru/post/327604/
                    camera.y_vector.x(), camera.y_vector.y(), camera.y_vector.z(), 0,
                    camera.z_vector.x(), camera.z_vector.y(), camera.z_vector.z(), 0,
                    0, 0, 0, 1);
    QMatrix4x4 transference_matrix(1, 0, 0, camera.camera_position.x(),
                                0, 1, 0, camera.camera_position.y(),
                                0, 0, 1, camera.camera_position.z(),
                                0, 0, 0, 1);
    QMatrix4x4 view = basis_matrix * transference_matrix;
    return view;
}

QMatrix4x4 Matrix_Oper::create_model_view_projection_matrix()
{
    QMatrix4x4 mvp_matrix; //= projection_matrix * view_matrix() * model_matrix();
    return mvp_matrix;
}




