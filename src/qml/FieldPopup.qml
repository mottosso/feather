/***********************************************************************
 *
 * Filename: FieldPopup.qml 
 *
 * Description: Popup for field values inside the node editor. 
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
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import feather.scenegraph 1.0
import feather.node 1.0

Menu {
    // ACTIONS

    // Make Plane 
    Action {
        id: lockFieldAction
        text: "Lock"
        tooltip: "Lock the field so it can't be edited"
        onTriggered: { }
    }


    // LAYOUT

    MenuItem {
        action: lockFieldAction 
    }

}
