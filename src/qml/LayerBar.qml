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
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Rectangle {
    id: layerFrame
    height: 24
    //radius: 4
    color: (layerFrame.ListView.view.currentIndex==index) ? "lime" : layerColor 
    border.width: (ListView.view.currentIndex==index) ? 2 : 1 
    border.color: (ListView.view.currentIndex==index) ? "hotpink" : "black" 

    // I might add later but I'm not sure
    // POPUP
    //LayerPopupMenu { id: popup; z: 1 }

    // LABEL

    ColorDialog {
        id: colorDialog
        title: "Layer Color"

        onAccepted: {
            layerFrame.ListView.view.model.setColor(colorDialog.color,index)
            colorDialog.visible = false;
        }

        onRejected: { colorDialog.visible = false; }

        Component.onCompleted: visible = false 
    }

    Row {
        spacing: 8
        anchors.fill: parent
        anchors.margins: 4

        // Bar Selecting 

        Item { 
            id: selectIcon
            visible: true 
            width: 20
            height: parent.height 
            property color deselectColor: layerColor

            Image {
                id: select_on_icon
                anchors.fill: parent
                visible: (layerFrame.ListView.view.currentIndex==index) ? true : false 
                sourceSize.width: 18
                sourceSize.height: 18
                source: "icons/select_bubble_on.svg"
            }

            Image {
                id: select_off_icon
                anchors.fill: parent
                visible: (layerFrame.ListView.view.currentIndex==index) ? false : true 
                sourceSize.width: 18
                sourceSize.height: 18
                source: "icons/select_bubble_off.svg"
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                onClicked: { 
                    if(mouse.button==Qt.LeftButton)
                        layerFrame.ListView.view.currentIndex = index
                    if(mouse.button==Qt.RightButton){
                        //popup.x = mouse.x - 10
                        //popup.y = mouse.y - popup.height + 10
                        //popup.visible=true 
                    }
                }
            }
        }

        Item {
            id: labelName
            height: parent.height
            width: parent.width-110

            Text {
                id: label
                anchors.fill: parent
                visible: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 14
                font.bold: false
                text: layerName
            }

            TextField {
                id: labelEdit
                anchors.fill: parent
                visible: false
                readOnly: false
            }
 
            MouseArea {
                id: mouseTextArea
                anchors.fill: parent
                hoverEnabled: true 
                acceptedButtons: Qt.LeftButton // | Qt.RightButton


                //onPressed: { /*mouse.accepted = false*/ }

                //onClicked: { mouse.accepted = false }

                onClicked: {
                    mouse.accepted = false
                    if(label.visible){
                        label.visible = false
                        labelEdit.text = layerName
                        labelEdit.placeholderText = "Enter Layer Name" 
                        labelEdit.visible = true
                        labelEdit.forceActiveFocus()
                    }
                }

                onExited: {
                    label.visible = true
                    labelEdit.visible = false
                }
    
                onDoubleClicked: { mouse.accepted = false }

            }

            function setLabelName(){
                layerFrame.ListView.view.model.setName(labelEdit.text,index);
                labelEdit.visible = false
                label.visible = true
            }

            Component.onCompleted: { labelEdit.accepted.connect(setLabelName) } 
 
        }


        // Bar Color 

        Item { 
            id: barColorIcon
            visible: true 
            width: 20
            height: parent.height

            Image {
                id: color_icon
                anchors.fill: parent
                visible: true 
                sourceSize.width: 18
                sourceSize.height: 18
                source: "icons/color.svg"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    colorDialog.color = layerColor
                    colorDialog.visible = true //(!colorDialog.visible) ? true : false
                    mouse.accepted = false
                }
            }
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
                visible: (layerVisible) ? true : false 
                sourceSize.width: 18
                sourceSize.height: 18
                source: "icons/visible.svg"
            }

            Image {
                id: not_visible_icon
                anchors.fill: parent
                visible: (layerVisible) ? false : true 
                sourceSize.width: 18
                sourceSize.height: 18
                source: "icons/not_visible.svg"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(layerVisible)
                        layerFrame.ListView.view.model.setVisible(false,index);   
                    else
                        layerFrame.ListView.view.model.setVisible(true,index);   
                    mouse.accepted = false
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
                visible: (layerLocked) ? true : false
                sourceSize.width: 18
                sourceSize.height: 18
                source: "icons/locked.svg"
            }

            Image {
                id: unlocked_icon
                anchors.fill: parent
                visible: (layerLocked) ? false : true 
                sourceSize.width: 18
                sourceSize.height: 18
                source: "icons/unlocked.svg"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(layerLocked)
                        layerFrame.ListView.view.model.setLocked(false,index);   
                    else
                        layerFrame.ListView.view.model.setLocked(true,index);   
                    mouse.accepted = false;
                }
            }
        }
    }
}
