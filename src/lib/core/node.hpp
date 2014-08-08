// =====================================================================================
// 
//       Filename:  node.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/08/2014 04:46:04 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef NODE_HPP
#define NODE_HPP

#include "deps.hpp"
#include "types.hpp"
#include "status.hpp"
#include "object.hpp"
#include "field.hpp"

namespace feather
{

    namespace node
    {

        enum Type {
            Null,
            Camera,
            Light,
            Texture,
            Shader,
            PolygonMesh,
            StartNode
        };

        /*
        struct NodeAttributes {
            FVertex3DArray v;
            FVertex3DArray vn;
            FTextureCoordArray st;
            int vAttr;
            int mAttr;
            QOpenGLShaderProgram program;
            QOpenGLShader* vshader;
            QOpenGLShader* fshader;
            QMatrix4x4 view;
        };
        
        template <int _Node>
            struct Node : public Object
            {
                // called when the node is created
                static status init(NodeAttributes* nattr, Fields* fields) { return status(FAILED,"No matching Type for Node."); };
                // called during a scenegraph update
                static status do_it(Fields* fields) { return status(FAILED,"No matching Type for Node."); };
                // called during an undo
                static status undo() { return status(FAILED,"No matching Type for Node."); };
                // called when the viewport is setup for opengl
                static status init_gl() { return status(FAILED,"No matching Type for Node."); };
                // called when the node is draw in the viewport
                static status draw_gl(NodeAttributes* nattr, Fields* fields) { return status(FAILED,"No matching Type for Node."); };
                // called when the node is deleted
                static status cleanup() { return status(FAILED,"No matching Type for Node."); };
            };
        */
    } // namespace node

} // namespace feather

#endif
