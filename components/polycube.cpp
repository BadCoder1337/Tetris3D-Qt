#include "polycube.h"

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
