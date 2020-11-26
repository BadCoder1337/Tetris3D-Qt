import QtQuick 2.14
import QtQuick3D 1.15
import QtQuick3D.Helpers 1.15

Item {
    Rectangle {
        id: scene
        anchors.fill: parent
        color: "darkRed"
        objectName: "scene"

        transform: Rotation {
            id: sceneRotation
            axis.x: 1
            axis.y: 0
            axis.z: 0
            origin.x: scene.width / 2
            origin.y: scene.height / 2
        }

        SceneView {
            id: scene3d
        }
    }

    Rectangle {
        radius: 10
        color: "#44BBC5D2"
        border.width: 1
        border.color: "black"
        width: childrenRect.width + anchors.margins
        height: childrenRect.height + anchors.margins
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 20

        Column {
            x: parent.anchors.margins / 2
            y: x

            DebugView {
                source: scene3d
            }


            Text {
                color: "white"
                text: "Multisample: " + ["NoAA", "SSAA", "MSAA", "ProgressiveAA"][scene3d.environment.antialiasingMode]

                MouseArea {
                    anchors.fill: parent
                    onClicked: scene3d.environment.antialiasingMode < 3
                               ? scene3d.environment.antialiasingMode++
                               : scene3d.environment.antialiasingMode = 0
                    onDoubleClicked: scenePhys.getBoxes()[0]
                }
            }

            Text {
                color: "white"
                text: "Quality: " + scene3d.environment.antialiasingQuality

                MouseArea {
                    anchors.fill: parent
                    onClicked: scene3d.environment.antialiasingQuality < 8
                               ? scene3d.environment.antialiasingQuality++
                               : scene3d.environment.antialiasingQuality = 0
                }
            }
        }
    }
}
