/***********************************************************************
 *
 * Filename: MenuButton.qml 
 *
 * Description: Used in menus to select items. 
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

import QtQuick 2.1

Rectangle {
    id: button

    property alias label: label.text

    height: 20
    width: parent.width
    color: "lightgrey"
    border.color: "black"
    border.width: 1
    radius: 2

    Text {
        id: label
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        //font.bold: true 
        font.pixelSize: 12
        color: "black"
    }

    states: [

        // NORMAL
        State {
            name: "normal"
            PropertyChanges {
                target: button 
                color: "lightgrey"
            }
        },

        // HOVER
        State {
            name: "hover"
            PropertyChanges {
                target: button 
                color: "lightblue"
            }
        },

        // PRESSED  
        State {
            name: "pressed"
            PropertyChanges {
                target: button 
                color: "green"
            }
        }

    ]


    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true 
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onPressed: {
            if(mouse.button == Qt.RightButton)
                popup.popup()

            intField.state="pressed"
            intField.update()
        }

        //onPositionChanged: { }
        onReleased: { button.state="normal" }
        onEntered: { button.state="hover" }
        onExited: { button.state="normal" }
    }

    Component.onCompleted: {
        button.state="normal" 
    }

}
