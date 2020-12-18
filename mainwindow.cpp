#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "./qu3e/q3.h"
#include "./components/physengine.h"

#include <QTimer>

#define DEV true
#define QML_DEV_PATH "../Tetris3D"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    scenePhys = new PhysEngine(nullptr, 1);
    scenePhys = new PhysEngine();

//    if (DEV) {
//        fsWatcher = new QFileSystemWatcher(this);
//        QDir qmlDir(QString(QML_DEV_PATH) + "/qml");
//        QStringList files = qmlDir.entryList(QStringList() << "*.qml", QDir::Files);
//         foreach(QString file, files) {
//             fsWatcher->addPath(qmlDir.path() + "/" + file);
//        }
//        qDebug() << fsWatcher->files();

//        connect(fsWatcher, SIGNAL(fileChanged(QString)), this, SLOT(loadQML()));
//        connect(fsWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(loadQML()));
//        connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(loadQML()));
//    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(step()));
    timer->setInterval(1000 / 60);
    timer->start();
}

MainWindow::~MainWindow()
{
    scenePhys->Shutdown();
    delete scenePhys;
    delete ui;
}

void MainWindow::step()
{
    scenePhys->Step();
    scenePhys->Render(ui->sceneRenderer);
}

//void MainWindow::on_doubleSpinBox_10_valueChanged(double arg1)
//{
//    qDebug() << scene3D->property("color");
//    scene3D->setProperty("color", "green");
//     qDebug() << scene3D->property("camera");
//}
