#include "mainwindow.h"
#include <QApplication>
#include "test.h"
#include "GeometryStack/geometrystacktests.h"

void runTests()
{
    Test test;
    GeometryStackTests geometryStack;
    QTest::qExec(&test);
    QTest::qExec(&geometryStack);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    runTests();

    MainWindow w;
    w.show();

    return a.exec();
}
