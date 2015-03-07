/***********************************************************************
 *
 * Filename: SceneGraphEditor.qml 
 *
 * Description: Holds the actual C++ scenegraph widget. 
 *
 * Copyright (C) 2015 Richard Layman, rlayman2000@yahoo.com 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

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

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            acceptedButtons: Qt.RightButton

            onClicked: { /*console.log("qml sg select")*/ }
        }
    }    

    Component.onCompleted: {
        sg_editor.update_sg()
    }
}
