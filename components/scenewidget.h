#ifndef SCENERENDERERWIDGET_H
#define SCENERENDERERWIDGET_H

#include "./qu3e/q3.h"
#include "transform3d.h"

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QTimer>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLDebugLogger>

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

class SceneWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions, public q3Render
{
    Q_OBJECT

public:
    SceneWidget(QWidget *parent);
    ~SceneWidget();

    Camera camera;
    Light light;
    q3Scene *scene = nullptr;
    QTimer *timer;

    QMatrix4x4 projection;
    QOpenGLShaderProgram shader;
    
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

public slots:
    void step();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    int elapsed;

    f32 x_, y_, z_;
    f32 sx_, sy_, sz_;
    f32 nx_, ny_, nz_;

    QOpenGLDebugLogger *logger;
    QOpenGLBuffer m_vertex;
    QOpenGLVertexArrayObject m_object;
    QOpenGLShaderProgram *m_program;

      // Shader Information
    int u_modelToWorld;
    int u_worldToView;
    QMatrix4x4 m_projection;
    Transform3D m_transform;

    // Fix for Windows
    QRegion m_cachedRegion;
};

#endif // SCENERENDERERWIDGET_H
