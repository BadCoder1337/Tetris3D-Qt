#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./qu3e/q3.h"

#include <QMainWindow>
#include <QQuickItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    q3Scene *scenePhys;
    QQuickItem *scene3D;

private slots:
    void on_doubleSpinBox_10_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
