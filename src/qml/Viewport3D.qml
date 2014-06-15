import QtQuick 2.0
import FeatherViewport 1.0

Rectangle {
    id: view3d
    border.color: "yellow"
    border.width: 2
    color: "darkgrey"

    anchors.fill: parent

    Viewport {
        id: renderer
        anchors.fill: parent
        anchors.margins: 10

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: false

            onClicked: {}
        }

    }

}
