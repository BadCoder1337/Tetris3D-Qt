#include "physengine.h"

PhysEngine::PhysEngine(QObject *parent, r32 dt, const q3Vec3& gravity, i32 iterations) : QObject(parent), q3Scene(dt, gravity, iterations)
{
    q3BodyDef bodyDef;
    q3Body* body = CreateBody( bodyDef );
    q3BoxDef boxDef;
    boxDef.SetRestitution( 0 );
    q3Transform tx;
    q3Identity( tx );
    tx.position.Set(0, -10, 0);
    boxDef.Set( tx, q3Vec3( 50.0f, 1.0f, 50.0f ) );
    body->AddBox( boxDef );

    bodyDef.bodyType = eDynamicBody;
    bodyDef.position.Set( 0.0f, 5.0f, 0.0f );
    body = CreateBody( bodyDef );

    tx.rotation.Set(q3Vec3(1.0f, 1.0f, 0.0f), -3.14f);

    for ( int i = 0; i < 10; ++i )
    {
        tx.position.Set( q3RandomFloat( 1.0f, 10.0f ), q3RandomFloat( 1.0f, 10.0f ), q3RandomFloat( 1.0f, 10.0f ) );
        boxDef.Set( tx, q3Vec3( 3.0f, 3.0f, 3.0f ) );
        body->AddBox( boxDef );
    }
}

QVector3D PhysEngine::getGravity() {
    auto g = this->GetGravity();
    return QVector3D(g.x, g.y, g.z);
}
