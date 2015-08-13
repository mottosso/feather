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
import QtQuick.Dialogs 1.0

Rectangle {
    id: layerFrame
    height: 24
    radius: 2
    //color: "hotpink"
    border.width: 1

    property int barId: 0
    property alias barName: label.text
    property alias barColor: layerFrame.color
    property bool barVisible: true  
    property bool barLocked: false
    // LABEL



    ColorDialog {
        id: colorDialog
        title: "Layer Color"
        onAccepted: {
            //console.log("You chose: " + colorDialog.color)
            layerFrame.color = colorDialog.color
            colorDialog.visible = false;
            //Qt.quit()
        }
        onRejected: {
            //console.log("Canceled")
            colorDialog.visible = false;
            //Qt.quit()
        }
        Component.onCompleted: visible = false 
    }


    Row {
        spacing: 8
        anchors.fill: parent
        anchors.margins: 4

        Text {
            id: label
            //anchors.top: parent.top
            //anchors.bottom: parent.bottom
            //anchors.left: parent.left
            height: parent.height
            width: parent.width-50
            //anchors.margins: 4
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 14
            font.bold: false 
        }    


        // Bar Visiblity 
        Item { 
            id: barVisibleIcon
            visible: true 
            width: 20
            height: parent.height

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

        // Bar Locking 
        Item { 
            id: barLockIcon
            visible: true 
            width: 20
            height: parent.height 

            Image {
                id: locked_icon
                anchors.fill: parent
                visible: true 
                sourceSize.width: 18
                sourceSize.height: 18
                source: "icons/locked.svg"
            }

            Image {
                id: unlocked_icon
                anchors.fill: parent
                visible: false 
                sourceSize.width: 18
                sourceSize.height: 18
                source: "icons/unlocked.svg"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    locked_icon.visible = (locked_icon.visible) ? false : true
                    unlocked_icon.visible = (unlocked_icon.visible) ? false : true
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
            mouse.accepted=false
        }

        onClicked: { mouse.accepted=false }

        onDoubleClicked: { colorDialog.color=layerFrame.color; colorDialog.visible=true }
        //onPositionChanged: { }
        //onReleased: { layerFrame.state="normal" }
        //onEntered: { layerFrame.state="hover" }
        //onExited: { layerFrame.state="normal" }
    }

    Component.onCompleted: {
        console.log("layer id=" + layerId)
        /*layerFrame.state="normal"*/
    }

}
