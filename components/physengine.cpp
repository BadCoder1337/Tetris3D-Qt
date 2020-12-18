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

//QVector3D PhysEngine::getGravity() {
//    auto g = this->GetGravity();
//    return QVector3D(g.x, g.y, g.z);
//}

//QVariantList PhysEngine::getBodies() {
//    auto body = m_bodyList;
//    QVariantList bodyList;
//    QVariantList boxList;
//    BodyData d_body;
//    BoxData d_box;
//    while (body) {
//       auto box = body->m_boxes;
//       d_body.position = body->m_tx.position.toQVector3D();
//       d_body.rotation = body->m_tx.rotation.toQQuaternion();
//       while (box) {
//           d_box.size = box->e.toQVector3D() * 2 * 0.01;
//           d_box.color = "red";
//           d_box.position = box->local.position.toQVector3D();
//           d_box.rotation = box->local.rotation.toQQuaternion();

//           boxList.append(QVariant::fromValue(d_box));
//           box = box->next;
//       }
//       d_body.boxes = boxList;
//       bodyList.append(QVariant::fromValue(d_body));
//       body = body->m_next;
//    }
//    auto v = m_bodyList->m_tx.rotation.toQQuaternion();
//    qDebug() << "getBoxes() LENGTH" << bodyList.length();
//    qDebug() << "getBoxes() RAW" << v;
//    // qDebug() << "getBoxes() RESULT" << static_cast<BodyData*>(bodyList.first().data())->position;
//    return bodyList;
//}
