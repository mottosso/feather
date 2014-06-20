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

}
