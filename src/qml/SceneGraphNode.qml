/***********************************************************************
 *
 * Filename: SceneGraphNode.qml 
 *
 * Description: A single node in scenegraph. 
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
    id: node
    width: 100
    height: 100
    border.width: 1
    radius: 2 
    property int nid: 0
    property int uid: 0
    property alias name: label.text
    property bool expanded: true // displays all the fids

    signal moved(int x, int y, int uid)

    onXChanged: { moved(node.x,node.y,node.uid) }
    onYChanged: { moved(node.x,node.y,node.uid) }

    ListModel {
        id: inputModel

        ListElement {
            field_name: "parent"
            field_fid: 1
        }

        ListElement {
            field_name: "subX"
            field_fid: 2
        }

        ListElement {
            field_name: "subY"
            field_fid: 3
        }


        ListElement {
            field_name: "parent"
            field_fid: 1
        }

        ListElement {
            field_name: "subX"
            field_fid: 2
        }

        ListElement {
            field_name: "subY"
            field_fid: 3
        }


    }

    ListModel {
        id: outputModel

        ListElement {
            field_name: "child"
            field_fid: 1
        }

        ListElement {
            field_name: "mesh"
            field_fid: 2
        }

    }


    Rectangle {
        id: labelBox
        width: parent.width-20
        height: 14
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.top
        radius: 2

        Text {
            id: label 
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: false 
            font.pixelSize: 12
        }
 
    }

    ListView {
        id: inputView
        anchors.top: labelBox.bottom
        anchors.left: node.left
        //anchors.bottom: node.bottom
        height: contentHeight
        anchors.margins: 2 
        width: (node.width/2) - 2
        spacing: 2
        model: inputModel
        delegate: SceneGraphConnection { anchors.left: parent.left; width: (node.width/2)-4; name: field_name; fid: field_fid; direction: 0 }
    }

    ListView {
        id: outputView
        anchors.top: labelBox.bottom
        anchors.left: inputView.right 
        anchors.right: node.right
        height: contentHeight 
        anchors.margins: 2
        spacing: 2
        model: outputModel
        delegate: SceneGraphConnection { anchors.right: parent.right; width: (node.width/2)-4; name: field_name; fid: field_fid; direction: 1 }
    }


    states: [
        // NORMAL 
        State {
            name: "Normal"
            PropertyChanges {
                target: node 
                color: "lightgrey"
                border.color: "black"
            }

            PropertyChanges {
                target: labelBox
                color: "white"
                border.color: "black"
            }

        },

        // DRAG 
        State {
            name: "Drag"
            PropertyChanges {
                target: node 
                color: "purple"
                border.color: "black"
            }

            PropertyChanges {
                target: labelBox
                color: "orange"
                border.color: "black"
            }

        },

        // HOVER 
        State {
            name: "Hover"
            PropertyChanges {
                target: node 
                color: "yellow"
                border.color: "black"
            }

            PropertyChanges {
                target: labelBox
                color: "pink"
                border.color: "black"
            }

        },

        // SELECTED 
        State {
            name: "Selected"
            PropertyChanges {
                target: node 
                color: "lime"
                border.color: "black"
            }

            PropertyChanges {
                target: labelBox
                color: "yellow"
                border.color: "black"
            }

        }

    ]

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        drag.target: node
        
        onEntered: {
            node.state="Hover"
        }
 
        onExited: {
            //console.log("exited")
            if(drag.active){ node.state="Drag" }
            else { node.state="Normal" }
            //node.state="Normal"
        }
       
        onPositionChanged: {
            if(drag.active){ node.state="Drag" }
            //else { node.state="Normal" }
        } 
    }

    Component.onCompleted: {
        node.state="Normal"
        node.height=inputView.height + 14
    }
}
