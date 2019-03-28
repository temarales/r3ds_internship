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
    Scene scene();
}

void MainWindow::handleButton()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                    QString::fromUtf8("Open file"),
                                    QDir::currentPath(),
                                    "Models (*.obj);;All files (*.*)");
    Model new_model = Model::model_from_file(fileName);
    scene.add_new_model(new_model);

    repaint();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPen linepen(Qt::red);
    linepen.setCapStyle(Qt::RoundCap);
    linepen.setWidth(10);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(linepen);
    /*Camera(const QVector3D in_camera_position,
           const QVector3D in_camera_target,
           const QVector3D in_up_vector);*/
    DrawStuff drawer(Camera(QVector3D(10, 10, 10), QVector3D(0, 0, 0), QVector3D(0, 1, 0)), scene, int(this->width()), int(this->height()));
    drawer.draw_all(painter);
}


MainWindow::~MainWindow()
{
    delete ui;
}




