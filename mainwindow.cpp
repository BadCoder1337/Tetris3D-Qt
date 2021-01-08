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

    srand(time(0));
    initEngine();

    stepTimer = new QTimer(this);
    connect(stepTimer, SIGNAL(timeout()), this, SLOT(step()));
    stepTimer->setInterval(1000 / 60);
    stepTimer->start();

    queryTimer = new QTimer(this);
    connect(queryTimer, SIGNAL(timeout()), this, SLOT(checkLayer()));
    queryTimer->setInterval(2000);
    queryTimer->start();

    shapeTimer = new QTimer(this);
    connect(shapeTimer, SIGNAL(timeout()), this, SLOT(addRandomObject()));
    shapeTimer->setInterval(3000);
    shapeTimer->start();
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int impulse = 100;
    int torque = 2000;
    switch (event->key()) {
        case Qt::Key_A: return engine->applyImpulse(q3Vec3(impulse, 0, 0));
        case Qt::Key_D: return engine->applyImpulse(q3Vec3(-impulse, 0, 0));
        case Qt::Key_W: return engine->applyImpulse(q3Vec3(0, 0, impulse));
        case Qt::Key_S: return engine->applyImpulse(q3Vec3(0, 0, -impulse));

        case Qt::Key_Left:  return engine->applyTorque(q3Vec3( torque,  0, 0));
        case Qt::Key_Right: return engine->applyTorque(q3Vec3(-torque, -0, 0));
        case Qt::Key_Up:    return engine->applyTorque(q3Vec3(0,  0,  torque));
        case Qt::Key_Down:  return engine->applyTorque(q3Vec3(0, -0, -torque));
    }
}

void MainWindow::step()
{
    engine->Step();
    ui->sceneRenderer->update();
}

//void MainWindow::addObject()
//{
//    if (!f_pcubes.isOpen()) return;

//    QTextStream in(&f_pcubes);
//    in.seek(fileStreamPos);

//    Polycube shape;
//    int count;
//    QString colorName;
//    int xPos, yPos, zPos;

//    in >> count >> xPos >> yPos >> zPos >> colorName;

//    QVector3D pos(xPos, yPos, zPos);

//    shape.setColor(QColor(colorName));

//    for (int i = 0; i < count; i++) {
//        int x, y, z;
//        in >> x >> y >> z;
//        auto v = QVector3D(x , y, z);
//        shape.addCube(v);
//    }

//    fileStreamPos = in.pos();
//    engine->addPolycube(pos, shape);

//    if (in.atEnd()) {
//        shapeTimer->stop();
//        f_pcubes.close();
//        fileStreamPos = 0;
//    }
//}

uint qHash(const QVector3D &v)
{
       return qHash( QString( "%1x%2x%3" ).arg(v.x()).arg(v.y()).arg(v.z()) ) ;
}

void MainWindow::addRandomObject()
{
    Polycube shape;

    QVector3D pos(0, 30, 0);

    shape.setColor(QColor(rand() % 255, rand() % 255, rand() % 255));

    QSet<QVector3D> polycubeDef;
    QVector3D init(0, 0, 0);
    while (polycubeDef.size() < 6) {
        QVector3D change;
        change[rand()%3] = rand()%2 ? 1 : -1;
        init += change;
        polycubeDef.insert(init);
    }

    QVector3D v;
    foreach (v, polycubeDef) shape.addCube(v);

    engine->addPolycube(pos, shape);
}

void MainWindow::checkLayer()
{
    q3AABB area;
    area.min = q3Vec3(-25, -9, -25);
    area.max = q3Vec3(25, -8.75f, 25);
    engine->QueryAABB(engine, area);

    if (engine->lowestBoxes.size() > 25) {
        score += engine->lowestBoxes.size();
        engine->clearLayer();
    }
    setWindowTitle("Tetris3D Demo - score: "+QString::number(score));
    engine->lowestBoxes.clear();
}

//void MainWindow::on_actionOpen_triggered()
//{
//    if (f_pcubes.isOpen()) f_pcubes.close();
//    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", QString(),
//               QString("Tetris3D shape stream (*.t3dss)"));
//    if (!fileName.isEmpty())
//    {
//        f_pcubes.setFileName(fileName);
//        f_pcubes.open(QIODevice::ReadOnly);
//        shapeTimer->start();
//     }
//}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::on_actionClear_triggered()
{
    score = 0;
    initEngine();
}
