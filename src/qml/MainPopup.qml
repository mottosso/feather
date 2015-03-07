/***********************************************************************
 *
 * Filename: MainPopup.qml 
 *
 * Description: Popup window for the viewport. 
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
    SceneGraph { id: sg }
    /*
    style: MenuStyle {
        frame: Rectangle { color: "red"; border.color: "black"; border.width: 1; radius: 10 }
        //itemDelegate.background: Rectangle { border.color: "black"; border.width: 1; radius: 10 }
    }
    */

    // ACTIONS

    // Make Plane 
    Action {
        id: makePlaneAction
        text: "Plane"
        tooltip: "Create Polygon Plane"
        onTriggered: { sg.add_node(Node.Object,325) }
    }

    // Make Cube 
    Action {
        id: makeCubeAction
        text: "Cube"
        tooltip: "Create Polygon Cube"
        onTriggered: {}
    }

    // Make Torus 
    Action {
        id: makeTorusAction
        text: "Torus"
        tooltip: "Create Polygon Torus"
        onTriggered: {}
    }

    // Make Cylinder 
    Action {
        id: makeCylinderAction
        text: "Cylinder"
        tooltip: "Create Polygon Cylinder"
        onTriggered: {}
    }

    // Make Sphere 
    Action {
        id: makeSphereAction
        text: "Sphere"
        tooltip: "Create Polygon Sphere"
        onTriggered: {}
    }

    // Make Cone
    Action {
        id: makeConeAction
        text: "Cone"
        tooltip: "Create Polygon Cone"
        onTriggered: {}
    }

    // Make Grid
    Action {
        id: makeGridAction
        text: "Grid"
        tooltip: "Create Polygon Grid"
        onTriggered: {}
    }



    // LAYOUT

    MenuItem {
        action: makePlaneAction
    }

    MenuItem {
        action: makeCubeAction
    }

    MenuItem {
        action: makeTorusAction
    }

    MenuItem {
        action: makeCylinderAction
    }

    MenuItem {
        action: makeSphereAction
    }

    MenuItem {
        action: makeConeAction
    }

    MenuSeparator {}

    MenuItem {
        action: makeGridAction
    }

}
