#ifndef SCENERENDERER_H
#define SCENERENDERER_H

#include "../qu3e/q3.h"
#include "physengine.h"

#include <QGLWidget>
#include <QMouseEvent>

struct Camera
{
    float position[ 3 ] = { 0.0f, 5.0f, -25.0f };
    float target[ 3 ] = { 0.0f, -3.0f, 0.0f };
};

struct Light
{
    float ambient[ 4 ] = { 1.0f, 1.0f, 1.0f, 0.5f };
    float diffuse[ 4 ] = { 0.2f, 0.4f, 0.7f, 1.0f };
    float specular[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };
};

class SceneRenderer : public QGLWidget, public q3Render
{
    Q_OBJECT
public:
    explicit SceneRenderer(QWidget *parent = 0);
    ~SceneRenderer();

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

    Camera camera;
    Light light;

    PhysEngine *physEngine = nullptr;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private:
    void draw();

    f32 x_, y_, z_;
    f32 sx_, sy_, sz_;
    f32 nx_, ny_, nz_;
};
#endif // SCENERENDERER_H
