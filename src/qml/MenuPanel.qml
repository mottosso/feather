import QtQuick 2.2

Rectangle {
    id: panel
    width: 150
    height: 200
    color: "lightgrey"
    radius: 4
    border.color: "black"
    border.width: 1
    y: 24
    
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true
        onEntered: { panel.visible = true }
        onExited: { console.log("exit"); panel.visible = false }
    }

    Component.onCompleted: { panel.visible = false }
}
