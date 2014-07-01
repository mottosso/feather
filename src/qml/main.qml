import QtQuick 2.2
import QtQuick.Window 2.1


Rectangle {
    id: main
    width: 1024
    height: 780
    color: "darkgrey"

    Viewport3D {
        anchors.top: toolbar.bottom
        anchors.bottom: statusbar.top
        anchors.left: parent.left
        anchors.right: parent.right
    }
    
    MainMenu {
        id: mainmenu
        //height: 25
    }

    ToolBar {
        id: toolbar
        anchors.top: mainmenu.bottom
    }

    Rectangle {
        id: statusbar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 28
        color: "grey"
        border.color: "black"
        border.width: 1
        
        Text {
            text: "feedback goes here"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.margins: 4
        } 
    }

    Outliner {
        id: outliner
    }
}
