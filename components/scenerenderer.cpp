#include "scenerenderer.h"
#include "physengine.h"

#include <QtMath>
#include <GL/GL.h>
#include <GL/GLU.h>

SceneRenderer::SceneRenderer(QWidget *parent): QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {}

SceneRenderer::~SceneRenderer() {}

void SceneRenderer::SetPenColor(f32 r, f32 g, f32 b, f32 a)
{
    Q3_UNUSED( a );

    glColor3f( (float)r, (float)g, (float)b );
}

void SceneRenderer::SetPenPosition(f32 x, f32 y, f32 z)
{
    x_ = x, y_ = y, z_ = z;
}

void SceneRenderer::SetScale(f32 sx, f32 sy, f32 sz)
{
    glPointSize( (float)sx );
    sx_ = sx, sy_ = sy, sz_ = sz;
}

void SceneRenderer::Line(f32 x, f32 y, f32 z)
{
//    glBegin( GL_LINES );
//    glVertex3f( (float)x_, (float)y_, (float)z_ );
//    glVertex3f( (float)x, (float)y, (float)z );
//    SetPenPosition( x, y, z );
//    glEnd( );
}

void SceneRenderer::SetTriNormal(f32 x, f32 y, f32 z)
{
    nx_ = x;
    ny_ = y;
    nz_ = z;
}

void SceneRenderer::Triangle(f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32 x3, f32 y3, f32 z3)
{
    glBegin( GL_TRIANGLES );
        glNormal3f( (float)nx_, (float)ny_, (float)nz_ );
        glVertex3f( (float)x1, (float)y1, (float)z1 );
        glVertex3f( (float)x2, (float)y2, (float)z2 );
        glVertex3f( (float)x3, (float)y3, (float)z3 );
    glEnd( );
}

void SceneRenderer::Point()
{
//    glBegin( GL_POINTS );
//    glVertex3f( (float)x_, (float)y_, (float)z_ );
//    glEnd( );
}

void SceneRenderer::initializeGL()
{
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void SceneRenderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (physEngine) {
        physEngine->Render(this);
    }
}

void SceneRenderer::resizeGL(int width, int height)
{
    f32 aspectRatio = (f32)width / (f32)height;
    glViewport( 0, 0, width, height );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45.0f, aspectRatio, 0.1f, 10000.0f );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            camera.position[0], camera.position[1], camera.position[2],
            camera.target[0], camera.target[1], camera.target[2],
            0.0f, 1.0f, 0.0f
            );
}
