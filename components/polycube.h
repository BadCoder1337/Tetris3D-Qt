#ifndef POLYCUBE_H
#define POLYCUBE_H

#include <QColor>
#include <QVector>
#include <QVector3D>
#include <QPair>

class Polycube
{
public:
    QVector<QVector3D> cubes;
    QColor color;

    Polycube& addCube(QVector3D v);
    Polycube& setColor(QColor c);
};

#endif // POLYCUBE_H
