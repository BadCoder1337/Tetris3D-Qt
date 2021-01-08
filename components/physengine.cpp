#include "physengine.h"

#define AREA_SIZE 10
#define CUBE_SIZE 2.0f
#define RESTITUTION 0.0f
#define WALL_SIZE 100

#include <QColor>

PhysEngine::PhysEngine(QObject *parent, r32 dt, const q3Vec3& gravity, i32 iterations) : QObject(parent), q3Scene(dt, gravity, iterations)
{
    SetAllowSleep(true);
    // ground
    q3BodyDef bodyDef;
    bodyDef.bodyType = eStaticBody;
    q3Body* body = CreateBody(bodyDef);
    q3BoxDef boxDef;
    boxDef.SetColor(Qt::green);
    boxDef.SetRestitution(RESTITUTION);
    q3Transform tx;
    q3Identity( tx );
    tx.position.Set(0, -10, 0);
    boxDef.Set( tx, q3Vec3( AREA_SIZE*2, 1, AREA_SIZE*2 ) );
    body->AddBox( boxDef );

    // left wall
    tx.position.Set(AREA_SIZE, -10 + WALL_SIZE / 2, 0);
    boxDef.Set( tx, q3Vec3( 1, WALL_SIZE, AREA_SIZE*2 ) );
    body->AddBox( boxDef );

    // right wall
    tx.position.Set(-AREA_SIZE, -10 + WALL_SIZE / 2, 0);
    boxDef.Set( tx, q3Vec3( 1, WALL_SIZE, AREA_SIZE*2 ) );
    body->AddBox( boxDef );

    // back wall
    tx.position.Set(0, -10 + WALL_SIZE / 2, AREA_SIZE);
    boxDef.Set( tx, q3Vec3( AREA_SIZE*2, WALL_SIZE, 1 ) );
    body->AddBox( boxDef );

    // front wall
    boxDef.SetColor(Qt::transparent);
    tx.position.Set(0, -10 + WALL_SIZE / 2, -AREA_SIZE);
    boxDef.Set( tx, q3Vec3( AREA_SIZE*2, WALL_SIZE, 1 ) );
    body->AddBox( boxDef );
}

void PhysEngine::addPolycube(QVector3D pos, Polycube pcube)
{
    q3BodyDef bodyDef;
    bodyDef.bodyType = eDynamicBody;
    bodyDef.position.Set(pos.x(), pos.y(), pos.z());
    q3Body* body = CreateBody(bodyDef);

    q3BoxDef boxDef;
    pcube.color.setAlphaF(0.5f);
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

    activeBody = body;
}

bool PhysEngine::ReportShape(q3Box *box)
{
    auto body = box->body;
    if (body->GetFlags() & q3Body::eDynamic && !(body->GetFlags() & q3Body::eAwake)) {
        lowestBoxes.append(box);
    }
    return true;
}

void PhysEngine::clearLayer()
{
    qDebug() << "clearLayer";
    q3Box* box;
    foreach (box, lowestBoxes) {
        auto body = box->body;
        body->RemoveBox(box);
    }
}

void PhysEngine::applyImpulse(q3Vec3 impulse)
{
    if (activeBody != nullptr) {
        activeBody->ApplyLinearImpulse(impulse);
    } else {
        qDebug() << "No active body";
    }

}

void PhysEngine::applyTorque(q3Vec3 torque)
{
    if (activeBody != nullptr) {
        activeBody->ApplyTorque(torque);
    } else {
        qDebug() << "No active body";
    }
}
