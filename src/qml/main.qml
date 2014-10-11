import QtQuick 2.2

Rectangle {
    width: 800
    height: 600
    color: "lightgrey"

    MainMenu {
        id: menu
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    MainToolBar {
        id: toolbar
        anchors.top: menu.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }

    OutlinerWindow {
        id: outliner
        anchors.top: toolbar.bottom
        anchors.right: parent.right
        width: 200
        height: parent.height/2
    }

    StatusBar {
        id: statusbar
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
 
    MaterialWindow {
        id: material 
        anchors.top: outliner.bottom
        anchors.right: parent.right
        anchors.bottom: statusbar.top
        width: 200
    }

    Item {
        anchors.top: toolbar.bottom
        anchors.left: parent.left
        anchors.right: outliner.left
        anchors.bottom: statusbar.top
 
        Viewport3D { anchors.fill: parent }
    }

}
