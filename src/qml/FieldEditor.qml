import QtQuick 2.3
import QtQuick.Window 2.2
import feather.scenegraph 1.0

Window {
    id: fieldEditor 
    title: "FieldEditor"
    visible: true
    flags: Qt.Tool
    width: 300
    height: 500

    SceneGraph { id: sg }

    Rectangle {
        id: frame
        anchors.fill: parent
        border.color: "black"
        border.width: 2
        color: "grey"
 
        // Node Title
        Rectangle {
            id: nodeTitle
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 25
            border.color: "black"
            border.width: 2
            radius: 2
            color: "lightgrey"
 
            Text {
                id: nodeLabel
                text: "cube01"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: false 
                font.pixelSize: 20
                color: "black"
            }
        }
 
        Column {
            spacing: 2
            anchors.top: nodeTitle.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 2

            IntField {
                id: test1
                width: parent.width
                label: "subX"
            }

            IntField {
                id: test2
                width: parent.width
                label: "subY"
            }
        }
    }
 
    Component.onCompleted: {
        
    }    
}
