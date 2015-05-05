/***********************************************************************
 *
 * Filename: ColorProperty.qml 
 *
 * Description: Used to set the color of a property.
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
import QtQuick.Dialogs 1.2

Item {
    id: colorProperty
    width: 150
    height: 20
    property alias label: label.text
    property alias color: colorDialog.color

    ColorDialog { id: colorDialog; title: "Color Property" }

    Row {
        spacing: 10
        anchors.fill: parent

        Text {
            id: label
            width: colorProperty.width-colorBox.width
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.bold: false 
            font.pixelSize: 12
            color: "black"
        }

        Rectangle {
            id: colorBox
            width: 40
            height: colorProperty.height
            color: colorDialog.color
            border.color: "black"
            border.width: 1
            radius: 2
  
            MouseArea {
                id: mouseArea
                anchors.fill: parent

                onClicked: { colorDialog.visible=true; }
            }
        }
    }
    
    Component.onCompleted: {
        colorDialog.visible=false        
    }
}
