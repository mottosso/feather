/***********************************************************************
 *
 * Filename: SceneGraphConnection.qml 
 *
 * Description: This is the link between scenegraph fields. 
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
import QtQuick 2.5

Rectangle {
    id: connection
    color: "darkgrey"
    height: 10
    width: 100
    radius: 2

    property alias name: label.text
    property int fid: 0
    property bool locked: false
    property int direction: 0 // 0=input, 1=output

    Rectangle {
        id: connector
        width: 10
        height: 10 
        anchors.verticalCenter: parent.verticalCenter
        color: "blue"
        border.width: 1
        border.color: "black"

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onEntered: { connection.state = "Hover" }
            onExited: { connection.state = "Normal" }
        }
    }

    Text {
        id: label 
        color: "black"
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: false 
        font.pixelSize: 10
    }

    states: [
        // NORMAL 
        State {
            name: "Normal"
            PropertyChanges {
                target: connection 
                color: "lightgrey"
            }

            PropertyChanges {
                target: connector 
                color: "lightblue"
            }
        },

        // HOVER 
        State {
            name: "Hover"
            PropertyChanges {
                target: connection 
                color: "lime"
            }

            PropertyChanges {
                target: connector 
                color: "darkblue"
            }
        }
    ]


    Component.onCompleted: {
        if(!direction) {
            connector.anchors.right = connection.left
        } else {
            connector.anchors.left = connection.right
        }
    
        state = "Normal"
    } 
}
