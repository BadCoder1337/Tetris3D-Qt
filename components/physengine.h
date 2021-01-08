#ifndef PHYSENGINE_H
#define PHYSENGINE_H

#include "../qu3e/q3.h"
#include "polycube.h"
#include <QObject>

class PhysEngine : public QObject, public q3Scene, public q3QueryCallback
{
    Q_OBJECT
public:
    PhysEngine(QObject *parent = nullptr, r32 dt = 1.0f / 60.0f, const q3Vec3& gravity = q3Vec3( r32( 0.0 ), r32( -9.8 ), r32( 0.0 ) ), i32 iterations = 20);

    QVector<q3Box*> lowestBoxes;
    void addPolycube(QVector3D pos, Polycube pcube);
    bool ReportShape(q3Box *box);
    void clearLayer();
    void applyImpulse(q3Vec3 impulse);
    void applyTorque(q3Vec3 torque);

    q3Body* activeBody = nullptr;
};

#endif // PHYSENGINE_H
