import QtQuick 2.2

Rectangle {
    id: background
    color: "grey"
    //width: 100
    //height: 20
    //anchors.top: parent.top
    //anchors.bottom: parent.bottom
    //anchors.margins: 4
    property alias title: label.text 
    radius: 4

    Text {
        id: label
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        color: "black"
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onClicked: console.log("clicked")
        onEntered: background.color = "lightgrey"
        onExited: background.color = "grey"

    }
}
