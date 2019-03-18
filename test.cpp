#include "test.h"
#include "objparser.h"
#include <QDateTime>

Test::Test(QObject *parent) : QObject(parent)
{

}

bool Test::vector2d_qFuzzyCompare(const QVector2D a, const QVector2D b)
{
    for (int i = 0; i < 2; i++)
        if (!qFuzzyCompare(a[i], b[i]))
            return false;
    return true;
}

bool Test::vector3d_qFuzzyCompare(const QVector3D a, const QVector3D b)
{
    for (int i = 0; i < 3; i++)
        if (!qFuzzyCompare(a[i], b[i]))
            return false;
    return true;
}

void Test::test_vertex3D_from_strings()
{
    QVector3D vertex;
    QString error = NULL;

    QVERIFY(!ObjParser::vertex3D_from_strings({"v", "1", "2"}, vertex, error));
    QVERIFY(!ObjParser::vertex3D_from_strings({"v", "1", "2", "3", "4"}, vertex, error));
    QVERIFY(!ObjParser::vertex3D_from_strings({"v", "1", " ", "3", "4"}, vertex, error));
    QVERIFY(!ObjParser::vertex3D_from_strings({"v", "h", "2", "g", "df"}, vertex, error));
    QVERIFY(ObjParser::vertex3D_from_strings({"v", "1", "2", "3e-1"}, vertex, error));
    QVERIFY(vector3d_qFuzzyCompare(vertex, QVector3D(1, 2, 0.3)));
}

void Test::test_vertex2D_from_strings()
{
    QVector2D vertex;
    QString error = NULL;

    QVERIFY(!ObjParser::vertex2D_from_strings({"v", "1", "2", "3"}, vertex, error));
    QVERIFY(!ObjParser::vertex2D_from_strings({"v", "1", " ", "3", "4"}, vertex, error));
    QVERIFY(!ObjParser::vertex2D_from_strings({"v", "h", "2", "g", "df"}, vertex, error));
    QVERIFY(ObjParser::vertex2D_from_strings({"v", "1", "2"}, vertex, error));
    QVERIFY(ObjParser::vertex2D_from_strings({"v", "3.0958", "1.5479"}, vertex, error));
    QVERIFY(vector2d_qFuzzyCompare(vertex, QVector2D(3.0958, 1.5479)));
}



void Test::test_face_indices_from_string()
{
    QVector<int> v_index;
    QVector<int> vt_index;
    QVector<int> vn_index;
    QVector<int> start_pointers;
    QString error = NULL;
    const int vertices_count = 5;

    QVector<int> example1 = {1,2,3};
    QVector<int> example2 = {1,2,3,4,5};

    QVERIFY(ObjParser::face_indices_from_string({"f", "1/1", "2/ 2", "3/3"}, v_index, vt_index, vn_index,
                                                start_pointers, vertices_count, vertices_count, error));
    QCOMPARE(v_index, example1);
    QCOMPARE(vt_index, example1);
    v_index.clear();
    vt_index.clear();
    vn_index.clear();
    start_pointers.clear();

    QVERIFY(ObjParser::face_indices_from_string({"f", "1/1", "2/2", "3/3"}, v_index, vt_index, vn_index,
                                                start_pointers, vertices_count, vertices_count, error));
    QCOMPARE(v_index, example1);
    QCOMPARE(vt_index, example1);
    v_index.clear();
    vt_index.clear();
    vn_index.clear();
    start_pointers.clear();

    QVERIFY(ObjParser::face_indices_from_string({"f", "1/1", "2/2", "3/3", "4/4", "5/5"}, v_index, vt_index,
                                                vn_index, start_pointers, vertices_count, vertices_count,  error));
    QCOMPARE(v_index, example2);
    QCOMPARE(vt_index, example2);
    v_index.clear();
    vt_index.clear();
    vn_index.clear();
    start_pointers.clear();

    QVERIFY(ObjParser::face_indices_from_string({"f", "1/1/1", "2/2/2", "3/3/3", "4/4/4", "5/5/5"}, v_index, vt_index, vn_index,
                                                start_pointers, vertices_count, vertices_count,  error));
    QCOMPARE(v_index, example2);
    QCOMPARE(vt_index, example2);
    QCOMPARE(vn_index, example2);
    v_index.clear();
    vt_index.clear();
    vn_index.clear();
    start_pointers.clear();

    QVERIFY(ObjParser::face_indices_from_string({"f", "1//1", "2//2", "3//3"}, v_index, vt_index, vn_index,
                                                start_pointers, vertices_count, vertices_count, error));
    QCOMPARE(v_index, example1);
    QCOMPARE(vn_index, example1);
    v_index.clear();
    vt_index.clear();
    vn_index.clear();
    start_pointers.clear();
}

