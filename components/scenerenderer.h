#ifndef SCENERENDERER_H
#define SCENERENDERER_H

#include "./qu3e/q3.h"
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

class SceneRenderer : public QOpenGLFunctions, public q3Render
{
public:
//    SceneRenderer();
//    ~SceneRenderer();

    bool Init();

    void SetPenColor( f32 r, f32 g, f32 b, f32 a ) override final;
    void SetPenPosition( f32 x, f32 y, f32 z ) override final;
    void SetScale( f32 sx, f32 sy, f32 sz ) override final;
    void Line( f32 x, f32 y, f32 z ) override final;
    void Triangle(
            f32 x1, f32 y1, f32 z1,
            f32 x2, f32 y2, f32 z2,
            f32 x3, f32 y3, f32 z3
            ) override final;
    void SetTriNormal( f32 x, f32 y, f32 z ) override final;
    void Point( ) override final;

    QMatrix4x4 projection;
    QOpenGLShaderProgram shader;

    bool failed;

private:
    f32 x_, y_, z_;
    f32 sx_, sy_, sz_;
    f32 nx_, ny_, nz_;
};

#endif // SCENERENDERER_H
