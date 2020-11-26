QT       += core gui qml quick 3dinput widgets 3dextras quickwidgets

CONFIG += c++11

SOURCES += \
    components/physengine.cpp \
    components/polycube.cpp \
    main.cpp \
    mainwindow.cpp \
    qu3e/broadphase/q3BroadPhase.cpp \
    qu3e/broadphase/q3DynamicAABBTree.cpp \
    qu3e/collision/q3Box.cpp \
    qu3e/collision/q3Collide.cpp \
    qu3e/common/q3Geometry.cpp \
    qu3e/common/q3Memory.cpp \
    qu3e/dynamics/q3Body.cpp \
    qu3e/dynamics/q3Contact.cpp \
    qu3e/dynamics/q3ContactManager.cpp \
    qu3e/dynamics/q3ContactSolver.cpp \
    qu3e/dynamics/q3Island.cpp \
    qu3e/math/q3Mat3.cpp \
    qu3e/math/q3Quaternion.cpp \
    qu3e/math/q3Vec3.cpp \
    qu3e/scene/q3Scene.cpp

HEADERS += \
    components/physengine.h \
    components/polycube.h \
    mainwindow.h \
    qu3e/broadphase/q3BroadPhase.h \
    qu3e/broadphase/q3DynamicAABBTree.h \
    qu3e/broadphase/q3DynamicAABBTree.inl \
    qu3e/collision/q3Box.h \
    qu3e/collision/q3Box.inl \
    qu3e/collision/q3Collide.h \
    qu3e/common/q3Geometry.h \
    qu3e/common/q3Geometry.inl \
    qu3e/common/q3Memory.h \
    qu3e/common/q3Settings.h \
    qu3e/common/q3Types.h \
    qu3e/debug/q3Render.h \
    qu3e/dynamics/q3Body.h \
    qu3e/dynamics/q3Contact.h \
    qu3e/dynamics/q3ContactManager.h \
    qu3e/dynamics/q3ContactSolver.h \
    qu3e/dynamics/q3Island.h \
    qu3e/math/q3Mat3.h \
    qu3e/math/q3Mat3.inl \
    qu3e/math/q3Math.h \
    qu3e/math/q3Math.inl \
    qu3e/math/q3Quaternion.h \
    qu3e/math/q3Transform.h \
    qu3e/math/q3Transform.inl \
    qu3e/math/q3Vec3.h \
    qu3e/math/q3Vec3.inl \
    qu3e/q3.h \
    qu3e/scene/q3Scene.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

#LIBS += -lOpenGL32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    qml/SceneView.qml \
    qml/main.qml
