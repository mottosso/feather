import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.0 

Menu {

    /*
    FileDialog {
        id: importDialog
        title: "Import Obj"
        onAccepted: {
            console.log("picked: " + importDialog.fileUrls)
        }
        onRejected: {} 
    }
    */

    id: fileMenu 
    title: "File"
    visible: true


    // ACTIONS


    // New 
    Action {
        id: newAction
        text: "New"
        tooltip: "Clear the scene"
        onTriggered: {}
    }

    // Open
    Action {
        id: openAction
        text: "Open"
        tooltip: "Open feather model"
        onTriggered: {}
    }

    // Import Obj
    /*
    Action {
        id: importObjAction
        text: "Obj"
        tooltip: "Import models in the Obj format"
        onTriggered: {}
    }
    */

    // Close 
    Action {
        id: closeAction
        text: "Close"
        tooltip: "Close Feather"
        onTriggered: { Qt.quit() }
    }


    // MENU


    // New 
    MenuItem {
        action: newAction
    }

    // Open 
    MenuItem {
        action: openAction
    }

    MenuSeparator {}

    // Import Menu
    Menu {
        id: importMenu
        title: "Import"

        // Obj
        /*
        MenuItem {
            action: importObjAction
        }
        */

    }

    MenuSeparator {}

    // Close
    MenuItem {
        action: closeAction
    }
}
