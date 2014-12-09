import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.0 

MenuItem {

    FileDialog {
        id: importDialog
        title: "Import Obj"
        onAccepted: {
            console.log("picked: " + importDialog.fileUrls)
        }
        onRejected: {} 
    }

    action: Action {
        id: importObjAction
        text: "Obj"
        tooltip: "Import models in the Obj format"
        onTriggered: {}
    }

}
