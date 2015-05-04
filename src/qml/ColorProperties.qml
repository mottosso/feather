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
    id: colorProperties
    title: "Color Properties"
    width: 500
    height: 400
    visible: true
    color: "grey"

    GridLayout {
        //anchors.fill: parent
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        //width: parent.width
        rows: 20
        columns: 3

        ColorProperty { id: windowBgProp; label: "Window BG"; color: "grey" }
        ColorProperty { id: boolTypeProp; label: "Boolean Type"; color: "lightblue" }
        ColorProperty { id: intTypeProp; label: "Int Type"; color: "lightgreen" }
        ColorProperty { id: meshTypeProp; label: "Mesh Type"; color: "pink" }

    } 

    Component.onCompleted: {}
}
