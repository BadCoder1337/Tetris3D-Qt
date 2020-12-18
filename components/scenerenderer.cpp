#include "scenerenderer.h"

SceneRenderer::SceneRenderer(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
}

SceneRenderer::~SceneRenderer()
{
}

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
    glBegin( GL_LINES );
    glVertex3f( (float)x_, (float)y_, (float)z_ );
    glVertex3f( (float)x, (float)y, (float)z );
    SetPenPosition( x, y, z );
    glEnd( );
}

void SceneRenderer::SetTriNormal(f32 x, f32 y, f32 z)
{
    nx_ = x;
    ny_ = y;
    nz_ = z;
}

void SceneRenderer::Triangle(f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32 x3, f32 y3, f32 z3)
{
    glEnable( GL_LIGHTING );
    glBegin( GL_TRIANGLES );
    glNormal3f( (float)nx_, (float)ny_, (float)nz_ );
    glColor4f( 0.2f, 0.4f, 0.7f, 0.5f );
    glVertex3f( (float)x1, (float)y1, (float)z1 );
    glVertex3f( (float)x2, (float)y2, (float)z2 );
    glVertex3f( (float)x3, (float)y3, (float)z3 );
    glEnd( );
    glDisable( GL_LIGHTING );
}

void SceneRenderer::Point()
{
    glBegin( GL_POINTS );
    glVertex3f( (float)x_, (float)y_, (float)z_ );
    glEnd( );
}

QSize SceneRenderer::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize SceneRenderer::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void SceneRenderer::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void SceneRenderer::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void SceneRenderer::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void SceneRenderer::initializeGL()
{
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void SceneRenderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    draw();
}

void SceneRenderer::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void SceneRenderer::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void SceneRenderer::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}

void SceneRenderer::draw()
{
    qglColor(Qt::red);
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glVertex3f(-1,-1,0);
        glVertex3f(-1,1,0);
        glVertex3f(1,1,0);
        glVertex3f(1,-1,0);

    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(0,-1,0.707);
        glVertex3f(-1,-1,0);
        glVertex3f(1,-1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(1,0, 0.707);
        glVertex3f(1,-1,0);
        glVertex3f(1,1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(0,1,0.707);
        glVertex3f(1,1,0);
        glVertex3f(-1,1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(-1,0,0.707);
        glVertex3f(-1,1,0);
        glVertex3f(-1,-1,0);
        glVertex3f(0,0,1.2);
    glEnd();
}
