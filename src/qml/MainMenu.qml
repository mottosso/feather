import QtQuick 2.2

Item {
    height: 32
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right

    MenuBar { 
        anchors.fill: parent
       
        Row {
            spacing: 4 
            anchors.top: parent.top
            anchors.bottom: parent.bottom

        MenuItem {
            id: filemenu
            title: "File"
        } 

        MenuItem {
            id: editmenu
            title: "Edit"
        } 


        }

    }
}
