/***********************************************************************
 *
 * Filename: PopupMenu.qml 
 *
 * Description: Template Popup menu used by various editors popup menus. 
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
    id: popup
    width: 150
    height: 95
    visible: false

    border.color: "black"
    border.width: 1
    color: "grey"

    ListModel {
        id: layerModel
        ListElement { name: "Add Layer" }
        ListElement { name: "Remove Layer" }
        ListElement { name: "Move Layer Up" }
        ListElement { name: "Move Layer Down" }
    }

    signal addLayer()
    signal removeLayer()
    signal moveLayerUp()
    signal moveLayerDown()

    Translation { id: translation }
   
    ListView {
        id: view
        anchors.fill: parent
        anchors.margins: 4
        model: layerModel
        spacing: 2
        focus: true

        highlight: Rectangle {
            id: button
            height: 20
            width: parent.width
            color: "lightgrey"
            border.color: "black"
            border.width: 1
        }
 
        delegate: Item {
            height: 20
            width: parent.width
            //color: "grey"
            //border.color: "black"
            //border.width: 1
            Text {
                anchors.fill: parent
                text: name
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 14
            }

        }
    }

    function resize() {
        popup.height = (popup.model.rowCount() * 15) + popup.model.rowCount();
    }


    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onExited: { popup.visible = false; }
    }
}
