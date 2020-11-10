#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "./components/scenewidget.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    SceneWidget* sceneWidget = new SceneWidget(this);
//    sceneWidget->setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);

    ui->setupUi(this);
    ui->centralwidget->layout()->addWidget(sceneWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

