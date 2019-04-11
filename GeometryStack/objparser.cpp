#include "objparser.h"

bool ObjParser::fileImport(const QString &name, QVector<QVector3D> &vertices, QVector<QVector2D> &t_vertices,
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

    if (!parseObj(stream, vertices, t_vertices, face_v_indices, face_vt_indices, face_normal_indices, start_pointers, error))
    {
        error = "Cannot parse stream.\n";
        file.close();
        return false;
    }
    file.close();
    return true;
}

bool ObjParser::parseObj(QTextStream &stream, QVector<QVector3D> &vertices, QVector<QVector2D> &textureVertices,
                          QVector<int> &faceVertexIndices, QVector<int> &faceTextureIndices,
                          QVector<int> &faceNormalIndices, QVector<int> &startPointers, QString &error)
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
                if (!vertex3dFromStrings(content, vertex, error))
                    return false;
                vertices.push_back(vertex);
            }
            else if(content[0] == "vt")
            {
                QVector2D textureVertex;
                if (!vertex2dFromStrings(content, textureVertex, error))
                    return false;
                textureVertices.push_back(textureVertex);
            }
            else if (content[0] == "f")
            {
                const int verticesCount = vertices.size();
                const int textureVerticesCount = textureVertices.size();
                if (!faceIndicesFromString(content, faceVertexIndices, faceTextureIndices,
                                                faceNormalIndices, startPointers, verticesCount, textureVerticesCount, error))
                    return false;
            }
        }
    }
    startPointers.push_back(faceVertexIndices.size());
    return true;
}

bool ObjParser::faceIndicesFromString(
        const QStringList &content, QVector<int> &faceVertexIndices,
        QVector<int> &faceTextureIndices, QVector<int> &faceNormalIndices,
        QVector<int> &startPointers, const int verticesCount, const int textureVerticesCount, QString &error)
{
    const QChar faceDelim = '/';
    //bool with_texture = false;
    //bool with_normal = false;

    if (content.size() < 3)
    {
        error = "Polygon is too small.\n";
        return false;
    }

    for (int i = 1; i < content.size(); i++)
    {

        QStringList facePart = content[i].split(faceDelim);

        if (facePart.size() > 3)
        {
            error = "Something wrong with faces.\n";
            return false;
        }

        bool is_part0_ok = false;
        int vertexIndex = facePart[0].toInt(&is_part0_ok);
        if (!is_part0_ok || vertexIndex > verticesCount)
        {
            error = "Can not convert indices to int.\n";
            return false;
        }
        faceVertexIndices.push_back(vertexIndex);

        if (facePart.size() > 1 && !facePart[1].isEmpty())
        {
            bool is_part1_ok = false;
            int textureVertexIndex = facePart[1].toInt(&is_part1_ok);
            if (!is_part1_ok || textureVertexIndex > textureVerticesCount)
            {
                error = "Can not convert indices to int.\n";
                return false;
            }
            faceTextureIndices.push_back(textureVertexIndex);
            /*if (i == 1)
                with_texture = true;*/
        }

        if (facePart.size() > 2)
        {
            bool is_part2_ok = false;
            int normalVertexIndex = facePart[2].toInt(&is_part2_ok);
            if (!is_part2_ok)
            {
                error = "Can not convert indices to int.\n";
                return false;
            }
            faceNormalIndices.push_back(normalVertexIndex);
            /*if (i == 1)
                with_normal = true;*/
        }
    }
    startPointers.push_back(faceVertexIndices.size() - content.size() + 1);
    return true;

}


bool ObjParser::vertex3dFromStrings(const QStringList &content, QVector3D &vertex, QString &error)
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

bool ObjParser::vertex2dFromStrings(const QStringList &content, QVector2D &textureVertex, QString &error)
{
    if(content.size() > 4 || content.size() < 3 || (content.size() == 4 && !(qFuzzyCompare(content[3].toDouble(), 0))))
    {
        error = "Something else is in the file.\n";
        return false;
    }

    bool is_content1_ok = false;
    bool is_content2_ok = false;

    textureVertex = QVector2D(content[1].toDouble(&is_content1_ok), content[2].toDouble(&is_content2_ok));
    if (!is_content1_ok || !is_content2_ok)
    {
        error = "Can not convert to double.\n";
        return false;
    }
    return true;
}
