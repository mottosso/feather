/***********************************************************************
 *
 * Filename: TimeSlider.qml 
 *
 * Description: Handles zooming in on the timeline. 
 *
 * Copyright (C) 2016 Richard Layman, rlayman2000@yahoo.com 
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
    id: slider 
    color: "darkgrey"
    border.width: 1
    radius: 2

    width: 500
    height: 20

    Rectangle {
        id: viewable
        color: "lightgrey"
        border.width: 1
        radius: 5
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        x: 100
        width: 800

        Rectangle {
            id: viewable_start
            color: "blue"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 4
            border.width: 1
            width: height
            radius: height/2
        }

        Text {
            id: viewable_start_label
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: viewable_start.right
            anchors.margins: 4
            width: 100
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 10
            text: "00:00:00" 
        }    
 
        Text {
            id: viewable_end_label
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: viewable_end.left
            anchors.margins: 4
            width: 100
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 10
            text: "00:00:00" 
        }    
        
        Rectangle {
            id: viewable_end
            color: "blue"
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 4
            border.width: 1
            width: height
            radius: height/2
        }

    }
}
