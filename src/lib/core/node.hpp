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

namespace feather
{

    namespace node
    {

        enum Type {
            EndNode,
            Camera,
            Light,
            Texture,
            Shader,
            PolygonMesh,
            StartNode
        };

        template <typename _Node>
            struct Node : public Object
            {
                /* called when the node is created */
                static status init(_Node node) { return status(FAILED,"No matching Type for Node."); };
                /* called during a scenegraph update */
                static status do_it(_Node node) { return status(FAILED,"No matching Type for Node."); };
                /* called during an undo */
                static status undo() { return status(FAILED,"No matching Type for Node."); };
                /* called when the viewport is setup for opengl */
                static status init_gl() { return status(FAILED,"No matching Type for Node."); };
                /* called when the node is draw in the viewport */
                static status draw_gl() { return status(FAILED,"No matching Type for Node."); };
                /* called when the node is deleted */
                static status cleanup() { return status(FAILED,"No matching Type for Node."); };

                private:
                // OpenGL attributes 
                FVertex3DArray m_v;
                FVertex3DArray m_vn;
                FTextureCoordArray m_st;
                int m_vAttr;
                int m_mAttr;
                //QOpenGLShaderProgram m_program;
                //QOpenGLShader* m_shader;
            };

    } // namespace node

} // namespace feather

#endif
