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

import QtQuick 2.1

Rectangle {
    id: popup
    width: 100
    height: 200
    visible: false

    border.color: "black"
    border.width: 1
    color: "grey"
    radius: 2

    property alias model: view.model 

    Translation { id: translation }
    
    ListView {
        id: view
        anchors.fill: parent
        anchors.margins: 1
        delegate: MenuButton { label: translation.get_field_name(nid,fid); ftype: type } 
        spacing: 1

    }

    function resize() {
        popup.height = (popup.model.rowCount() * 15) + popup.model.rowCount();
    }

}
