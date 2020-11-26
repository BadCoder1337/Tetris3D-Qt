import QtQuick 2.14
import QtQuick3D 1.15
import QtQuick3D.Materials 1.15
import QtQuick3D.Effects 1.15
import QtQuick3D.Helpers 1.15

View3D {
    id: view3d
    anchors.fill: parent
    anchors.margins: 10
    focus: true

    property vector3d cameraPosition: Qt.vector3d(0, 400, 500)
    property vector3d cameraRotation: Qt.vector3d(-30, 0, 0)
    property real fov: 60;

    property vector3d lightPosition: Qt.vector3d(0, 0, 0)
    property vector3d lightRotation: Qt.vector3d(-30, -70, 0)

    property bool commandPressed: false

    environment: SceneEnvironment {
        backgroundMode: SceneEnvironment.SkyBox
        lightProbe: Texture { source: "/assets/skybox.hdr" }
        antialiasingQuality: SceneEnvironment.Medium
        antialiasingMode: SceneEnvironment.SSAA
    }

    WasdController {
        controlledObject: camera
        anchors.fill: parent
        enabled: !commandPressed
    }

    WasdController {
        controlledObject: light
        anchors.fill: parent
        enabled: commandPressed
    }

    Shortcut {
        sequence: "Ctrl+L"
        onActivated: {
            console.log("Ctrl+L");
            commandPressed = !commandPressed;
        }
    }

    Node {
      id: sceneNode

      PerspectiveCamera {
          id: camera
          position: cameraPosition
          eulerRotation: cameraRotation
          fieldOfView: fov
      }

      DirectionalLight {
          id: light
          position: lightPosition
          eulerRotation: lightRotation
      }

      Repeater3D {
          model: scenePhys.getBoxes()
          Model {
              position: modelData.position
              rotation: model.rotation
              scale: Qt.vector3d(0.01, 0.01, 0.01)
              source: "#Cube"

              materials: [ DefaultMaterial { diffuseColor: modelData.color }]
          }
      }

      Model {
          position: light.position
          rotation: light.rotation
          scale: Qt.vector3d(0.01, 0.01, 0.01)
          source: "#Cube"

          materials: [ DefaultMaterial {
                  diffuseColor: "yellow"
              }
          ]
      }

//      Model {
//          position: Qt.vector3d(0, 150, 0)
//          source: "#Sphere"


//          materials: [ DefaultMaterial {
//                  diffuseColor: "blue"
//              }
//          ]

//          SequentialAnimation on y {
//              loops: Animation.Infinite
//              NumberAnimation {
//                  duration: 3000
//                  to: -150
//                  from: 150
//                  easing.type:Easing.InQuad
//              }
//              NumberAnimation {
//                  duration: 3000
//                  to: 150
//                  from: -150
//                  easing.type:Easing.OutQuad
//              }
//          }
//      }
    }

}

