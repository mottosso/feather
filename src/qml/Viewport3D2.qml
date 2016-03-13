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

Rectangle {
    id: frame
    color: "yellow"

    /*
    Viewport {
        anchors.margins: 2
    }
    */


    /*
    Viewport {
        rect : Qt.rect(0.0, 0.0, 1.0, 1.0)
    
        property alias gBuffer : gBufferTargetSelector.target
        property alias camera : sceneCameraSelector.camera
    
        LayerFilter {
            layers : "scene"
        
            RenderTargetSelector {
                id : gBufferTargetSelector
            
                ClearBuffer {
                    buffers: ClearBuffer.ColorDepthBuffer
                
                    RenderPassFilter {
                        id : geometryPass
                        includes : Annotation { name : "pass"; value : "geometry" }
                    
                        CameraSelector {
                            id : sceneCameraSelector
                        }   
                    }   
                }   
            }   
        }   
    
        LayerFilter {
            layers : "screenQuad"
        
            ClearBuffer {
                buffers: ClearBuffer.ColorDepthBuffer
            
                RenderPassFilter {
                    id : finalPass
                    includes : Annotation { name : "pass"; value : "final" }
                    CameraSelector {
                        camera: sceneCameraSelector.camera
                    }   
                }   
            
            }
        }   
    }   
    */


    /* 
    Scene3D {
        id: scene3d
        anchors.fill: parent
        anchors.margins: 2
        focus: true
        aspects: "input"
    
        Viewport2 { 
            id: vp

            Camera {
                id: camera
                projectionType: CameraLens.PerspectiveProjection
                fieldOfView: 45
                aspectRatio: 16/9
                nearPlane : 0.01
                farPlane : 1000.0
                position: Qt.vector3d( 0.0, 0.0, -25.0 )
                upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
                viewCenter: Qt.vector3d( 0.0, 0.0, 10.0 )
            }

            GBuffer {
                id : gBuffer
            }

            Layer {
                id : sceneLayer
                names : "scene"
            }

            SceneEffect {
                id : sceneMaterialEffect
            }


    Entity {
        id : screenQuadEntity
        components : [
            Layer {
                names : "screenQuad"
            },
            PlaneMesh {
                width: 2.0
                height: 2.0
                meshResolution: Qt.size(2, 2)
            },
            Transform { // We rotate the plane so that it faces us
                //rotation: fromAxisAndAngle(Qt.vector3d(1, 0, 0), 90)
            },
            Material {
                parameters : [
                    Parameter { name: "color"; value : gBuffer.color },
                    Parameter { name: "position"; value : gBuffer.position },
                    Parameter { name: "normal"; value : gBuffer.normal },
                    Parameter { name: "winSize"; value : Qt.size(1024, 1024) }
                ]
                effect : FinalEffect {}
            }
        ]

    }


            Configuration  {
                controlledCamera: camera
            }

            components : FrameGraph {
                id : deferredFrameGraphComponent
                activeFrameGraph: DeferredRenderer {
                    camera : camera
                    gBuffer: gBuffer
                }
            }

        }
 
    }
    */

    Scene3D {
        id: scene3d
        anchors.fill: parent
        anchors.margins: 2
        focus: true
        aspects: "input"
 

        Viewport2 {
            id: root 
            Camera {
                    id: camera1
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
                controlledCamera: camera1
            }

            FrameGraph {
                id: frameGraph
                //activeFrameGraph: viewport

                activeFrameGraph: Viewport {
                    rect: Qt.rect(0, 0, 1, 1)
                    clearColor: "grey"

                    CameraSelector { 
                        id : cameraSelectorViewport
                        camera : camera1

                        ClearBuffer {
                            buffers : ClearBuffer.ColorDepthBuffer
                        }
                    }
                }
            }

            //Viewport2 { id: vp }
 
            components: [ frameGraph ]

        }

    } //sceneRoot


    function addNode(uid) {
        vp.addItems(uid) 
    }

    function addDrawItems(item) {
        vp.addItems(item)
    }

    function updateDrawItems(uid) {
        vp.updateItems(uid)
    }

    function updateViewport(uid,nid,fid) {
        vp.doUpdate()
    }

    Component.onCompleted: {
        SceneGraph.nodeAdded.connect(addNode)
        SceneGraph.nodeAddDrawItems.connect(addDrawItems)
        SceneGraph.nodeUpdateDrawItems.connect(updateDrawItems)
        SceneGraph.nodeFieldChanged.connect(updateViewport)
    }
}
