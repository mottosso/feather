import QtQuick 2.2
//import QtQuick.Window 2.0
//import QtQuick.Dialogs 1.1
import QtQuick.Controls 1.2
//import QtQuick.Controls.Styles 1.0
//import QtQuick.Layouts 1.1

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

        // splash screen
        //Window { id: splash; width: 600; height: 347; visible: true; flags: Qt.SplashScreen; Image { anchors.fill: parent; source: "./icons/splash.jpg" } }

        menuBar: MainMenu {}

        toolBar: MainToolBar {}

        statusBar: StatusBar { id: status_bar; Label { text: "Welcome to " + root.software + " v" + root.version } }

        Viewport3D {
            anchors.fill: parent
        }

        SceneGraph {}

        Component.onCompleted: { }


    }

}
