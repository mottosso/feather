import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Dialogs 1.0
import QtQuick.Controls 1.0

MenuBar {

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
            onTriggered: { /*console.log("triggered")*/ }
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

}

