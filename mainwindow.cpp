#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "./qu3e/q3.h"
#include "./components/physengine.h"

#include <QTimer>
#include <QDir>

#define DEV true
#define QML_DEV_PATH "../Tetris3D"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    scenePhys = new PhysEngine(nullptr, 1);
    scenePhys = new PhysEngine();

//    auto camera = scene3D->property("camera");
//    auto cameraPosition = scene3D->property("cameraPosition").value<QVector3D>();
//    qDebug() << cameraPosition;

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

//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(step()));
//    timer->setInterval(1000);
//    timer->start();
}

//void MainWindow::loadQML() {
//    qDebug() << "loadQML";
//    ui->quickWidget->engine()->clearComponentCache();
//    ui->quickWidget->engine()->rootContext()->setContextProperty("scenePhys", scenePhys);
//    ui->quickWidget->engine()->rootContext()->setContextProperty("sceneBodies", scenePhys->getBodies());
//    if (DEV) {
//        ui->quickWidget->setSource(QUrl::fromLocalFile(QString(QML_DEV_PATH) + "/qml/main.qml"));
//    } else {
//        ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));
//    }
//    scene3D = ui->quickWidget->rootObject()->findChild<QQuickItem*>("scene")->childItems().first();
//}

void MainWindow::step() {
    qDebug() << "step()";
    scenePhys->Step();
//    ui->quickWidget->engine()->rootContext()->setContextProperty("sceneBoxes", scenePhys->getBodies());
}

MainWindow::~MainWindow()
{
    scenePhys->Shutdown();
    delete scenePhys;
    delete ui;
}

//void MainWindow::on_doubleSpinBox_10_valueChanged(double arg1)
//{
//    qDebug() << scene3D->property("color");
//    scene3D->setProperty("color", "green");
//     qDebug() << scene3D->property("camera");
//}
