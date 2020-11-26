import QtQuick 2.14
import QtQuick3D 1.15

Item {
    Text {
        text: "Multisample: " + ["NoAA", "SSAA", "MSAA", "ProgressiveAA"][scene3d.environment.antialiasingMode]
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

        MouseArea {
            anchors.fill: parent
            onClicked: scene3d.environment.antialiasingMode < 3
                       ? scene3d.environment.antialiasingMode++
                       : scene3d.environment.antialiasingMode = 0
        }
    }

    Rectangle {
        id: scene
        anchors.fill: parent
        anchors.margins: 50
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
            color: "skyblue"
        }
    }

    Rectangle {
        radius: 10
        color: "#44ffffff"
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

            Text { text: "Vendor: " + scene3d.environment. capabilities.vendor }
            Text { text: "Renderer: " + rootEntity.capabilities.renderer }
            Text { text: "Driver Version: " + rootEntity.capabilities.driverVersion }
            Text { text: "GL Version: " + rootEntity.capabilities.majorVersion + "." + rootEntity.capabilities.minorVersion }
            Text { text: "Profile: " + (rootEntity.capabilities.profile === RenderCapabilities.CoreProfile ? "Core" : (rootEntity.capabilities.profile === RenderCapabilities.CompatibilityProfile ? "Compatibility" : "Unknown")) }
            Text { text: "GLSL Version: " + rootEntity.capabilities.glslVersion }
            Text { text: "Extensions: " + (rootEntity.capabilities.extensions.length ? "" : "None") }
            ListView {
                model: rootEntity.capabilities.extensions
                delegate: Text { text: "  " + model.modelData }
                width: parent.width
                height: 100
                visible: rootEntity.capabilities.extensions.length > 0
                clip: true
            }
            Text { text: "Max Texture Size: " + rootEntity.capabilities.maxTextureSize + "\nMax Texture Units: " + rootEntity.capabilities.maxTextureUnits + "\nMax Texture Layers: " + rootEntity.capabilities.maxTextureLayers }
            Text { text: "Supports UBO: " + rootEntity.capabilities.supportsUBO }
            Text { text: "  Max UBO Size: " + rootEntity.capabilities.maxUBOSize + "\n  Max UBO Bindings: " + rootEntity.capabilities.maxUBOBindings; visible: rootEntity.capabilities.supportsUBO }
            Text { text: "Supports SSBO: " + rootEntity.capabilities.supportsSSBO }
            Text { text: "  Max SSBO Size: " + rootEntity.capabilities.maxSSBOSize + "\n  Max SSBO Bindings: " + rootEntity.capabilities.maxSSBOBindings; visible: rootEntity.capabilities.supportsSSBO }
            Text { text: "Supports Image Store: " + rootEntity.capabilities.supportsImageStore }
            Text { text: "  Max Image Units: " + rootEntity.capabilities.maxImageUnits; visible: rootEntity.capabilities.supportsImageStore }
            Text { text: "Supports Compute Shaders: " + rootEntity.capabilities.supportsCompute }
            Text { text: "  Max Work Group Size: " + rootEntity.capabilities.maxWorkGroupSizeX + ", " + rootEntity.capabilities.maxWorkGroupSizeY + ", " + rootEntity.capabilities.maxWorkGroupSizeZ; visible: rootEntity.capabilities.supportsCompute }
            Text { text: "  Max Work Group Count: " + rootEntity.capabilities.maxWorkGroupCountX + ", " + rootEntity.capabilities.maxWorkGroupCountY + ", " + rootEntity.capabilities.maxWorkGroupCountZ; visible: rootEntity.capabilities.supportsCompute }
            Text { text: "  Max Invocations: " + rootEntity.capabilities.maxComputeInvocations; visible: rootEntity.capabilities.supportsCompute }
            Text { text: "  Max Shared Memory: " + rootEntity.capabilities.maxComputeSharedMemorySize; visible: rootEntity.capabilities.supportsCompute }
        }
    }
}
