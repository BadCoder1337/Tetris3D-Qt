#include "scenewidget.h"

#include <QPainter>
#include <QPaintEvent>

SceneWidget::SceneWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->setInterval(1000);
    timer->start();

    setMinimumSize(200, 200);
    setMaximumSize(2000, 2000);
    setAutoFillBackground(false);
}

SceneWidget::~SceneWidget() {
    delete timer;
}

void SceneWidget::initializeGL() {
   renderer.Init();
};

void SceneWidget::resizeGL(int width, int height) {
//    f32 aspectRatio = (f32)w / (f32)h;
//    glViewport( 0, 0, w, h );
//    glMatrixMode( GL_PROJECTION );
//    glLoadIdentity( );
//    projection.setToIdentity();
//    projection.perspective(45.0f, aspectRatio, 0.1f, 10000.0f);
//    glMatrixMode( GL_MODELVIEW );
//    glLoadIdentity( );

//    shader.setUniformValue("worldToCamera", )
//    gluLookAt(
//        camera.position[ 0 ], camera.position[ 1 ], camera.position[ 2 ],
//        camera.target[ 0 ], camera.target[ 1 ], camera.target[ 2 ],
//        0.0f, 1.0f, 0.0f
//        );
    renderer.projection.setToIdentity();
    renderer.projection.perspective(60.0f, width / float(height), 0.1f, 1000.0f);
};

void SceneWidget::paintGL() {
    qDebug() << (scene == nullptr ? "scene is nullptr" : "scene ready");
    if (scene) {
        scene->Render(&renderer);
    }
   // make step here
};
