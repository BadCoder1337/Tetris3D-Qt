#include "physengine.h"

#define CUBE_SIZE 1.5f
#define RESTITUTION 0.0f

PhysEngine::PhysEngine(QObject *parent, r32 dt, const q3Vec3& gravity, i32 iterations) : QObject(parent), q3Scene(dt, gravity, iterations)
{
    q3BodyDef bodyDef;
    q3Body* body = CreateBody(bodyDef);
    q3BoxDef boxDef;
    boxDef.SetRestitution(RESTITUTION);
    q3Transform tx;
    q3Identity( tx );
    tx.position.Set(0, -10, 0);
    boxDef.Set( tx, q3Vec3( 50.0f, 1.0f, 50.0f ) );
    boxDef.SetColor(Qt::green);
    body->AddBox( boxDef );
}

void PhysEngine::addPolycube(QVector3D pos, Polycube pcube)
{
    q3BodyDef bodyDef;
    bodyDef.bodyType = eDynamicBody;
    bodyDef.position.Set(pos.x(), pos.y(), pos.z());
    q3Body* body = CreateBody(bodyDef);

    q3BoxDef boxDef;
    boxDef.SetColor(pcube.color);
    boxDef.SetRestitution(RESTITUTION);

    q3Transform tx;
    q3Identity( tx );

    QVector3D cube;

    foreach (cube, pcube.cubes) {
        tx.position.Set( cube.x() * CUBE_SIZE, cube.y() * CUBE_SIZE, cube.z() * CUBE_SIZE );
        boxDef.Set( tx, q3Vec3( CUBE_SIZE, CUBE_SIZE, CUBE_SIZE ) );
        body->AddBox( boxDef );
    }
}
