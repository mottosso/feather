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

            ColorProperty { id: windowBgProp; name: "windowBg"; label: "Window Main" }
            ColorProperty { id: textBgProp; name: "textBg"; label: "Window Trim" }
            ColorProperty { id: textColorProp; name: "text"; label: "Window Trim" }
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

            ColorProperty { id: boolTypeProp; name: "boolType"; label: "Boolean Type" }
            ColorProperty { id: intTypeProp; name: "intType"; label: "Int Type" }
            ColorProperty { id: floatTypeProp; name: "floatType"; label: "Float Type" }
            ColorProperty { id: doubleTypeProp; name: "doubleType"; label: "Double Type" }
            ColorProperty { id: vertexTypeProp; name: "vertexType"; label: "Vertex Type" }
            ColorProperty { id: vectorTypeProp; name: "vectorType"; label: "Vector Type" }
            ColorProperty { id: meshTypeProp; name: "meshType"; label: "Mesh Type" }
            ColorProperty { id: rgbTypeProp; name: "rgbType"; label: "RGB Type" }
            ColorProperty { id: rgbaTypeProp; name: "rgbaType"; label: "RGBA Type" }
            ColorProperty { id: boolArrayTypeProp; name: "boolArrayType"; label: "Bool Array Type" }
            ColorProperty { id: intArrayTypeProp; name: "intArrayType"; label: "Int Array Type" }
            ColorProperty { id: floatArrayTypeProp; name: "floatArrayType"; label: "Float Array Type" }
            ColorProperty { id: vertexArrayTypeProp; name: "vertexArrayType"; label: "Vertex Array Type" }
            ColorProperty { id: vectorArrayTypeProp; name: "vectorArrayType"; label: "Vector Array Type" }
            ColorProperty { id: rgbArrayTypeProp; name: "rgbArrayType"; label: "RGB Array Type" }
            ColorProperty { id: rgbaArrayTypeProp; name: "rgbaArrayType"; label: "RGBA Array Type" }
        } 

    }

    }

    Component.onCompleted: { }
}
