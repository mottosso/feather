/***********************************************************************
 *
 * Filename: SceneGraphNode.qml 
 *
 * Description: A single node in scenegraph. 
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
import Qt3D 2.0
import Qt3D.Renderer 2.0

Entity {
    id: node 

    components: [ transform, mesh, material ]

    Transform {
        id: transform
    }

    Material {
        id: material
    }


    GeometryRenderer {
        id: mesh
        instanceCount: 1
        baseVertex: 0
        baseInstance: 0
        primitiveType: GeometryRenderer.Triangles

        Buffer {
            id: vertexBuffer
            type: Buffer.VertexBuffer
            data: buildVertex()
        }

        Buffer {
            id: indexBuffer
            type: Buffer.IndexBuffer
            data: buildIndex()
        }

        geometry:  Geometry {
            Attribute {
                attributeType: Attribute.VertexAttribute
                dataType: Attribute.Float
                dataSize: 3
                byteOffset: 0
                byteStride: 9 * 4
                count: 4
                name: defaultPositionAttributeName()
                buffer: vertexBuffer
            }

            Attribute {
                attributeType: Attribute.VertexAttribute
                dataType: Attribute.Float
                dataSize: 3
                byteOffset: 3 * 4
                byteStride: 9 * 4
                count: 4
                name: defaultNormalAttributeName()
                buffer: vertexBuffer
            }

            Attribute {
                attributeType: Attribute.VertexAttribute
                dataType: Attribute.Float
                dataSize: 3
                byteOffset: 6 * 4
                byteStride: 9 * 4
                count: 4
                name: defaultColorAttributeName()
                buffer: vertexBuffer
            }

            Attribute {
                attributeType: Attribute.IndexAttribute
                dataType: Attribute.UnsignedShort
                dataSize: 1
                byteOffset: 0
                byteStride: 0
                count: 12
                buffer: indexBuffer
            }
        }
    }


    function buildVertex() {

        // Vertices
        var v0 = Qt.vector3d(-1.0, 0.0, -1.0)
        var v1 = Qt.vector3d(1.0, 0.0, -1.0)
        var v2 = Qt.vector3d(0.0, 1.0, 0.0)
        var v3 = Qt.vector3d(0.0, 0.0, 1.0)

        // Face Normals
        function normal(v0, v1, v2) {
            return v1.minus(v0).crossProduct(v2.minus(v0)).normalized();
        }
        var n023 = normal(v0, v2, v3)
        var n012 = normal(v0, v1, v2)
        var n310 = normal(v3, v1, v0)
        var n132 = normal(v1, v3, v2)

        // Vector normals
        var n0 = n023.plus(n012).plus(n310).normalized()
        var n1 = n132.plus(n012).plus(n310).normalized()
        var n2 = n132.plus(n012).plus(n023).normalized()
        var n3 = n132.plus(n310).plus(n023).normalized()

        // Colors
        var red = Qt.vector3d(1.0, 0.0, 0.0)
        var green = Qt.vector3d(0.0, 1.0, 0.0)
        var blue = Qt.vector3d(0.0, 0.0, 1.0)
        var white = Qt.vector3d(1.0, 1.0, 1.0)

        var vertices = [
                    v0, n0, red,
                    v1, n1, blue,
                    v2, n2, green,
                    v3, n3, white
                ]

        var vertexArray = new Float32Array(4 * (3 + 3 + 3));
        var i = 0;

        vertices.forEach(function(vec3) {
            vertexArray[i++] = vec3.x;
            vertexArray[i++] = vec3.y;
            vertexArray[i++] = vec3.z;
        });

        return vertexArray;
    }

    function buildIndex() {
        var indexArray = new Uint16Array(12);

        // Front
        indexArray[0] = 0;
        indexArray[1] = 1;
        indexArray[2] = 2;
        // Bottom
        indexArray[3] = 3;
        indexArray[4] = 1;
        indexArray[5] = 0;
        // Left
        indexArray[6] = 0;
        indexArray[7] = 2;
        indexArray[8] = 3;
        // Right
        indexArray[9] = 1;
        indexArray[10] = 3;
        indexArray[11] = 2;

        return indexArray;
    }

}
