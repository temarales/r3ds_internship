#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>

namespace ObjParser{
    bool vertex2dFromStrings(const QStringList &content, QVector2D &vertex, QString &error);
    bool vertex3dFromStrings(const QStringList &content, QVector3D &vertex, QString &error);
    bool parseObj(
            QTextStream &stream, QVector<QVector3D> &vertices, QVector<QVector2D> &textureVertices,
            QVector<int> &faceVertexIndices, QVector<int> &faceTextureIndices,
            QVector<int> &faceNormalIndices, QVector<int> &startPointers, QString &error);

    bool fileImport(
            const QString &name, QVector<QVector3D> &vertices, QVector<QVector2D> &t_vertices,
            QVector<int> &face_v_indices, QVector<int> &face_vt_indices,
            QVector<int> &face_normal_indices, QVector<int> &start_pointers, QString &error);

    bool faceIndicesFromString(
            const QStringList &content, QVector<int> &faceVertexIndices, QVector<int> &faceTextureIndices,
            QVector<int> &faceNormalIndices, QVector<int> &startPointers, const int verticesCount,
            const int textureVerticesCount, QString &error);
}

#endif // OBJPARSER_H
