/***********************************************************************
 *
 * Filename: ColorProperties.qml 
 *
 * Description: Container for all the application color properties.
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
import QtQuick.Layouts 1.1


Window {
    id: colorWindow
    title: "Color Properties"
    width: 500
    height: 400
    visible: true
    color: "grey"

    Item {
        id: colorProperties
        anchors.fill: parent
        anchors.margins: 4

    Column {
        spacing: 10

        // UI 

        Rectangle {
            width: colorProperties.width
            height: 16
            color: "lightgrey" 
            border.color: "black"
            border.width: 1
            radius: 2
            
            Text {
                text: "UI"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: false 
                font.pixelSize: 12
                color: "black"
            }
        }

        GridLayout {
            width: colorProperties.width
            height: 1 * windowBgProp.height
            rows: 1 
            columns: 3

            ColorProperty { id: windowBgProp; label: "Window Main"; color: "grey" }
            ColorProperty { id: textBgProp; label: "Window Trim"; color: "limegreen" }
            ColorProperty { id: textColorProp; label: "Window Trim"; color: "black" }

        } 

        // TYPES

        Rectangle {
            width: colorProperties.width
            height: 16
            color: "lightgrey" 
            border.color: "black"
            border.width: 1
            radius: 2
            
            Text {
                text: "Types"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: false 
                font.pixelSize: 12
                color: "black"
            }
        }

        GridLayout {
            width: colorProperties.width
            height: 6 * windowBgProp.height
            rows: 6 
            columns: 3

            ColorProperty { id: boolTypeProp; label: "Boolean Type"; color: "#008080" }
            ColorProperty { id: intTypeProp; label: "Int Type"; color: "#E2725B" }
            ColorProperty { id: floatTypeProp; label: "Float Type"; color: "#318CE7" }
            ColorProperty { id: doubleTypeProp; label: "Double Type"; color: "#FCF75E" }
            ColorProperty { id: vertexTypeProp; label: "Vertex Type"; color: "#FF7F00" }
            ColorProperty { id: vectorTypeProp; label: "Vector Type"; color: "#00CC99" }
            ColorProperty { id: meshTypeProp; label: "Mesh Type"; color: "#FF007F" }
            ColorProperty { id: rgbTypeProp; label: "RGB Type"; color: "#EDC9AF" }
            ColorProperty { id: rgbaTypeProp; label: "RGBA Type"; color: "#FF7F50" }
            ColorProperty { id: boolArrayTypeProp; label: "Bool Array Type"; color: "#FFA812" }
            ColorProperty { id: intArrayTypeProp; label: "Int Array Type"; color: "#966FD6" }
            ColorProperty { id: floatArrayTypeProp; label: "Float Array Type"; color: "#D1E231" }
            ColorProperty { id: vertexArrayTypeProp; label: "Vertex Array Type"; color: "#B39EB5" }
            ColorProperty { id: vectorArrayTypeProp; label: "Vector Array Type"; color: "#69359C" }
            ColorProperty { id: rgbArrayTypeProp; label: "RGB Array Type"; color: "#87CEEB" }
            ColorProperty { id: rgbaArrayTypeProp; label: "RGBA Array Type"; color: "#0F4D92" }
        } 

    }

    }

    Component.onCompleted: {}
}
