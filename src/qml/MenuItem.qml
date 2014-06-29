import QtQuick 2.2

Item {
    property alias title: label.text 
    width: 100
    height: 32
     
    // Title
    Rectangle {
        id: background
        color: "grey"
        anchors.fill: parent
        anchors.margins: 2
        radius: 4
    }

    Text {
        id: label
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        color: "black"
    }

    // SubMenu

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onClicked: console.log("clicked")
        onEntered: background.color = "lightgrey"
        onExited: background.color = "grey"

    }

}
