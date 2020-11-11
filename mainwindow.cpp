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

    for ( int i = 0; i < 1; ++i )
    {
        tx.position.Set( q3RandomFloat( 1.0f, 10.0f ), q3RandomFloat( 1.0f, 10.0f ), q3RandomFloat( 1.0f, 10.0f ) );
        boxDef.Set( tx, q3Vec3( 3.0f, 3.0f, 3.0f ) );
        body->AddBox( boxDef );
    }

    ui->sceneWidget->scene = scene;

    ui->dSBTx->setValue(ui->sceneWidget->initialTransformation.x());
    ui->dSBTy->setValue(ui->sceneWidget->initialTransformation.y());
    ui->dSBTz->setValue(ui->sceneWidget->initialTransformation.z());

    ui->dSBFOV->setValue(ui->sceneWidget->initialProjection.x());
    ui->dSBNearPlane->setValue(ui->sceneWidget->initialProjection.y());
    ui->dSBFarPlane->setValue(ui->sceneWidget->initialProjection.z());

    connect(ui->dSBFOV, SIGNAL(valueChanged(double)), this, SLOT(setParams()));
    connect(ui->dSBCx, SIGNAL(valueChanged(double)), this, SLOT(setParams()));
    connect(ui->dSBCy, SIGNAL(valueChanged(double)), this, SLOT(setParams()));
    connect(ui->dSBCz, SIGNAL(valueChanged(double)), this, SLOT(setParams()));
    connect(ui->dSBTx, SIGNAL(valueChanged(double)), this, SLOT(setParams()));
    connect(ui->dSBTy, SIGNAL(valueChanged(double)), this, SLOT(setParams()));
    connect(ui->dSBTz, SIGNAL(valueChanged(double)), this, SLOT(setParams()));
    connect(ui->dSBFarPlane, SIGNAL(valueChanged(double)), this, SLOT(setParams()));
    connect(ui->dSBNearPlane, SIGNAL(valueChanged(double)), this, SLOT(setParams()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setParams() {
    qDebug() << "SET PARAMS";
    ui->sceneWidget->m_transform.setTranslation(ui->dSBTx->value(), ui->dSBTy->value(), ui->dSBTz->value());
    ui->sceneWidget->m_projection.setToIdentity();
    ui->sceneWidget->m_projection.perspective(ui->dSBFOV->value(), ui->sceneWidget->width() / (float)ui->sceneWidget->height(), ui->dSBNearPlane->value(), ui->dSBFarPlane->value());
    ui->sceneWidget->update();
}