void Test::test_parse_obj()
{
    QVector<QVector3D> vertices;
    QVector<QVector2D> t_vertices;
    QVector<int> face_vertices;
    QVector<int> face_t_vertices;
    QVector<int> face_n_vertices;
    QVector<int> start_pointers;

    QVector<QVector3D>vertices_right= {QVector3D(-1, -1, -1), QVector3D(-1, 0, -1), QVector3D(0, 0, -1), QVector3D(0, -1, -1)};
    QVector<QVector2D> t_vertices_right= {QVector2D(3.0958, 0), QVector2D(3.0958, 1.5479), QVector2D(1.5479, 1.5479), QVector2D(1.5479, 0)};
    QVector<int> face_vertices_right = {1, 2, 3, 4, 4, 3, 1, 3};
    QVector<int> face_t_vertices_right = {1, 2, 3, 4, 4, 3, 2, 2};
    QVector<int> start_pointers_right = {0, 4, 7};

    QString error = nullptr;
    QFile file("ShowModel/r3ds/test.obj");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);

    QVERIFY(ObjParser::parse_obj(stream, vertices, t_vertices, face_vertices, face_t_vertices,
                                 face_n_vertices, start_pointers, error));
    QCOMPARE(vertices, vertices_right);
    QCOMPARE(t_vertices, t_vertices_right);
    QCOMPARE(face_vertices, face_vertices_right);
    QCOMPARE(start_pointers, start_pointers_right);
    QCOMPARE(face_n_vertices.size(), 0);

}

void Test::test3_parse_obj()
{
    QVector<QVector3D> vertices;
    QVector<QVector2D> t_vertices;
    QVector<int> face_vertices;
    QVector<int> face_t_vertices;
    QVector<int> face_n_vertices;
    QVector<int> start_pointers;

    QVector<QVector3D>vertices_right= {QVector3D(-1, -1, -1), QVector3D(-1, 0, -1), QVector3D(0, 0, -1), QVector3D(0, -1, -1)};
    QVector<QVector2D> t_vertices_right= {QVector2D(3.0958, 0), QVector2D(3.0958, 1.5479), QVector2D(1.5479, 1.5479), QVector2D(1.5479, 0)};
    QVector<int> face_vertices_right = {1, 2, 3, 4, 4, 3, 1, 3};
    QVector<int> face_n_vertices_right = {1, 2, 3, 4, 1, 2, 3, 3};
    QVector<int> start_pointers_right = {0, 4, 7};

    QString error = nullptr;
    QFile file("ShowModel/r3ds/test3.obj");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);

    QVERIFY(ObjParser::parse_obj(stream, vertices, t_vertices, face_vertices, face_t_vertices,
                                 face_n_vertices, start_pointers, error));
    QCOMPARE(vertices, vertices_right);
    QCOMPARE(t_vertices, t_vertices_right);
    QCOMPARE(face_vertices, face_vertices_right);
    QCOMPARE(face_n_vertices, face_n_vertices_right);
    QCOMPARE(start_pointers, start_pointers_right);
    QCOMPARE(face_t_vertices.size(), 0);

}

