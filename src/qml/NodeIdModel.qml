/***********************************************************************
 *
 * Filename: NodeIdModel.qml 
 *
 * Description: Holds all the nodes that can be added to the scenegraph. 
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
import feather.node 1.0

ListModel {
    id: model
    ListElement { text: "Empty"; type: Node.Empty; nid: 0 }
    ListElement { text: "Transform"; type: Node.Modifier; nid: 2 }
    // Polygons
    ListElement { text: "Shape"; type: Node.Polygon; nid: 320 }
    ListElement { text: "Plane"; type: Node.Polygon; nid: 321 }
    ListElement { text: "Cube"; type: Node.Polygon; nid: 322 }

    function set_type(type){
        console.log("set type " + type)
        //console.log(model.get(type).nid)
    }
}
