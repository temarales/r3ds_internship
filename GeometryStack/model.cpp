#include "model.h"

Model::Model()
{

}

Model::Model(QVector<QVector3D> inVertices, QVector<QVector2D> inTextureVertices,
             QVector<int> inFaceVertexIndices, QVector<int> inFaceTextureVertexIndices, QVector<int> inFaceNormalIndices,
             QVector<int> inStartPointers)
{
    vertices = inVertices;
    textureVertices = inTextureVertices;
    faceVertexIndices = inFaceVertexIndices;
    faceVertexTextureIndices = inFaceTextureVertexIndices;
    faceNormalIndices = inFaceNormalIndices;
    startPointers = inStartPointers;
}

Model Model::modelFromFile(const QString &filename)
{
    QString error = nullptr;
    QVector<QVector3D> new_vertices;
    QVector<QVector2D> new_texture_vertices;
    QVector<int> new_face_v_indices;
    QVector<int> new_face_vt_indices;
    QVector<int> new_face_normal_indices;
    QVector<int> new_start_pointers;

    ObjParser::fileImport(filename, new_vertices, new_texture_vertices, new_face_v_indices,
                           new_face_vt_indices, new_face_normal_indices, new_start_pointers, error);

    Model new_model(new_vertices, new_texture_vertices, new_face_v_indices,
                    new_face_vt_indices, new_face_normal_indices, new_start_pointers);
    return new_model;
}

void Model::triangulate()
{
    for(int i = 0; i < this->startPointers.count(); i++) {

    }
}


