/***********************************************************************
 *
 * Filename: NodeFields.qml 
 *
 * Description: This file holds all the field names for the nodes. 
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
import feather.field 1.0

FieldModel {

    Component.onCompleted: {
        // Empty
        addFieldName("parent",1,1)
        addFieldName("child",1,2)

        // Camera 
        addFieldName("parent",2,1)
        addFieldName("child",2,2)
        addFieldName("type",2,3)
        addFieldName("fov",2,4)

        // Shape 
        addFieldName("parent",3,1)
        addFieldName("child",3,2)
        addFieldName("meshIn",3,3)
        addFieldName("meshOut",3,4)
 
        // Time 
        addFieldName("parent",4,1)
        addFieldName("child",4,2)
        addFieldName("stime",4,3)
        addFieldName("etime",4,4)
        addFieldName("cpos",4,5)
        addFieldName("fps",4,6)
        addFieldName("stime",4,7)
        addFieldName("etime",4,8)
        addFieldName("cpos",4,9)
        addFieldName("fps",4,10)
 
        // Multiply 
        addFieldName("parent",5,1)
        addFieldName("child",5,2)
        addFieldName("value",5,3)
        addFieldName("mult",5,4)
        addFieldName("value",5,5)
 
        // Divide 
        addFieldName("parent",6,1)
        addFieldName("child",6,2)
        addFieldName("value",6,3)
        addFieldName("div",6,4)
        addFieldName("value",6,5)

        // Transform
        addFieldName("parent",7,1)
        addFieldName("child",7,2)
        addFieldName("tX",7,3)
        addFieldName("tY",7,4)
        addFieldName("tZ",7,5)
        addFieldName("sX",7,6)
        addFieldName("sY",7,7)
        addFieldName("sZ",7,8)
        addFieldName("rX",7,9)
        addFieldName("rY",7,10)
        addFieldName("rZ",7,11)
        addFieldName("local_tX",7,12)
        addFieldName("local_tY",7,13)
        addFieldName("local_tZ",7,14)
        addFieldName("local_sX",7,15)
        addFieldName("local_sY",7,16)
        addFieldName("local_sZ",7,17)
        addFieldName("local_rX",7,18)
        addFieldName("local_rY",7,19)
        addFieldName("local_rZ",7,20)
        addFieldName("world_tX",7,21)
        addFieldName("world_tY",7,22)
        addFieldName("world_tZ",7,23)
        addFieldName("world_sX",7,24)
        addFieldName("world_sY",7,25)
        addFieldName("world_sZ",7,26)
        addFieldName("world_rX",7,27)
        addFieldName("world_rY",7,28)
        addFieldName("world_rZ",7,29)

        // Polygon Shape 
        addFieldName("parent",320,1)
        addFieldName("mesh",320,3)
        addFieldName("test",320,4)
        // Out
        addFieldName("child",320,2)

        // Polygon Plane 
        addFieldName("parent",321,1)
        addFieldName("subX",321,3)
        addFieldName("subY",321,4)
        // Out
        addFieldName("child",321,2)
        addFieldName("mesh",321,5)

        // Polygon Cube
        // In
        addFieldName("parent",322,1)
        addFieldName("subX",322,3)
        addFieldName("subY",322,4)
        addFieldName("subZ",322,5)
        // Out 
        addFieldName("child",322,2)
        addFieldName("mesh",322,6)
    }

}
