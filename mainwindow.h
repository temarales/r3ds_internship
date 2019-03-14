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
        QVector<QVector3D> vertices;
        QVector<QVector2D> t_vertices;
        QVector<int> face_vertices;
        QVector<int> face_t_vertices;
        QVector<int> face_n_vertices;
        QVector<int> start_pointers;

    protected:
        void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
