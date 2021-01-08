#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./qu3e/q3.h"
#include "./components/physengine.h"

#include <QMainWindow>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer *stepTimer;
    QTimer *queryTimer;
    QTimer *shapeTimer;

    int score = 0;

    PhysEngine *engine = nullptr;

    void initEngine();

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void step();
//    void addObject();
    void addRandomObject();
    void checkLayer();

private slots:
//    void on_actionOpen_triggered();
    void on_actionQuit_triggered();
    void on_actionClear_triggered();

private:
    Ui::MainWindow *ui;

    QFile f_pcubes;
    int fileStreamPos = 0;
};
#endif // MAINWINDOW_H
