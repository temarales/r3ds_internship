#include "objparser.h"

bool ObjParser::file_import(const QString &name, QVector<QVector3D> &vertices, QVector<QVector2D> &t_vertices,
                            QVector<int> &face_v_indices, QVector<int> &face_vt_indices,
                            QVector<int> &face_normal_indices, QVector<int> &start_pointers,
                            QString &error)
{
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        error = "Cannot open input file.\n";
        file.close();
        return false;
    }

    QTextStream stream(&file);
    if(stream.status()!= QTextStream::Ok)
    {
        error =  "Cannot make text stream for file.\n";
        file.close();
        return false;
    }

    if (!parse_obj(stream, vertices, t_vertices, face_v_indices, face_vt_indices, face_normal_indices, start_pointers, error))
    {
        error = "Cannot parse stream.\n";
        file.close();
        return false;
    }
    file.close();
    return true;
}

bool ObjParser::parse_obj(QTextStream &stream, QVector<QVector3D> &vertices, QVector<QVector2D> &texture_vertices,
                          QVector<int> &face_vertex_indices, QVector<int> &face_texture_indices,
                          QVector<int> &face_normal_indices, QVector<int> &start_pointers, QString &error)
{
    const QChar delim = ' ';

    while (!stream.atEnd())
    {
        const QString line = stream.readLine();
        const QStringList content = line.split(delim, QString::SkipEmptyParts);
        if (content.size() != 0)
        {
            if (content[0] == "v")
            {
                QVector3D vertex;
                if (!vertex3D_from_strings(content, vertex, error))
                    return false;
                vertices.push_back(vertex);
            }
            else if(content[0] == "vt")
            {
                QVector2D t_vertex;
                if (!vertex2D_from_strings(content, t_vertex, error))
                    return false;
                texture_vertices.push_back(t_vertex);
            }
            else if (content[0] == "f")
            {
                const int vertices_count = vertices.size();
                const int texture_vertices_count = texture_vertices.size();
                if (!face_indices_from_string(content, face_vertex_indices, face_texture_indices,
                                                face_normal_indices, start_pointers, vertices_count, texture_vertices_count, error))
                    return false;
            }
        }
    }
    start_pointers.push_back(face_vertex_indices.size() - 1);
    return true;
}

bool ObjParser::face_indices_from_string(const QStringList &content, QVector<int> &face_vertex_indices,
                                           QVector<int> &face_texture_indices, QVector<int> &face_normal_indices,
                                           QVector<int> &start_pointers, const int vertices_count, const int texture_vertices_count, QString &error)
{
    const QChar face_delim = '/';
    //bool with_texture = false;
    //bool with_normal = false;

    for (int i = 1; i < content.size(); i++)
    {

        QStringList face_part = content[i].split(face_delim);

        if (face_part.size() > 3)
        {
            error = "Something wrong with faces.\n";
            return false;
        }

        bool is_part0_ok = false;
        int vertex_index = face_part[0].toInt(&is_part0_ok);
        if (!is_part0_ok || vertex_index > vertices_count)
        {
            error = "Can not convert indices to int.\n";
            return false;
        }
        face_vertex_indices.push_back(vertex_index);

        if (face_part.size() > 1 && !face_part[1].isEmpty())
        {
            bool is_part1_ok = false;
            int texture_vertex_index = face_part[1].toInt(&is_part1_ok);
            if (!is_part1_ok || texture_vertex_index > texture_vertices_count)
            {
                error = "Can not convert indices to int.\n";
                return false;
            }
            face_texture_indices.push_back(texture_vertex_index);
            /*if (i == 1)
                with_texture = true;*/
        }

        if (face_part.size() > 2)
        {
            bool is_part2_ok = false;
            int normal_vertex_index = face_part[2].toInt(&is_part2_ok);
            if (!is_part2_ok)
            {
                error = "Can not convert indices to int.\n";
                return false;
            }
            face_normal_indices.push_back(normal_vertex_index);
            /*if (i == 1)
                with_normal = true;*/
        }
    }
    start_pointers.push_back(face_vertex_indices.size() - content.size() + 1);
    return true;

}


bool ObjParser::vertex3D_from_strings(const QStringList &content, QVector3D &vertex, QString &error)
{
    if(content.size() != 4)
    {
        error = "Something else is in the file.\n";
        return false;
    }

    bool is_content1_ok = false;
    bool is_content2_ok = false;
    bool is_content3_ok = false;

    vertex = QVector3D(content[1].toDouble(&is_content1_ok), content[2].toDouble(&is_content2_ok), content[3].toDouble(&is_content3_ok));
    if (!is_content1_ok || !is_content2_ok || !is_content3_ok)
    {
        error = "Can not convert to double.\n";
        return false;
    }

    return true;
}

bool ObjParser::vertex2D_from_strings(const QStringList &content, QVector2D &t_vertex, QString &error)
{
    if(content.size() > 4 || content.size() < 3 || (content.size() == 4 && !(qFuzzyCompare(content[3].toDouble(), 0))))
    {
        error = "Something else is in the file.\n";
        return false;
    }

    bool is_content1_ok = false;
    bool is_content2_ok = false;

    t_vertex = QVector2D(content[1].toDouble(&is_content1_ok), content[2].toDouble(&is_content2_ok));
    if (!is_content1_ok || !is_content2_ok)
    {
        error = "Can not convert to double.\n";
        return false;
    }
    return true;
}
