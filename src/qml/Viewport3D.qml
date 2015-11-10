/***********************************************************************
 *
 * Filename: Viewport3D.qml 
 *
 * Description: Holds the C++ viewport. 
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
import feather.viewport 1.0
import feather.scenegraph 1.0

Rectangle {
    color: "orange"
    border.color: "black"
    border.width: 1
    property alias showAxis: renderer.axis
    property alias showGrid: renderer.grid
    property alias shadingMode: renderer.shadingMode
    property alias selectionMode: renderer.selectionMode
    //focus: true   
   
    Viewport {
        id: renderer
        anchors.fill: parent 
        anchors.margins: 2
        //focus: true

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: false 
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onPressed: {
                if(mouse.button == Qt.RightButton)
                    main_popup.popup();

                renderer.mousePressed(mouse.x,mouse.y)

            }
            onPositionChanged: { renderer.rotateCamera(mouse.x,mouse.y) }
            //onReleased: { console.log("released") }
            onWheel: { renderer.zoomCamera(wheel.angleDelta.y) }
            onEntered: { renderer.focus = true }
        }

        Keys.onPressed: {
            switch(event.key){
                case Qt.Key_Up:
                    renderer.moveCamera(0,-1,0);
                    event.accepted = true;
                    break
                case Qt.Key_Down:
                    renderer.moveCamera(0,1,0);
                    event.accepted = true;
                    break
                case Qt.Key_Left:
                    renderer.moveCamera(1,0,0);
                    event.accepted = true;
                    break
                case Qt.Key_Right:
                    renderer.moveCamera(-1,0,0);
                    event.accepted = true;
                    break
            }
            updateGL()
            //update()
        }

        MainPopup { id: main_popup; visible: true }
    }

    // info box for top right corner
    Rectangle {
        id: infoBox
        anchors.top: parent.top
        anchors.right: parent.right
        color: "#33000000"
        width:  100 
        height: 58 

        Column {
            anchors.fill: parent
            anchors.margins: 4
            spacing: 4

            Text {
                id: selectedLabel
                width: parent.width
                height: 14
                visible: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 12
                font.bold: false
                text: "Selected Item" 
            }

            Text {
                id: selectedNameLabel
                width: parent.width
                height: 14
                visible: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 12
                font.bold: false
                text: "Name: ---" 
            }

            Text {
                id: selectedUidLabel
                width: parent.width
                height: 14
                visible: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 12
                font.bold: false
                text: "UID: ---" 
            }

        }
    }

    function nodeAdded(uid) { console.log("node " + uid + " added"); renderer.nodeInitialize(uid) }

    function nodesAdded() { renderer.nodesAdded() }

    function nodesRemoved() { renderer.nodesRemoved() }

    function updateGL() { renderer.updateGL() }

    function updateSelectionInfo(uid) {
        selectedNameLabel.text = "Name: " + SceneGraph.node_name(uid)
        selectedUidLabel.text = "UID: " + uid
    }

    Component.onCompleted: {
        SceneGraph.nodeAdded.connect(nodeAdded)
        SceneGraph.nodesAdded.connect(nodesAdded)
        SceneGraph.nodesRemoved.connect(nodesRemoved)
        SceneGraph.updateGraph.connect(updateGL)
        SceneGraph.nodeSelected.connect(updateSelectionInfo)
        renderer.updateGL()
    }
}
