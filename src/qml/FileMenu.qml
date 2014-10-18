import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.0 

Menu {

    FileDialog {
        id: importDialog
        title: "Import Obj"
        
    }

    id: fileMenu 
    title: "File"
    visible: true
    Menu {
        id: importMenu
        title: "Import"
        MenuItem {
            id: importObj
            text: "Obj"
            onTriggered: { importDialog.visible=true }
        }
    }
}
