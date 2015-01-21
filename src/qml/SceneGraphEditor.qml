import QtQuick 2.3
import QtQuick.Window 2.2
import feather.editors 1.0

Window {
    id: outliner
    title: "SceneGraph"
    visible: true
    flags: Qt.Tool
    width: 800
    height: 600

    SceneGraphEditor {
        id: sg_editor
        anchors.fill: parent
        //width: 200
        //height: 200
    }    

    Component.onCompleted: {
        sg_editor.update_sg()
    }
}
