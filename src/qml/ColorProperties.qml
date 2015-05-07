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
import QtQuick.Layouts 1.1


Rectangle {
    id: colorProperties
    visible: true
    color: "grey"
    property Properties properties: Null

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
            height: rows * 20
            rows: 2 
            columns: 4

            ColorProperty { properties: colorProperties.properties; width: 130; name: "windowBg"; label: "Window BG" }
            ColorProperty { properties: colorProperties.properties; width: 130; name: "panel"; label: "Panel" }
            ColorProperty { properties: colorProperties.properties; width: 130; name: "labelBg"; label: "Label BG" }
            ColorProperty { properties: colorProperties.properties; width: 130; name: "label"; label: "Label" }
            ColorProperty { properties: colorProperties.properties; width: 130; name: "textBg"; label: "Text BG" }
            ColorProperty { properties: colorProperties.properties; width: 130; name: "text"; label: "Text" }

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
                text: "TYPES"
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
            height: rows * 20 
            rows: 2 
            columns: 4

            ColorProperty { properties: colorProperties.properties; name: "boolType"; label: "Boolean" }
            ColorProperty { properties: colorProperties.properties; name: "intType"; label: "Int" }
            ColorProperty { properties: colorProperties.properties; name: "floatType"; label: "Float" }
            ColorProperty { properties: colorProperties.properties; name: "doubleType"; label: "Double" }
            ColorProperty { properties: colorProperties.properties; name: "vertexType"; label: "Vertex" }
            ColorProperty { properties: colorProperties.properties; name: "meshType"; label: "Mesh" }
            ColorProperty { properties: colorProperties.properties; name: "rgbType"; label: "RGB" }
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
                text: "NODES"
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
            height: rows * 20 
            rows: 1 
            columns: 4

            ColorProperty { properties: colorProperties.properties; name: "cameraNode"; label: "Camera" }
            ColorProperty { properties: colorProperties.properties; name: "lightNode"; label: "Light" }
       } 

    }

    Component.onCompleted: { }
}
