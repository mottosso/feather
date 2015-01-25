import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: window
    width: 1200
    height: 700
    visible: true

    title: "Feather 0.1"

    menuBar: MainMenu {}

    toolBar: MainToolBar {}

    statusBar: StatusBar {
        RowLayout { BusyIndicator { implicitWidth: 10; implicitHeight: 10; running: true } Label { text: "Feather 0.1" } }
    }


    //Outliner {}


    SplitView {
        id: splitView
        anchors.fill: parent
        orientation: Qt.Horizontal

        Viewport3D {
            id: vp3d
            Layout.fillWidth: true
        }

        SceneGraphEditor {
            id: sgEditor
            width: 300
        }

    }

    //Material {}
}
