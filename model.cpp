#include "model.h"

Model::Model()
{

}

Model::Model(QVector<QVector3D> in_vertices, QVector<QVector2D> in_texture_vertices,
             QVector<int> in_face_v_indices, QVector<int> in_face_vt_indices, QVector<int> in_face_normal_indices,
             QVector<int> in_start_pointers)
{
    vertices = in_vertices;
    texture_vertices = in_texture_vertices;
    face_v_indices = in_face_v_indices;
    face_vt_indices = in_face_vt_indices;
    face_normal_indices = in_face_normal_indices;
    start_pointers = in_start_pointers;
}

Model Model::model_from_file(const QString &filename)
{
    QString error = nullptr;
    QVector<QVector3D> new_vertices;
    QVector<QVector2D> new_texture_vertices;
    QVector<int> new_face_v_indices;
    QVector<int> new_face_vt_indices;
    QVector<int> new_face_normal_indices;
    QVector<int> new_start_pointers;

    ObjParser::file_import(filename, new_vertices, new_texture_vertices, new_face_v_indices,
                           new_face_vt_indices, new_face_normal_indices, new_start_pointers, error);

    Model new_model(new_vertices, new_texture_vertices, new_face_v_indices,
                    new_face_vt_indices, new_face_normal_indices, new_start_pointers);
    return new_model;
}
