import QtQuick 2.3
import QtQuick.Window 2.2
import feather.scenegraph 1.0

Window {
    id: fieldEditor 
    title: "FieldEditor"
    visible: true
    flags: Qt.Tool
    width: 200
    height: 500

    SceneGraph { id: sg }

    Rectangle {
        id: nodeFrame
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height/2
        anchors.margins: 2
        border.color: "black"
        border.width: 1
        color: "grey"
        radius: 4
 
        // Node Title
        Rectangle {
            id: nodeTitle
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 20
            border.color: "black"
            border.width: 1
            radius: 4
            color: "lightgrey"
 
            Text {
                id: nodeLabel
                text: "cube01"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: true 
                font.pixelSize: 16
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
                // Ok, this is dangerous because the program will seq fault.
                // This will need to be verified by the scenegraph
                // BUT.... for the time being this will do for testing
                uId: 0
                nodeKey: 322
                fieldKey: 1 
                label: "subX"
            }

        }


    }
 
    Rectangle {
        id: baseFrame
        anchors.top: nodeFrame.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 2
        border.color: "black"
        border.width: 1
        color: "darkgrey"
        radius: 4

        // Node Base Title
        Rectangle {
            id: nodeBaseTitle
            anchors.top: parent.top 
            anchors.left: parent.left
            anchors.right: parent.right
            height: 20
            border.color: "black"
            border.width: 1
            radius: 4
            color: "slategrey"
 
            Text {
                id: nodeBaseLabel
                text: "cube01->Base"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: true 
                font.pixelSize: 16
                color: "black"
            }
        }

    }
        
 
    Component.onCompleted: {
        
    }    
}
