#ifndef BOXDATA_H
#define BOXDATA_H

#include <QObject>
#include <QColor>
#include <QQuaternion>
#include <QVector3D>

struct BoxData {
private:
    Q_GADGET
    Q_PROPERTY(QColor color         MEMBER color)
    Q_PROPERTY(QQuaternion rotation MEMBER rotation)
    Q_PROPERTY(QVector3D position   MEMBER position)
    Q_PROPERTY(QVector3D size       MEMBER size)

public:
    QColor color;
    QQuaternion rotation;
    QVector3D position;
    QVector3D size;
};

Q_DECLARE_METATYPE(BoxData);

#endif // BOXDATA_H
