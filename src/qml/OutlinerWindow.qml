import QtQuick 2.2
//import QtQuick.Window 2.1

Rectangle {
    color: "lightgrey"
    radius: 4
    border.color: "black"
    border.width: 1

    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 24
        color: "grey"
        radius: 4
        border.color: "black"
        border.width: 1
 
        Text {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter 
            text: "Outliner"
            font.bold: true
            color: "black"
        }
    }

}
