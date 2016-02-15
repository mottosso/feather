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
import Qt3D 2.0
import Qt3D.Renderer 2.0
import QtQuick.Scene3D 2.0


Scene3D {
    id: scene3d
    anchors.fill: parent
    anchors.margins: 2
    focus: true
    aspects: "input"


    Entity {
        id: root

        // Render from the mainCamera
        components: [
            FrameGraph {
                activeFrameGraph: ForwardRenderer {
                    id: renderer
                    camera: mainCamera
                    clearColor: "black"
                }
            }
        ]

        Camera {
            id: mainCamera
            position: Qt.vector3d( 0.0, 0.0, 15.0 )
        }

        Configuration  {
            controlledCamera: mainCamera
        }

        SceneGraphNode {
            id: testNode 
        }
    }
}
