#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./qu3e/q3.h"
#include "./components/physengine.h"

#include <QMainWindow>
#include <QQuickItem>
#include <QFileSystemWatcher>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    PhysEngine *scenePhys;
    QQuickItem *scene3D;
    QFileSystemWatcher *fsWatcher;

public slots:
    void loadQML();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
