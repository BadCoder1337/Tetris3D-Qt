#ifndef SCENERENDERERWIDGET_H
#define SCENERENDERERWIDGET_H

#include <QOpenGLWidget>

class SceneRendererWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    SceneRendererWidget(QWidget *parent);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;
//    void initializeGL() override;
//    void resizeGL(int w, int h) override;
//    void paintGL() override;

private:
    int elapsed;
};

#endif // SCENERENDERERWIDGET_H