void Test::test2_parse_obj()
{
    QVector<QVector3D> vertices;
    QVector<QVector2D> t_vertices;
    QVector<int> face_vertices;
    QVector<int> face_t_vertices;
    QVector<int> face_n_vertices;
    QVector<int> start_pointers;

    QVector<QVector3D>vertices_right= {QVector3D(-1, -1, -1), QVector3D(-1, 0, -1), QVector3D(0, 0, -1), QVector3D(0, -1, -1)};
    QVector<QVector2D> t_vertices_right= {QVector2D(2, 0), QVector2D(4, 3), QVector2D(3, 4), QVector2D(0, 2)};
    QVector<int> face_vertices_right = {1, 2, 3, 4, 4, 3, 1, 3};
    QVector<int> face_t_vertices_right = {1, 2, 3, 4, 4, 3, 2, 2};
    QVector<int> start_pointers_right = {0, 4, 7};

    QString error = nullptr;
    QFile file("ShowModel/r3ds/test2.obj");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);

    QVERIFY(ObjParser::parse_obj(stream, vertices, t_vertices, face_vertices, face_t_vertices,
                                 face_n_vertices, start_pointers, error));
    QCOMPARE(vertices, vertices_right);
    QCOMPARE(t_vertices, t_vertices_right);
    QCOMPARE(face_vertices, face_vertices_right);
    QCOMPARE(start_pointers, start_pointers_right);
    QCOMPARE(face_n_vertices.size(), 0);
}

void Test::test1_parse_obj()
{
    QVector<QVector3D> vertices;
    QVector<QVector2D> t_vertices;
    QVector<int> face_vertices;
    QVector<int> face_t_vertices;
    QVector<int> face_n_vertices;
    QVector<int> start_pointers;

    QVector<QVector3D>vertices_right= {QVector3D(-1, -1, -1), QVector3D(-1, 0, -1), QVector3D(0, 0, -1), QVector3D(0, -1, -1)};
    QVector<QVector2D> t_vertices_right= {QVector2D(2, 0), QVector2D(4, 3), QVector2D(3, 4), QVector2D(0, 2)};
    QVector<int> face_vertices_right = {1, 2, 3, 4, 2, 4, 3, 1, 3, 4, 3, 1};
    QVector<int> face_t_vertices_right = {1, 2, 3, 4, 3, 4, 3, 2, 2, 1, 2, 2};
    QVector<int> start_pointers_right = {0, 5, 9, 11};

    QString error = nullptr;
    QFile file("ShowModel/r3ds/test1.obj");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);

    QVERIFY(ObjParser::parse_obj(stream, vertices, t_vertices, face_vertices, face_t_vertices,
                                 face_n_vertices, start_pointers, error));
    QCOMPARE(vertices, vertices_right);
    QCOMPARE(t_vertices, t_vertices_right);
    QCOMPARE(face_vertices, face_vertices_right);
    QCOMPARE(start_pointers, start_pointers_right);
    QCOMPARE(face_n_vertices.size(), 0);
}

void Test::test_file_import()
{
    QVector<QVector3D> vertices;
    QVector<QVector2D> t_vertices;
    QVector<int> face_vertices;
    QVector<int> face_t_vertices;
    QVector<int> face_n_vertices;
    QVector<int> start_pointers;

    QString error = NULL;
    QString filename1 = "/home/temarales/ShowModel/r3ds/cube.obj";
    QString filename2 = "/home/temarales/ShowModel/r3ds/Basemesh.obj";

    QVERIFY(ObjParser::file_import(filename1, vertices, t_vertices, face_vertices, face_t_vertices, face_n_vertices, start_pointers, error));
    QVERIFY(ObjParser::file_import(filename2, vertices, t_vertices, face_vertices, face_t_vertices, face_n_vertices, start_pointers, error));
}
