import QtQuick 2.2
import QtQuick.Dialogs 1.2

MenuPanel {

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
}
