#include "polycube.h"

Polycube::Polycube(QObject *parent) : QObject(parent)
{

}

Polycube& Polycube::addCube(QVector3D v)
{
    cubes.append(v);
    return *this;
}

Polycube& Polycube::setColor(QColor c)
{
    color = c;
    return *this;
}
