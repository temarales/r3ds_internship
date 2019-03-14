#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    open_button = new QPushButton("Import File", this);
    open_button->setGeometry(QRect(QPoint(300, 400), QSize(200, 50)));
    connect(open_button, SIGNAL (released()), this, SLOT (handleButton()));

    QVector<QVector3D> vertices();
    QVector<QVector2D> t_vertices();
    QVector<int> face_vertices();
    QVector<int> face_t_vertices();
    QVector<int> face_n_vertices();
    QVector<int> start_pointers();

}

void MainWindow::handleButton()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                    QString::fromUtf8("Open file"),
                                    QDir::currentPath(),
                                    "Models (*.obj);;All files (*.*)");
    QString error = nullptr;
    ObjParser::file_import(fileName, vertices, t_vertices, face_vertices, face_t_vertices, face_n_vertices, start_pointers, error);
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}




