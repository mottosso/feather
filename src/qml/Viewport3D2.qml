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
import Qt3D.Input 2.0
import feather.viewport 1.0
import feather.scenegraph 1.0

Item {
    id: frame
    //color: "yellow"

        Viewport3 {
            id: vp
        }

    /*
    Scene3D {
        id: scene3d
        anchors.fill: parent
        anchors.margins: 2
        focus: true
        aspects: "input"
    */

        /*
        Entity {
            id : sceneRoot
            property real rotationAngle : 0
 
            Camera {
                id: camera
                projectionType: CameraLens.PerspectiveProjection
                fieldOfView: 45
                //aspectRatio: frame.width/frame.height
                nearPlane : 0.1
                farPlane : 1000.0
                position: Qt.vector3d( 0.0, 0.0, 20.0 )
                upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
                viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
            }

            Configuration  {
                controlledCamera: camera
            }

            MouseController { id: mouseController }

            FrameGraph {
                id : frameGraph

                activeFrameGraph: ForwardRenderer {
                    id : mainViewport
                    clearColor: "grey"
                    camera: camera 
                } // mainViewport

            } // frameGraph

            Viewport2 {
                id: vp
                MouseInput {
                    id: mouseInput
                    controller: mouseController
                    onClicked: { console.log("VP CLICKED") }
                }   
                components: [mouseInput]
            } 
            */

            //property MouseInput mouseInput: MouseInput {
            /*
            MouseInput {
                id: mouseInput
                controller: mouseController
                onClicked: { console.log("ENTITY CLICKED") }
            }

            PhongMaterial {
                id: material
                ambient: "red"
            }

            SphereMesh {
                id: sphereMesh
                radius: 1
            }

            Transform {
                id: sphereTransform
                Translate {
                    translation: Qt.vector3d(0, 0, 0)
                }

                Rotate {
                    id: sphereRotation
                    axis: Qt.vector3d(0, 1, 0)
                }
            }
            
            Entity {
                id: sphereEntity
                components: [ sphereMesh, material, sphereTransform]
            }
 
            components: [frameGraph, sphereEntity, mouseInput]
            */
            //components: [frameGraph, sphereEntity]
 
        //}

    //}// sceneRoot

    /*
    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: true 
        onClicked: { console.log("RECT CLICKED") }
    }
    */

    function addNode(uid) {
        // vp.addItems(uid) 
    }

    function addDrawItems(item) {
        // vp.addItems(item)
    }

    function updateDrawItems(uid) {
        // vp.updateItems(uid)
    }

    Component.onCompleted: {
        SceneGraph.nodeAdded.connect(addNode)
        SceneGraph.nodeAddDrawItems.connect(addDrawItems)
        SceneGraph.nodeUpdateDrawItems.connect(updateDrawItems)
    }
}
