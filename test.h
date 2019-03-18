#ifndef TEST_H
#define TEST_H

#include <QTest>

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = 0);
    bool vector2d_qFuzzyCompare(const QVector2D a, const QVector2D b);
    bool vector3d_qFuzzyCompare(const QVector3D a, const QVector3D b);
private slots:
    void test_vertex3D_from_strings();
    void test_vertex2D_from_strings();
    void test_face_indices_from_string();
    void test_file_import();

    void test_parse_obj();
    void test1_parse_obj();
    void test2_parse_obj();
    void test3_parse_obj();
};

#endif // TEST_H
