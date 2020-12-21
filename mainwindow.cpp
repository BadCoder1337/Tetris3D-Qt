#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "./qu3e/q3.h"
#include "./components/physengine.h"
#include "./components/polycube.h"

#include <QTimer>
#include <QFileDialog>

#define DEV true
#define QML_DEV_PATH "../Tetris3D"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initEngine();

    stepTimer = new QTimer(this);
    connect(stepTimer, SIGNAL(timeout()), this, SLOT(step()));
    stepTimer->setInterval(1000 / 60);
    stepTimer->start();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(addObject()));
    timer->setInterval(2000);
}

MainWindow::~MainWindow()
{
    f_pcubes.close();
    engine->Shutdown();
    delete engine;
    delete ui;
}

void MainWindow::initEngine()
{
    if (engine) {
        engine->Shutdown();
        delete engine;
    }

    engine = new PhysEngine();
    ui->sceneRenderer->physEngine = engine;
}

void MainWindow::step()
{
    engine->Step();
    ui->sceneRenderer->update();
}

void MainWindow::addObject()
{
    if (!f_pcubes.isOpen()) return;

    QTextStream in(&f_pcubes);
    in.seek(fileStreamPos);

    Polycube shape;
    int count;
    QString colorName;
    int xPos, yPos, zPos;

    in >> count >> xPos >> yPos >> zPos >> colorName;

    QVector3D pos(xPos, yPos, zPos);

    shape.setColor(QColor(colorName));

    for (int i = 0; i < count; i++) {
        int x, y, z;
        in >> x >> y >> z;
        auto v = QVector3D(x , y, z);
        shape.addCube(v);
    }

    fileStreamPos = in.pos();
    engine->addPolycube(pos, shape);

    if (in.atEnd()) {
        timer->stop();
        f_pcubes.close();
        fileStreamPos = 0;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    if (f_pcubes.isOpen()) f_pcubes.close();
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", QString(),
               QString("Tetris3D shape stream (*.t3dss)"));
    if (!fileName.isEmpty())
    {
        f_pcubes.setFileName(fileName);
        f_pcubes.open(QIODevice::ReadOnly);
        timer->start();
     }
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::on_actionClear_triggered()
{
    initEngine();
}
