#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "./components/scenewidget.h"
#include "./qu3e/q3.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    q3Scene *scene = new q3Scene(1.0f / 60.0f);

    q3BodyDef bodyDef;
    q3Body* body = scene->CreateBody( bodyDef );
    q3BoxDef boxDef;
    boxDef.SetRestitution( 0 );
    q3Transform tx;
    q3Identity( tx );
    tx.position.Set(0, -10, 0);
    boxDef.Set( tx, q3Vec3( 50.0f, 1.0f, 50.0f ) );
    body->AddBox( boxDef );

    bodyDef.bodyType = eDynamicBody;
    bodyDef.position.Set( 0.0f, 5.0f, 0.0f );
    body = scene->CreateBody( bodyDef );

    tx.rotation.Set(q3Vec3(1.0f, 1.0f, 0.0f), -3.14f);

    for ( int i = 0; i < 10; ++i )
    {
        tx.position.Set( q3RandomFloat( 1.0f, 10.0f ), q3RandomFloat( 1.0f, 10.0f ), q3RandomFloat( 1.0f, 10.0f ) );
        boxDef.Set( tx, q3Vec3( 3.0f, 3.0f, 3.0f ) );
        body->AddBox( boxDef );
    }

    ui->sceneWidget->scene = scene;
}

MainWindow::~MainWindow()
{
    delete ui;
}

