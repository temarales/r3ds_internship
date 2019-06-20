#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DrawingTools/drawwindowgl.h"
#include <QGridLayout>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    open_button = new QPushButton("Import File", this);
    open_button->setGeometry(QRect(QPoint(0, 0), QSize(200, 50)));
    connect(open_button, SIGNAL (released()), this, SLOT (handleButton()));

    mdiArea = new QMdiArea(this);
    //setCentralWidget(mdiArea);
    mdiArea->setGeometry(300, 150, 640, 440);
    widget = new DrawWindowGL(mdiArea, &scene, &camera);
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    mdiArea->addSubWindow(widget);
    widget->showMaximized();

    camera = Camera(QVector3D(0, 20, 70), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
    Scene scene;
}

void MainWindow::handleButton()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                    QString::fromUtf8("Open file"),
                                    QDir::currentPath(),
                                    "Models (*.obj);;All files (*.*)");
    Model newModel = Model::modelFromFile(fileName);
    QString error;
    newModel.triangulate(error);
    newModel.calculateNewNormals();
    scene.addNewModel(newModel);

    widget->repaint();
    //repaint();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    /*QPainter painter(this);
    QPen linepen(Qt::red);
    linepen.setCapStyle(Qt::RoundCap);
    linepen.setWidth(1);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(linepen);

    DrawStuff drawer(camera, scene, int(this->width()), int(this->height()));
    drawer.drawAll(painter);*/
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_W)
    {
        widget->setBackgroundcolor(Qt::green);
        camera.moveCloserOrFurther(-2);
    }
    if(ev->key() == Qt::Key_S)
    {
        widget->setBackgroundcolor(Qt::gray);
        camera.moveCloserOrFurther(2);
    }
    if(ev->key() == Qt::Key_D)
    {
        camera.RotateView(-10, 1, 1, 1);
    }
    if (ev->key() == Qt::Key_A)
    {
        camera.RotateView(10, 1, 1, 1);
    }

    widget->update();
}


MainWindow::~MainWindow()
{
    delete ui;
}




