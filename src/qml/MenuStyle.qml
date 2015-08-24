/***********************************************************************
 *
 * Filename: MenuStyle.qml 
 *
 * Description: look for the menus. 
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
import QtQuick.Controls.Styles 1.4

MenuStyle {
    id: item
    frame: Rectangle { color: "darkgrey"; border.color: "black"; border.width: 1 }
    itemDelegate.background: menuItem 
    itemDelegate.label: menuText

    Component {
        id: menuText
        Text {
            //anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: false 
            font.pixelSize: 12
            color: "black"
            text: styleData.text
        }
    }

    Component {
        id: menuItem
        Rectangle {
            color: (styleData.selected) ? "lightgrey" : "darkgrey"
            //radius: 2
        }
    }
}

