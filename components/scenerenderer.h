#ifndef SCENERENDERER_H
#define SCENERENDERER_H

#include "../qu3e/q3.h"

#include <QGLWidget>
#include <QMouseEvent>

class SceneRenderer : public QGLWidget, public q3Render
{
    Q_OBJECT
public:
    explicit SceneRenderer(QWidget *parent = 0);
    ~SceneRenderer();
signals:

public slots:
    void SetPenColor( f32 r, f32 g, f32 b, f32 a = 1.0f ) override;
    void SetPenPosition( f32 x, f32 y, f32 z ) override;
    void SetScale( f32 sx, f32 sy, f32 sz ) override;

    // Render a line from pen position to this point.
    // Sets the pen position to the new point.
    void Line( f32 x, f32 y, f32 z ) override;

    void SetTriNormal( f32 x, f32 y, f32 z ) override;

    // Render a triangle with the normal set by SetTriNormal.
    void Triangle(
        f32 x1, f32 y1, f32 z1,
        f32 x2, f32 y2, f32 z2,
        f32 x3, f32 y3, f32 z3
        ) override;

    // Draw a point with the scale from SetScale
    void Point( ) override;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    void draw();

    int xRot, yRot, zRot;

    f32 x_, y_, z_;
    f32 sx_, sy_, sz_;
    f32 nx_, ny_, nz_;

    QPoint lastPos;
};
#endif // SCENERENDERER_H
