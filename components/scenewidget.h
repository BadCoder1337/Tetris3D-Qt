#ifndef SCENERENDERERWIDGET_H
#define SCENERENDERERWIDGET_H

#include "./qu3e/q3.h"
#include "scenerenderer.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QTimer>

struct Camera
{
    QVector3D position = QVector3D(0.0f, 5.0f, 20.0f);
    QVector3D target = QVector3D(0.0f, 0.0f, 0.0f);
};

struct Light
{
    float ambient[ 4 ] = { 1.0f, 1.0f, 1.0f, 0.5f };
    float diffuse[ 4 ] = { 0.2f, 0.4f, 0.7f, 1.0f };
    float specular[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };
};

class SceneWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    SceneWidget(QWidget *parent);
    ~SceneWidget();

    Camera camera;
    Light light;
    q3Scene* scene = nullptr;
    SceneRenderer renderer;
    QTimer *timer;

public slots:

protected:
    //void paintEvent(QPaintEvent *event) override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    int elapsed;

};

#endif // SCENERENDERERWIDGET_H
