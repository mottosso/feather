import QtQuick 2.1
//import QtQuick.Window 2.1
//import QtQuick.Dialogs 1.0
//import QtQuick.Controls 1.0

Rectangle {
    id: menu
    height: 24
    color: "lightgrey"
    radius: 4
    border.color: "black"
    border.width: 1

    Row {
        spacing: 10

        Text {
            width: contentWidth + 10 
            height: menu.height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter 
            text: "File"
            color: "black"
        }

        Text {
            width: contentWidth + 10 
            height: menu.height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter 
            text: "Edit"
            color: "black"
        }


    }

    FileMenu {}
}

/*
MenuBar {

    // File Menu

    Menu {
        title: "File"
        MenuItem {
            text: "Open"
            shortcut: "Ctrl+O"
            onTriggered: {}            
        }

       MenuItem {
            text: "Save"
            shortcut: "Ctrl+S"
            onTriggered: { console.log("triggered") }
       }

       MenuSeparator {}

       Menu {
            title: "Import"

            MenuItem {
                text: "Obj"
                onTriggered: {}
           }

       }

       Menu {
            title: "Export"

            MenuItem {
                text: "Obj"
                onTriggered: {}
            }

            MenuItem {
                text: "Ply"
                onTriggered: {}
            }

       }

       MenuSeparator {}

       MenuItem {
            text: "Exit"
            shortcut: "Ctrl+S"
            onTriggered: { Qt.quit() }
       }

    }

    Menu {
        title: "Edit"
        MenuItem {
            text: "Undo/Redo"
            shortcut: "Ctrl+Z"
            onTriggered: {}
        }

        MenuItem {
            text: "Redo"
            shortcut: "Ctrl+Shift+Z"
            onTriggered: {}
        }

        MenuItem {
            text: "Undo"
            shortcut: "Alt+Ctrl+Z"
            onTriggered: {}
        }

       MenuSeparator {}

        MenuItem {
            text: "Purge Undo History"
            onTriggered: {}
        }
    }
}
*/

