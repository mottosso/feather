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
        addFieldName("tX",1,3)
        addFieldName("tY",1,4)
        addFieldName("tZ",1,5)
        addFieldName("sX",1,6)
        addFieldName("sY",1,7)
        addFieldName("sZ",1,8)
        addFieldName("rX",1,9)
        addFieldName("rY",1,10)
        addFieldName("rZ",1,11)
        addFieldName("tX",1,12)
        addFieldName("tY",1,13)
        addFieldName("tZ",1,14)
        addFieldName("sX",1,15)
        addFieldName("sY",1,16)
        addFieldName("sZ",1,17)
        addFieldName("rX",1,18)
        addFieldName("rY",1,19)
        addFieldName("rZ",1,20)
 
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
