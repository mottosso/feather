import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.0 
import "actions"

Menu {

    FileDialog {
        id: importDialog
        title: "Import Obj"
        onAccepted: {
            console.log("picked: " + importDialog.fileUrls)
        }
        onRejected: {} 
    }

    id: fileMenu 
    title: "File"
    visible: true


    // New 
    MenuItem {
        id: new 
        text: "New"
        onTriggered: { }
    }

    // Import Menu
    Menu {
        id: importMenu
        title: "Import"

        // Obj
        MenuItem {
            id: importObj
            text: "Obj"
            onTriggered: { importDialog.visible=true }
        }

    }

    MenuSeparator {}

    MenuItem {
        text: "Close"
        onTriggered: { Qt.quit() }
    }
}
