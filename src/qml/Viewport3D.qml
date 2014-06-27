import QtQuick 2.2
import FeatherViewport 1.0

Rectangle {
    width: 500
    height: 500
    color: "yellow"
    border.color: "black"
    border.width: 1
    radius: 4

    Viewport {
        id: renderer
        anchors.fill: parent
        anchors.margins: 4

        /*
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: false

            onClicked: {}
        }
        */
    }

}
