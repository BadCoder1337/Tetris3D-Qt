#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "./components/scenewidget.h"
#include "./qu3e/q3.h"

#include <QTimer>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQuickPaintedItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scenePhys = new q3Scene(1.0f / 60.0f);

    q3BodyDef bodyDef;
    q3Body* body = scenePhys->CreateBody( bodyDef );
    q3BoxDef boxDef;
    boxDef.SetRestitution( 0 );
    q3Transform tx;
    q3Identity( tx );
    tx.position.Set(0, -10, 0);
    boxDef.Set( tx, q3Vec3( 50.0f, 1.0f, 50.0f ) );
    body->AddBox( boxDef );

    bodyDef.bodyType = eDynamicBody;
    bodyDef.position.Set( 0.0f, 5.0f, 0.0f );
    body = scenePhys->CreateBody( bodyDef );

    tx.rotation.Set(q3Vec3(1.0f, 1.0f, 0.0f), -3.14f);

    for ( int i = 0; i < 10; ++i )
    {
        tx.position.Set( q3RandomFloat( 1.0f, 10.0f ), q3RandomFloat( 1.0f, 10.0f ), q3RandomFloat( 1.0f, 10.0f ) );
        boxDef.Set( tx, q3Vec3( 3.0f, 3.0f, 3.0f ) );
        body->AddBox( boxDef );
    }

    ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));

    scene3D = ui->quickWidget->rootObject()->findChild<QQuickItem*>("scene")->childItems().first();
}

MainWindow::~MainWindow()
{
    delete scenePhys;
    delete ui;
}

void MainWindow::on_doubleSpinBox_10_valueChanged(double arg1)
{
    qDebug() << scene3D->property("color");
    scene3D->setProperty("color", "green");
    qDebug() << scene3D->childItems();
}
