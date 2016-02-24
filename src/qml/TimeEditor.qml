/***********************************************************************
 *
 * Filename: TimeEditor.qml 
 *
 * Description: Controls time attributes of the scenegraph. 
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
import feather.scenegraph 1.0

Rectangle {
    id: editor
    height: 50
    border.width: 1
    radius: 2
    color: "darkgrey"

    Rectangle {
        id: start_time_box
        width: 50
        height: controller.height
        anchors.top: parent.top
        anchors.left: parent.left
        border.width: 1
        radius: 2
        color: "grey"

        TextEdit {
            id: stime
            anchors.fill: parent
            anchors.margins: 2
            text: "0"
            font.pixelSize: 14
            horizontalAlignment: TextEdit.AlignHCenter
            verticalAlignment: TextEdit.AlignVCenter
        }
    }

    
    Rectangle {
        id: bar_box
        height: controller.height 
        anchors.left: start_time_box.right
        anchors.top: parent.top
        anchors.right: end_time_box.left
        border.width: 1
        radius: 2
        color: "orange"
       
        TimeBar {
            id: bar
            anchors.fill: parent
            anchors.margins: 2
        }
    }

    Rectangle {
        id: end_time_box
        width: 50
        height: controller.height 
        anchors.top: parent.top
        anchors.right: controller.left
        border.width: 1
        radius: 2
        color: "grey"

        TextEdit {
            id: etime
            anchors.fill: parent
            anchors.margins: 2
            text: "0"
            font.pixelSize: 14
            horizontalAlignment: TextEdit.AlignHCenter
            verticalAlignment: TextEdit.AlignVCenter
        }
    }


    TimeController {
        id: controller
        anchors.top: parent.top
        anchors.right: parent.right
    }

    TimeSlider {
        id: slider
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: bar_box.bottom
        anchors.right: controller.left
        anchors.margins: 2 
    }

    TimeCode {
        id: timecode
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: controller.bottom
        anchors.left: slider.right
        anchors.margins: 2
    }

    Component.onCompleted: {
        console.log("time node uid = " + SceneGraph.get_node_by_name("time"))
    }
}
