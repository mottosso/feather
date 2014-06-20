import QtQuick 2.2
import QtQuick.Window 2.1

Rectangle {
    id: main
    width: 1024
    height: 780
    color: "darkgrey"

    Viewport3D {
        width: 500
        height: 500
        x: 100
        y: 100
    }
    
    MainMenu { id: mainmenu }

    Popup {
        id: popup
        //width: 100
        //height: 200
        //anchors.top: parent.top
        //anchors.left: parent.left
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 28
        color: "grey"
        border.color: "black"
        border.width: 1
        radius: 2
        
        Text {
            text: "feedback goes here"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.margins: 4
        } 
    }
}
