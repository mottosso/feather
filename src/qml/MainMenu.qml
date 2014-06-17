import QtQuick 2.2

Item {
    height: 32
    width: 200

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
