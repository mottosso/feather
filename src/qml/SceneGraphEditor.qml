import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import feather.editors 1.0

Rectangle {
    id: sgWindow
    color: "blue" 

    // Actions

    // Add Node 
    Action {
        id: addNode
        tooltip: "Add a node to the scenegraph"
        onTriggered: {}
    }

    // Delete Node 
    Action {
        id: deleteNode
        tooltip: "Remove selected node from scenegraph"
        onTriggered: {}
    }


    ToolBar {
        id: toolBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 36

        RowLayout {
            spacing: 6
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
             
            ToolButton {
                id: addNodeButton
                width: 32; height: 32
                iconSource: "/usr/local/feather/ui/icons/add_node.png"
                action: addNode 
            }

            ToolButton {
                id: deleteNodeButton
                width: 32; height: 23
                iconSource: "/usr/local/feather/ui/icons/delete_node.png"
                action: deleteNode 
            }

        }

    } 

    SceneGraphEditor {
        id: sg_editor
        anchors.top: toolBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 2
    }    

    Component.onCompleted: {
        sg_editor.update_sg()
    }
}
