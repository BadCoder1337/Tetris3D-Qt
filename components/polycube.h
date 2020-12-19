#ifndef POLYCUBE_H
#define POLYCUBE_H

#include <QObject>
#include <QColor>
#include <QVector>
#include <QVector3D>
#include <QPair>

class Polycube : public QObject
{
    Q_OBJECT
public:
    explicit Polycube(QObject *parent = nullptr);

    QVector<QVector3D> cubes;
    QColor color;

    Polycube& addCube(QVector3D v);
    Polycube& setColor(QColor c);

signals:

};

#endif // POLYCUBE_H
