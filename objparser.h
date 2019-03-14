#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <QVector>
#include <QVector4D>
#include <QVector3D>
#include <QVector2D>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <fstream>

using namespace std;

namespace ObjParser
{
        bool vertex2D_from_strings(const QStringList &content, QVector2D &vertex, QString &error);

        bool vertex3D_from_strings(const QStringList &content, QVector3D &vertex, QString &error);

        bool parse_obj(QTextStream &stream, QVector<QVector3D> &vertices, QVector<QVector2D> &texture_vertices,
                                  QVector<int> &face_vertex_indices, QVector<int> &face_texture_indices,
                                  QVector<int> &face_normal_indices, QVector<int> &start_pointers, QString &error);

        bool file_import(const QString &name, QVector<QVector3D> &vertices, QVector<QVector2D> &t_vertices,
                                    QVector<int> &face_v_indices, QVector<int> &face_vt_indices,
                                    QVector<int> &face_normal_indices, QVector<int> &start_pointers, QString &error);

        bool face_indices_from_string(const QStringList &content, QVector<int> &face_vertex_indices,
                                        QVector<int> &face_texture_indices, QVector<int> &face_normal_indices,
                                        QVector<int> &start_pointers, const int vertices_count,
                                      const int texture_vertices_count, QString &error);

}

#endif // OBJPARSER_H
