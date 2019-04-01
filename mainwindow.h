#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QtGui>
#include <QFileDialog>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include "objparser.h"
#include "drawstuff.h"
#include "scene.h"
#include <QPen>


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:
     void handleButton();

    private:
        Ui::MainWindow *ui;
        QPushButton *open_button;
        Scene scene;
        DrawStuff drawer;
        Camera camera;

    protected:
        void paintEvent(QPaintEvent *event);
        void keyPressEvent(QKeyEvent *ev);
};

#endif // MAINWINDOW_H
