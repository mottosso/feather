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
        addFieldName("Parent",1,1)
        addFieldName("Child",1,2)

        // Transform
        addFieldName("tX",3,3)
        addFieldName("tY",3,4)
        addFieldName("tZ",3,5)
        addFieldName("sX",3,6)
        addFieldName("sY",3,7)
        addFieldName("sZ",3,8)
        addFieldName("rX",3,9)
        addFieldName("rY",3,10)
        addFieldName("rZ",3,11)
        addFieldName("local_tX",3,12)
        addFieldName("local_tY",3,13)
        addFieldName("local_tZ",3,14)
        addFieldName("local_sX",3,15)
        addFieldName("local_sY",3,16)
        addFieldName("local_sZ",3,17)
        addFieldName("local_rX",3,18)
        addFieldName("local_rY",3,19)
        addFieldName("local_rZ",3,20)
        addFieldName("world_tX",3,21)
        addFieldName("world_tY",3,22)
        addFieldName("world_tZ",3,23)
        addFieldName("world_sX",3,24)
        addFieldName("world_sY",3,25)
        addFieldName("world_sZ",3,26)
        addFieldName("world_rX",3,27)
        addFieldName("world_rY",3,28)
        addFieldName("world_rZ",3,29)
 
        // Polygon Shape 
        addFieldName("Parent",320,1)
        addFieldName("Mesh",320,3)
        addFieldName("Test",320,4)
        // Out
        addFieldName("Child",320,2)

        // Polygon Shape 
        addFieldName("Parent",321,1)
        addFieldName("SubX",321,3)
        addFieldName("SubY",321,4)
        // Out
        addFieldName("Child",321,2)
        addFieldName("Mesh",321,5)

        // Polygon Cube
        // In
        addFieldName("Parent",322,1)
        addFieldName("SubX",322,3)
        addFieldName("SubY",322,4)
        addFieldName("SubZ",322,5)
        // Out 
        addFieldName("Child",322,2)
        addFieldName("Mesh",322,6)
    }

}
