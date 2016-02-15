/***********************************************************************
 *
 * Filename: SceneGraph3D.qml 
 *
 * Description: Displays all nodes in the scenegraph. 
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
import QtQuick 2.5

Rectangle {
    id: window
    color: "darkgrey"

    //scale: 0.5

Canvas {
    id: scenegraph
    contextType: "2d"
    anchors.fill: parent

    Path {
        id: path

        startX: 0
        startY: 0

        PathLine {
            id: target 
            x: 200
            y: 200
        }
    }

    onPaint: {
        context.reset()
        // draw connections
        context.strokeStyle = "#090909"
        context.path = path
        context.lineWidth = 1
        context.stroke()
    }

    SceneGraphNode {
        id: a 
        name: "test"
    }

    function updateConnections(x,y,uid) {
        path.startX=x
        path.startY=y 
        requestPaint()
    }

    Component.onCompleted: {
        a.moved.connect(updateConnections)                        
    }
}

}
