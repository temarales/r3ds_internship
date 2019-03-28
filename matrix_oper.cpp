#include "matrix_oper.h"


QVector<QVector2D> Matrix_Oper::vertices_for_drawing(
        const QVector<QVector3D> &vertices, Camera &camera, const int &width, const int &height,
        const qreal angle, const qreal nearPlane, const qreal farPlane)
{
    QVector<QVector4D> vertices_4d = project_vertices_to_4d(vertices);
    transform_vertices(vertices_4d, create_model_view_projection_matrix(camera, angle, 1, nearPlane, farPlane));
    QVector<QVector3D> new_vertices = retro_project_vertices_to3d(vertices_4d);
    QVector<QVector2D> draw = world_to_screen(new_vertices, width, height);
    return draw;
}

QVector<QPointF> Matrix_Oper::points_for_drawing(const QVector<QVector2D> &vertices)
{
    QVector<QPointF> points;
    points.reserve(vertices.size());
    for (const QVector2D &vertex : vertices)
    {
        const QPointF point = vertex.toPointF();
        points.append(point);
    }
    return points;
}

void Matrix_Oper::transform_vertices(QVector<QVector4D> &vertices, const QMatrix4x4 mvp)
{
    for (int i = 0; i < vertices.length(); i++)
        vertices[i] = mvp * vertices[i];
}

QVector<QVector2D> Matrix_Oper::world_to_screen(const QVector<QVector3D> &vertices, const int &width, const int &height)
{
    QVector<QVector2D> screen_vertices;
    screen_vertices.reserve(vertices.size());
    for (const QVector3D &vertex : vertices)
    {
        const QVector2D screen_vertex = QVector2D((vertex.x() + 1) / 2 * width,
                                                  (1 - (vertex.y()+ 1) / 2) * height);
        screen_vertices.push_back(screen_vertex);
    }
    return screen_vertices;
}

QVector<QVector4D> Matrix_Oper::project_vertices_to_4d(const QVector<QVector3D> &vertices)
{
    QVector<QVector4D> homogeneous_vertices;
    homogeneous_vertices.reserve(vertices.size());
    for (const QVector3D &vertex : vertices)
    {
        QVector4D homogeneous_vertex(vertex, 1);
        homogeneous_vertices.push_back(homogeneous_vertex);
    }
    return homogeneous_vertices;
}

QVector<QVector3D> Matrix_Oper::retro_project_vertices_to3d(const QVector<QVector4D> &vertices4d)
{
    QVector<QVector3D> vertices3d; //https://github.com/ssloy/tinyrenderer/wiki/Lesson-4:-Perspective-projection
    vertices3d.reserve(vertices4d.size());
    for (int i = 0; i < vertices4d.size(); i++)
    {
        const QVector3D vertex3d(vertices4d[i].x()/vertices4d[i].w(),
                                 vertices4d[i].y()/vertices4d[i].w(),
                                 vertices4d[i].z()/vertices4d[i].w());
        vertices3d.push_back(vertex3d);
    }
    return vertices3d;
}

QMatrix4x4 Matrix_Oper::frustum_matrix(const qreal left, const qreal right, const qreal bottom, const qreal top, const qreal nearPlane, const qreal farPlane)
{
    QMatrix4x4 frustum_m;
    frustum_m.frustum(left, right, bottom, top, nearPlane, farPlane);
    return frustum_m;
}

QMatrix4x4 Matrix_Oper::perspective_matrix(const qreal angle, const qreal aspect, const qreal nearPlane, const qreal farPlane)
{
    QMatrix4x4 perspective_m;
    perspective_m.perspective(angle, aspect, nearPlane, farPlane);
    return perspective_m;
}

QMatrix4x4 Matrix_Oper::create_model_view_projection_matrix(Camera &camera, const qreal angle, const qreal aspect, const qreal nearPlane, const qreal farPlane)
{
    QMatrix4x4 model_m;
    model_m.translate(QVector3D(3, 3, 3));
    //const QMatrix4x4 mvp_matrix = perspective_matrix(angle, aspect, nearPlane, farPlane)*camera.view_matrix(); //= projection_matrix * view_matrix() * model_matrix();
    const QMatrix4x4 mvp_matrix = frustum_matrix(-2, 2, -2, 2, -2, 2) * camera.view_matrix()*model_m;
    return mvp_matrix;
}




