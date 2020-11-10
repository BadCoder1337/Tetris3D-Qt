#include "scenerenderer.h"

#include <QOpenGLFunctions>

bool SceneRenderer::Init() {
    return shader.link() && shader.bind();
}

void SceneRenderer::SetPenColor( f32 r, f32 g, f32 b, f32 a = 1.0f )
{
    Q3_UNUSED( a );

    glColor3f( (float)r, (float)g, (float)b );
}

void SceneRenderer::SetPenPosition( f32 x, f32 y, f32 z )
{
    x_ = x, y_ = y, z_ = z;
}

void SceneRenderer::SetScale( f32 sx, f32 sy, f32 sz )
{
    glPointSize( (float)sx );
    sx_ = sx, sy_ = sy, sz_ = sz;
}

void SceneRenderer::Line( f32 x, f32 y, f32 z )
{
    glBegin( GL_LINES );
    glVertex3f( (float)x_, (float)y_, (float)z_ );
    glVertex3f( (float)x, (float)y, (float)z );
    SetPenPosition( x, y, z );
    glEnd( );
}

void SceneRenderer::Triangle(
    f32 x1, f32 y1, f32 z1,
    f32 x2, f32 y2, f32 z2,
    f32 x3, f32 y3, f32 z3
    )
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

void SceneRenderer::SetTriNormal( f32 x, f32 y, f32 z )
{
    nx_ = x;
    ny_ = y;
    nz_ = z;
}

void SceneRenderer::Point( )
{
    glBegin( GL_POINTS );
    glVertex3f( (float)x_, (float)y_, (float)z_ );
    glEnd( );
};
