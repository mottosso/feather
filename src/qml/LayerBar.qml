/***********************************************************************
 *
 * Filename: LayerBar.qml 
 *
 * Description: How a single layer will be displayed by the layer editor. 
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

Rectangle {
    id: layerFrame
    height: 20
    radius: 2
    //color: "hotpink"
    border.width: 1

    property int barId: 0
    property alias barName: label.text
    property alias barColor: layerFrame.color
    property bool barVisible: true  
    property bool barLocked: false
    // LABEL

    Row {
        spacing: 2
        anchors.fill: parent

    Text {
        id: label
        //anchors.top: parent.top
        //anchors.bottom: parent.bottom
        //anchors.left: parent.left
        height: parent.height
        width: parent.width-40
        //anchors.margins: 4
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12
        font.bold: false 
    }    

 
    Item { 
        id: barVisibleIcon
        visible: true 
        width: 20
        height: 20

        Image {
            id: visible_icon
            anchors.fill: parent
            visible: true 
            sourceSize.width: 18
            sourceSize.height: 18
            source: "icons/visible.svg"
        }

        Image {
            id: not_visible_icon
            anchors.fill: parent
            visible: false 
            sourceSize.width: 18
            sourceSize.height: 18
            source: "icons/not_visible.svg"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                visible_icon.visible = (visible_icon.visible) ? false : true
                    not_visible_icon.visible = (not_visible_icon.visible) ? false : true
            }
        }
    }

    }

    
    /*
    states: [
        // NORMAL
        State {
            name: "normal"
            PropertyChanges {
                target: intField 
                color: typeNormalStateColor() //"lightgrey"
            }

            PropertyChanges {
                target: label 
                color: "black"
                font.bold: false
            }
 
            PropertyChanges {
                target: valueBox
                color: (field.connected) ? "deeppink" : "lightblue"
            }

            PropertyChanges {
                target: valueText
                color: "black"
                font.bold: false
            }
        },

        // HOVER
        State {
            name: "hover"
            PropertyChanges {
                target: intField 
                color: "lightblue"
            }

            PropertyChanges {
                target: label 
                color: "black"
                font.bold: true 
            }

            PropertyChanges {
                target: valueBox
                color: "midnightblue"
            }

            PropertyChanges {
                target: valueText
                color: "white"
                 font.bold: true 
            }
        },

        // PRESSED  
        State {
            name: "pressed"
            PropertyChanges {
                target: intField 
                color: "green"
            }

            PropertyChanges {
                target: label 
                color: "black"
                font.bold: true 
            }

            PropertyChanges {
                target: valueBox
                color: "limegreen"
            }

            PropertyChanges {
                target: valueText
                color: "black"
                font.bold: true 
            }
        }

    ]
    */

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true 
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onPressed: {
            //if(mouse.button == Qt.RightButton)
        }

        //onPositionChanged: { }
        //onReleased: { layerFrame.state="normal" }
        //onEntered: { layerFrame.state="hover" }
        //onExited: { layerFrame.state="normal" }
    }

    Component.onCompleted: { console.log("layer id=" + layerId); /*layerFrame.state="normal"*/ }
}
