import QtQuick 2.2

Rectangle {
    id: node
    width: 70
    height: 100
    color: "indigo"
    border.color: "white"
    border.width: 1
    radius: 4
    property alias label: label.text

    signal moved(int x, int y)

    Text {
        id: label
        anchors.margins: 2
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignHCenter
        height: 10
        font.pixelSize: 10
        font.bold: true
        color: "white"
        text: node.label
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        hoverEnabled: false
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        property int x_offset: 0
        property int y_offset: 0

        onPressed: {
            x_offset = mouse.x;
            y_offset = mouse.y;
        }

        onPositionChanged: {
            node.x = node.x + (mouse.x - x_offset)
            node.y = node.y + (mouse.y - y_offset)
            node.moved(node.x, node.y)
        }
 
    }

    Component.onCompleted: { node.moved(node.x, node.y) }
}
