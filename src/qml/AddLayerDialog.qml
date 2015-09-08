/***********************************************************************
 *
 * Filename: AddLayerDialog.qml 
 *
 * Description: Dialog to add a new layer to the layer editor.
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
import feather.layer 1.0
import QtQuick.Controls 1.4
//import QtQuick.Dialogs 1.2

Window {
    id: editor 
    title: "Add Layer"
    visible: false 
    flags: Qt.Tool
    width: 300
    height: 40
    property Properties properties: Null

    color: properties.getColor("windowBg")

    signal addLayer(string name)

    Action {
        id: addLayerAction
        text: "Add Layer"
        tooltip: "Add layer bar to the layer editor"
        onTriggered: { addLayer(labelEdit.text); editor.visible=false }
    }


    Item {
        anchors.fill: parent
        anchors.margins: 4

    Column {
        spacing: 4

        Row {
            spacing: 4

            Text {
                id: label
                height: 20
                width: 140 
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 14
                font.bold: false
                text: "Layer Name:" 
            }

            TextField {
                id: labelEdit
                readOnly: false
                height: 20
                width: 140 
            }
        }

 
        Row {
            spacing: 4
 
            PushButton {
                id: cancelButton
                text: "Cancel"
                properties: editor.properties
                action: Action {
                    onTriggered: { editor.visible=false }
                }
            }
            
            PushButton {
                id: okButton
                text: "Ok"
                properties: editor.properties
                action: addLayerAction
            }

        }

    }

    }

    //onAccepted: { add_layer() }

    /*
    function add_layer(){
        addLayer(labelEdit.text)
    }
    */

    /*
    function updateColor(){
        editor.color = properties.getColor("windowBg")
    }

    Component.onCompleted: {
        //accepted.connect(add_layer)
        updateColor()
        properties.colorsChanged.connect(updateColor)
    }
    */
}
