#include "mainwindow.h"
#include <QApplication>
#include "test.h"

void runTests()
{
    Test test;
    QTest::qExec(&test);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    runTests();

    MainWindow w;
    w.show();

    return a.exec();
}
