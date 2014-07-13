import QtQuick 2.2
import FeatherViewport 1.0

Rectangle {
    anchors.fill: parent
    color: "orange"
    border.color: "black"
    border.width: 1

    Viewport {
        id: renderer
        anchors.fill: parent
        anchors.margins: 2

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: false

            onClicked: { renderer.mousePressed(mouse.x,mouse.y) }
            onPositionChanged: { renderer.moveCamera(mouse.x,mouse.y) }
            //onReleased: { console.log("released") }
            onWheel: { console.log("wheel") }
        }
    }

}
