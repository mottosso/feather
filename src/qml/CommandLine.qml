/***********************************************************************
 *
 * Filename: CommandLine.qml 
 *
 * Description: Command line and return messages.
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
import feather.command 1.0

Rectangle {
    id: cmdlineEditor
    color: "grey"
    border.color: "black"
    border.width: 1
    width: 500
    height: 20

    Item {
        anchors.fill: parent

        // Command Line
        Rectangle {
            id: cmdBgId
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: parent.width/2
            color: "white"
            border.color: "black"
            border.width: 1
            radius: 2
            anchors.margins: 2

            TextInput {
                id: cmdId
                color: "black"
                anchors.fill: parent
                cursorVisible: true
                font.pixelSize: 16
            }
        }

        // Message Box
        Rectangle {
            id: msgBgId
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: cmdBgId.right
            color: "darkred"
            border.color: "black"
            border.width: 1
            radius: 2
            anchors.margins: 2

            TextInput {
                id: msgId
                color: "yellow"
                anchors.fill: parent
                cursorVisible: true
                font.pixelSize: 16
            }
        }

    }
}
