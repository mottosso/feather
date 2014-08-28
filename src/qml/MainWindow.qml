import QtQuick 2.2
import QtQuick.Controls 1.2

Item {
    id: root

    property string software: "Feather"
    property real version: 0.1
    property string title: software + " v" + version

    ApplicationWindow {
        id: main_window
        //visibility: Window.Maximized
        width: 900
        height: 600
        visible: true
        title: "Feather"

        menuBar: MainMenu {}

        toolBar: MainToolBar {}

        statusBar: StatusBar { id: status_bar; Label { text: "Welcome to " + root.software + " v" + root.version } }

        Viewport3D {
            anchors.fill: parent
        }

        Component.onCompleted: { }
    }

}
