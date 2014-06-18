import QtQuick 2.2
import QtQuick.Window 2.1

Rectangle {
    id: main
    width: 400
    height: 540
    color: "darkgrey"

    MainMenu {
        id: mainmenu
        
    }

    Popup {
        id: popup
        //width: 100
        //height: 200
        //anchors.top: parent.top
        //anchors.left: parent.left
    }

    Window {
         title: "Viewport"
        flags: Qt.Window // Window, Dialog, Popup, SubWindow, Tool, ToolTip, SplashScreen
        width: 500
        height: 500
        x: 100
        y: 100
        visible: true
         
     Viewport3D {
            anchors.fill: parent 
        } 

    }

}
