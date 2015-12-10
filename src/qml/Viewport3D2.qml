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
//import feather.viewport 1.0
import feather.scenegraph 1.0


Rectangle {
    id: frame

Scene3D {
    id: scene3d
    anchors.fill: parent
    anchors.margins: 10
    focus: true
    aspects: "input"

Entity {
    id : rootNode

    CameraLens {
        id : cameraLens
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.01
        farPlane : 1000.0
    } // cameraLens

    Entity {
        id : sceneRoot
        components: [frameGraph]
        property real rotationAngle : 0

        SequentialAnimation {
            running : true
            loops: Animation.Infinite
            NumberAnimation {target : sceneRoot; property : "rotationAngle"; to : 360; duration : 2000;}
        }

        property var cameras : [cameraViewport1, cameraViewport2, cameraViewport3, cameraViewport4]

        Timer {
            running : true
            interval : 10000
            repeat : true
            property int count : 0
            onTriggered:
            {
                cameraSelectorTopLeftViewport.camera = sceneRoot.cameras[count++ % 4];
                cameraSelectorTopRightViewport.camera = sceneRoot.cameras[count % 4];
                cameraSelectorBottomLeftViewport.camera = sceneRoot.cameras[(count + 1) % 4];
                cameraSelectorBottomRightViewport.camera = sceneRoot.cameras[(count + 2) % 4];
            }
        }

        FrameGraph {
            id : frameGraph

            Viewport {
                id : mainViewport
                rect: Qt.rect(0, 0, 1, 1)

                ClearBuffer {
                    buffers : ClearBuffer.ColorDepthBuffer
                }

                Viewport {
                    id : topLeftViewport
                    rect : Qt.rect(0, 0, 0.5, 0.5)
                    CameraSelector {id : cameraSelectorTopLeftViewport; camera : sceneRoot.cameras[0]}
                }

                Viewport {
                    id : topRightViewport
                    rect : Qt.rect(0.5, 0, 0.5, 0.5)
                    CameraSelector {id : cameraSelectorTopRightViewport; camera : sceneRoot.cameras[1]}
                }

                Viewport {
                    id : bottomLeftViewport
                    rect : Qt.rect(0, 0.5, 0.5, 0.5)
                    CameraSelector {id : cameraSelectorBottomLeftViewport; camera : sceneRoot.cameras[2]}
                }

                Viewport {
                    id : bottomRightViewport
                    rect : Qt.rect(0.5, 0.5, 0.5, 0.5)
                    CameraSelector {id : cameraSelectorBottomRightViewport; camera : sceneRoot.cameras[3]}
                }

            } // mainViewport
        } // frameGraph

        Entity {
            id : cameraViewport1
            property Transform transform : Transform {
                LookAt {
                    position: Qt.vector3d( 0.0, 0.0, -20.0 )
                    upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
                    viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
                }
            }
            components : [cameraLens, transform]
        }

        Entity {
            id : cameraViewport2
            property Transform transform : Transform {
                Rotate {
                    angle : sceneRoot.rotationAngle
                    axis : Qt.vector3d(0, 1, 0)
                }
                LookAt {
                    position: Qt.vector3d( 0.0, 0.0, 20.0 )
                    upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
                    viewCenter: Qt.vector3d( -3.0, 0.0, 10.0 )
                }
            }
            components : [cameraLens, transform]
        }

        Entity {
            id : cameraViewport3
            property Transform transform : Transform {
                LookAt {
                    position: Qt.vector3d( 0.0, 30.0, 30.0 )
                    upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
                    viewCenter: Qt.vector3d( -5.0, -20.0, -10.0 )
                }
            }
            components : [cameraLens, transform]
        }

        Entity {
            components : [
                Transform {
                    Rotate {
                        angle : -sceneRoot.rotationAngle
                        axis : Qt.vector3d(0, 0, 1)
                    }
                },
                SceneLoader {
                    source: "qrc:/assets/test_scene.dae"
                }]
        }

        Entity {
            id : cameraViewport4
            property Transform transform : Transform {
                LookAt {
                    position: Qt.vector3d( 0.0, 15.0, 20.0 )
                    upVector: Qt.vector3d( 0.0, 0.0, 1.0 )
                    viewCenter: Qt.vector3d( 0.0, -15.0, -20.0 )
                }
            }
            components : [cameraLens, transform]
        }

    } // sceneRoot

} // rootNode

}

}
