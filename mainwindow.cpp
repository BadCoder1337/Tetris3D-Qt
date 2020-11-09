#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "scenerendererwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    SceneRendererWidget* sceneRendererWidget = new SceneRendererWidget(this);

    ui->setupUi(this);
    ui->centralwidget->layout()->addWidget(sceneRendererWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

