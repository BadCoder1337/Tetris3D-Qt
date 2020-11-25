import QtQuick 2.0
import QtQuick3D 1.15
import QtQuick3D.Materials 1.15
import QtQuick3D.Effects 1.15
import QtQuick3D.Helpers 1.15

View3D {
    id: view3d
    anchors.fill: parent
    anchors.margins: 10
    focus: true
    property string color: "skyblue"
    environment: SceneEnvironment {
                clearColor: color
                backgroundMode: SceneEnvironment.Color
            }

    Node {
      id: sceneNode

      PerspectiveCamera {
          position: Qt.vector3d(0, 200, 300)
          eulerRotation.x: -30
      }

      DirectionalLight {
          eulerRotation.x: -30
          eulerRotation.y: -70
      }

      Model {
          position: Qt.vector3d(0, -200, 0)
          source: "#Cylinder"
          scale: Qt.vector3d(2, 0.2, 1)
          materials: [ DefaultMaterial {
                  diffuseColor: "red"
              }
          ]
      }

      Model {
          position: Qt.vector3d(0, 150, 0)
          source: "#Sphere"

          materials: [ DefaultMaterial {
                  diffuseColor: "blue"
              }
          ]

          SequentialAnimation on y {
              loops: Animation.Infinite
              NumberAnimation {
                  duration: 3000
                  to: -150
                  from: 150
                  easing.type:Easing.InQuad
              }
              NumberAnimation {
                  duration: 3000
                  to: 150
                  from: -150
                  easing.type:Easing.OutQuad
              }
          }
      }
    }

}

