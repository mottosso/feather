/***********************************************************************
 *
 * Filename: "Properties".qml 
 *
 * Description: Holds all the properties for the UI.
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

Item {
    id: properties
   
    signal colorsChanged()
 
    ListModel {
        id: colorProperties
        // UI
        ListElement { name: "windowBg"; color: "#848482" }
        ListElement { name: "textBg"; color: "#F0F8FF" }
        ListElement { name: "text"; color: "#000000" }
        ListElement { name: "panel"; color: "#303030" }
        ListElement { name: "labelBg"; color: "#F0F8FF" }
        ListElement { name: "label"; color: "#000000" }
        // TYPES
        ListElement { name: "boolType"; color: "#008080" }
        ListElement { name: "intType"; color: "#E2725B" }
        ListElement { name: "floatType"; color: "#318CE7" }
        ListElement { name: "doubleType"; color: "#FCF75E" }
        ListElement { name: "vertexType"; color: "#FF7F00" }
        ListElement { name: "meshType"; color: "#FF007F" }
        ListElement { name: "rgbType"; color: "#EDC9AF" }
        // NODES
        ListElement { name: "cameraNode"; color: "#0F4D92" }
        ListElement { name: "lightNode"; color: "#EDC9AF" }
    }

    Component.onCompleted: {}

    function loadProperties() {
        colorsChanged()
    }

    function saveProperties() {

    }

    function getColor(name) {
        for(var i=0; i < colorProperties.count; i++) {
            if(colorProperties.get(i).name==name)
                return colorProperties.get(i).color
        }
        return "#FFFFFF"
    }

    function setColor(name,color) {
        for(var i=0; i < colorProperties.count; i++) {
            if(colorProperties.get(i).name==name)
                colorProperties.get(i).color=color
        }
        colorsChanged()
    }

}
