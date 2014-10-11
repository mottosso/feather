import QtQuick 2.1

Rectangle {
    height: 32
    width: parent.width
    color: "lightgrey"
    border.color: "black"
    border.width: 1
    radius: 4
 
    Text {
        anchors.fill: parent
        anchors.margins: 4
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter 
        text: "Feather"
        color: "black"
    }
 
}
