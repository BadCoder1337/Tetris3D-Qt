#include "scenewidget.h"
#include "vertex.h"

#include <QSurfaceFormat>
#include <QOpenGLDebugLogger>

SceneWidget::SceneWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setOption(QSurfaceFormat::DebugContext);
    setFormat(format);

//    setUpdateBehavior(UpdateBehavior::NoPartialUpdate);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(step()));
    timer->setInterval(1000 / 60);
    timer->start();

    setMinimumSize(200, 200);
    setMaximumSize(2000, 2000);

}

SceneWidget::~SceneWidget() {
    m_vertex.release();
    m_object.destroy();
    m_vertex.destroy();
    delete m_program;
    delete timer;
}

void SceneWidget::initializeGL() {
    initializeOpenGLFunctions();
    logger = new QOpenGLDebugLogger(this);
    logger->initialize();

    m_transform.translate(0.0f, 0.0f, -5.0f);

    glEnable(GL_CULL_FACE);
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

      // Application-specific initialization
      {
        // Create Shader (Do not release until VAO is created)
        m_program = new QOpenGLShaderProgram();
        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/components/shaders/simple.vert");
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/components/shaders/simple.frag");
        m_program->link();
        m_program->bind();

        // Cache Uniform Locations
        u_modelToWorld = m_program->uniformLocation("modelToWorld");
        u_worldToView = m_program->uniformLocation("worldToView");

        // Create Buffer (Do not release until VAO is created)
        m_vertex.create();
        m_vertex.bind();
        m_vertex.setUsagePattern(QOpenGLBuffer::StreamDraw);

        // Create Vertex Array Object
        m_object.create();
        m_object.bind();
        m_program->enableAttributeArray(0);
        m_program->enableAttributeArray(1);
        m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
        m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

        // Release (unbind) all
        m_object.release();
//        m_vertex.release();
        m_program->release();
      }

    const QList<QOpenGLDebugMessage> messages = logger->loggedMessages();
        for (const QOpenGLDebugMessage &message : messages)
            qDebug() << "initializeGL" << message;
    delete logger;
};

void SceneWidget::resizeGL(int width, int height) {
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
    update();
};

void SceneWidget::paintGL() {
    logger = new QOpenGLDebugLogger(this);
    logger->initialize();

    glClear(GL_COLOR_BUFFER_BIT);

//    Triangle( 0.0f,  0.0f,  0.5f,
//              -1.0f,  1.0f,  0.5f,
//              -1.0f, -0.5f,  0.5f);

//    Triangle( 0.5f,  0.5f,  0.5f,
//              -0.5f,  0.5f,  0.5f,
//              -0.5f, -0.5f,  0.5f);

//    Triangle( 0.5f,  0.5f,  0.5f,
//              -0.5f,  0.5f,  0.5f,
//              -0.5f, -0.5f,  0.5f);

    qDebug() << (scene == nullptr ? "scene is nullptr" : "scene ready");
    if (scene) {
        scene->Render(this);
    }
    const QList<QOpenGLDebugMessage> messages = logger->loggedMessages();
        for (const QOpenGLDebugMessage &message : messages)
            qDebug() << "paintGL" << message;
    delete logger;

};

void SceneWidget::step() {
    qDebug() << "step";
    if (scene) {
        scene->Step();
        update();
    }
}

void SceneWidget::SetPenColor( f32 r, f32 g, f32 b, f32 a = 1.0f )
{
    Q3_UNUSED( a );

//    glColor3f( (float)r, (float)g, (float)b );
}

void SceneWidget::SetPenPosition( f32 x, f32 y, f32 z )
{
    x_ = x, y_ = y, z_ = z;
}

void SceneWidget::SetScale( f32 sx, f32 sy, f32 sz )
{
//    glPointSize( (float)sx );
    sx_ = sx, sy_ = sy, sz_ = sz;
}

void SceneWidget::Line( f32 x, f32 y, f32 z )
{
//    glBegin( GL_LINES );
//    glVertex3f( (float)x_, (float)y_, (float)z_ );
//    glVertex3f( (float)x, (float)y, (float)z );
    SetPenPosition( x, y, z );
//    glEnd( );
}

void SceneWidget::Triangle(
    f32 x1, f32 y1, f32 z1,
    f32 x2, f32 y2, f32 z2,
    f32 x3, f32 y3, f32 z3
    )
{
//    f32 values[] = { x1,  y1,  z1, x2,  y2,  z2, x3,  y3,  z3 };
//    QMatrix3x3 triangle(values);
    Vertex sg_vertexes[] = {
      // Face 1 (Front)
        Vertex( QVector3D( x1,  y1,  z1).normalized(), QVector3D( 1.0f, 0.0f, 0.0f ) ),
        Vertex( QVector3D( x2,  y2,  z2).normalized(), QVector3D( 0.0f, 1.0f, 0.0f ) ),
        Vertex( QVector3D( x3,  y3,  z3).normalized(), QVector3D( 0.0f, 0.0f, 1.0f ) )
    };

    m_vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

      // Render using our shader
    m_program->bind();
    m_program->setUniformValue(u_worldToView, m_projection);
      m_object.bind();
      m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());
      glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
      m_object.release();
    m_program->release();
}

void SceneWidget::SetTriNormal( f32 x, f32 y, f32 z )
{
    nx_ = x;
    ny_ = y;
    nz_ = z;
}

void SceneWidget::Point( )
{
//    glBegin( GL_POINTS );
//    glVertex3f( (float)x_, (float)y_, (float)z_ );
//    glEnd( );
};
