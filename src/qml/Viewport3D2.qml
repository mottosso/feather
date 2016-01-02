/***********************************************************************
 *
 * Filename: Viewport3D.qml 
 *
 * Description: Holds the C++ viewport. 
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
import QtQuick.Scene3D 2.0
import Qt3D 2.0
import Qt3D.Renderer 2.0
import feather.viewport 1.0
import feather.scenegraph 1.0


Rectangle {
    id: frame
    color: "yellow"

    Scene3D {
        id: scene3d
        anchors.fill: parent
        anchors.margins: 2
        focus: true
        aspects: "input"

        Entity {
            id : sceneRoot
            components: [frameGraph]
            property real rotationAngle : 0

            Camera {
                id: camera
                projectionType: CameraLens.PerspectiveProjection
                fieldOfView: 45
                aspectRatio: frame.width/frame.height
                nearPlane : 0.1
                farPlane : 1000.0
                position: Qt.vector3d( 0.0, 0.0, 20.0 )
                upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
                viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
            }

            Configuration  {
                controlledCamera: camera
            }

            SequentialAnimation {
                running : true
                loops: Animation.Infinite
                NumberAnimation {target : sceneRoot; property : "rotationAngle"; to : 360; duration : 2000;}
            }

            FrameGraph {
                id : frameGraph

                activeFrameGraph: ForwardRenderer {
                    id : mainViewport
                    clearColor: "grey"
                    camera: camera 
                } // mainViewport
            } // frameGraph

            /*
            PhongMaterial {
                id: material
            }

            SphereMesh {
                id: sphereMesh
                radius: 3
            }

            Transform {
                id: sphereTransform
                Translate {
                    translation: Qt.vector3d(20, 0, 0)
                }

                Rotate {
                    id: sphereRotation
                    axis: Qt.vector3d(0, 1, 0)
                }
            }
            
            Entity {
                id: sphereEntity
                components: [ sphereMesh, material, sphereTransform ]
            }
            */

            Viewport2 { id: vp }

        }

    } // sceneRoot

    MouseArea {
        anchors.fill: parent
        onClicked: { console.log("CLICKED"); vp.doUpdate() }
    }

    Component.onCompleted: { vp.doUpdate() }
}
