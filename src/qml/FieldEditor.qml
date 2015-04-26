/***********************************************************************
 *
 * Filename: FieldEditor.qml 
 *
 * Description: Container for node editor dialogs.
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
import feather.scenegraph 1.0
import feather.field 1.0

Window {
    id: fieldEditor 
    title: "FieldEditor"
    visible: true
    flags: Qt.Tool
    width: 200
    height: 500
    color: "dimgrey"
    property SceneGraph scenegraph: Null

    FieldModel { id: fieldModel }

    Rectangle {
        id: nodeFrame
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height/2
        anchors.margins: 1
        border.color: "black"
        border.width: 1
        color: "grey"
        radius: 2
 
        // Node Title
        Rectangle {
            id: nodeTitle
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 15
            border.color: "black"
            border.width: 1
            radius: 2
            color: "lightgrey"
 
            Text {
                id: nodeLabel
                text: "cube01"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: false 
                font.pixelSize: 12
                color: "black"
            }
        }

        ListView {
            spacing: 2
            anchors.top: nodeTitle.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 1
            model: fieldModel

            delegate: IntField {
                width: parent.width
                uId: uid
                nodeKey: nid
                fieldKey: fid
                label: "***" 
            }
        }

    }
 
    Rectangle {
        id: baseFrame
        anchors.top: nodeFrame.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 1
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
            height: 15
            border.color: "black"
            border.width: 1
            radius: 2
            color: "slategrey"
 
            Text {
                id: nodeBaseLabel
                text: "cube01->Base"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: false 
                font.pixelSize: 12
                color: "black"
            }
        }

    }
        
 
    Component.onCompleted: {
        scenegraph.selectionChanged.connect(setSelection)        
        scenegraph.nodeSelection.connect(nodeSelect)
    }    

    function setSelection(type,uid,nid,fid) {
        console.log("fed triggered");
        console.log("field editor triggered for uid " + uid + " nid " + nid + " fid " + fid);
        fieldModel.addField(uid,nid,fid,0,false)
        fieldModel.layoutChanged()
    }

    function nodeSelect(type,uid,nid) {
        fieldModel.addFields(uid,nid)
    }
}
