import QtQuick 2.3
import QtQuick.Dialogs 1.2
import QtQml.Models 2.1

Item {

    FileDialog {
        id: open_dialog
        title: "please select file"

        onAccepted: {
            console.log("file=" + open_dialog.fileUrls)
            //Qt.quit()
            close()
        }

        onRejected: {
            //Qt.quit()
            close()
        }

        Component.onCompleted: {
            visible = false 
        }
    }

    ListModel {
        id: fileModel
        
        ListElement {
            name: "File"
            //action: { console.log("file clicked") }
        }
        
        ListElement {
            name: "Open"
            //action: { console.log("open clicked") }
        }

    }

        
    MenuPanel {
        id: menu
        model: fileModel 
    }

    /*
    Column {
    spacing: 2

    MenuItem {
        id: open
        label: "File"
    }

    MenuItem {
        id: save 
        label: "Save"
    }

    }

    function open_file() {
        console.log("open file")
        open_dialog.open()
    }

    Component.onCompleted: { open.triggered.connect(open_file) }
    */
}
