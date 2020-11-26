#ifndef PHYSENGINE_H
#define PHYSENGINE_H

#include "../qu3e/q3.h"
#include <QObject>
#include <QVector3D>

class PhysEngine : public QObject, public q3Scene
{
    Q_OBJECT
public:
    explicit PhysEngine(QObject *parent = nullptr, r32 dt = 1.0f / 60.0f, const q3Vec3& gravity = q3Vec3( r32( 0.0 ), r32( -9.8 ), r32( 0.0 ) ), i32 iterations = 20);

    Q_INVOKABLE QVector3D getGravity();

signals:

};

#endif // PHYSENGINE_H
