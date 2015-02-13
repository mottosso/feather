import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    id: sgEditor 
    title: "SceneGraph Editor"
    visible: true
    flags: Qt.Tool
    width: 400
    height: 500

    SceneGraphEditor {
        id: sg
        anchors.fill: parent
    }

}
