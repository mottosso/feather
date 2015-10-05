/***********************************************************************
 *
 * Filename: AddNodeDialog.qml 
 *
 * Description: Dialog to add a new node to the scenegraph.
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
import QtQuick.Controls 1.4

Window {
    id: dialog
    title: "Add Node"
    width: 300
    height: 140
    modality: Qt.WindowModal
    flags: Qt.Dialog
    visible: false
    x: (Screen.desktopAvailableWidth - width)/2
    y: (Screen.desktopAvailableHeight - height)/2

    property Properties properties: Null

    color: properties.getColor("windowBg")

    Column {
        spacing: 4
        anchors.fill: parent
        
        // Name 
        Row {
            spacing: 4
            width: parent.width
             
            Text {
                id: nameLabel
                width: 70
                height: 30
                visible: true
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 14
                font.bold: false
                text: "Name" 
            }

            TextField {
                id: nameEdit
                width: 200
                height: 30
                visible: false
                readOnly: false
            }
        }

        // Type
        Row {
            spacing: 4
            width: parent.width

            Text {
                id: typeLabel
                width: 70
                height: 30
                visible: true
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 14
                font.bold: false
                text: "Type" 
            }
        
            OptionBox {
                id: typeOption
                width: 200
                height: 30
                model: NodeTypeModel{}
                properties: dialog.properties 
             }
        }        

        // Id 
        Row {
            spacing: 4
            width: parent.width

            Text {
                id: idLabel
                width: 70
                height: 30
                visible: true
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 14
                font.bold: false
                text: "Id" 
            }
        
            OptionBox {
                id: idOption
                width: 200
                height: 30
                // I need to make the NodeIdModel in C++
                //model: NodeTypeModel{}
                properties: dialog.properties 
             }
        }        

        Row {
            spacing: 4
            anchors.horizontalCenter: parent.horizontalCenter

            PushButton {
                id: cancelButton
                width: 100 
                height: 30
                text: "Cancel"
                properties: dialog.properties 
            }

            PushButton {
                id: acceptButton
                width: 100 
                height: 30
                text: "Accept"
                properties: dialog.properties 
            }
        }
    }

    function hide(){
        dialog.visible = false
    }

    function addNode(){

    }

    Component.onCompleted: {
        cancelButton.clicked.connect(hide)
        acceptButton.clicked.connect(addNode)
    }
}
