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

        template <typename _Node, int _NodeType>
            struct Node
            {
                static status init(_Node node) { return status(FAILED,"No matching Type for Node."); };
                static status do_it(_Node node) { return status(FAILED,"No matching Type for Node."); };
                static status undo() { return status(FAILED,"No matching Type for Node."); };
                static status remove() { return status(FAILED,"No matching Type for Node."); };
                static status init_gl() { return status(FAILED,"No matching Type for Node."); };
                static status draw_gl() { return status(FAILED,"No matching Type for Node."); };
                static status cleanup() { return status(FAILED,"No matching Type for Node."); };
                
                private:
                FVertex3DArray m_v;
                FVertex3DArray m_vn;
                FTextureCoordArray m_st;
                // opengl
                int m_vAttr;
                int m_mAttr;
                QOpenGLShaderProgram m_program;
                QOpenGLShader* m_shader;
            };

    } // namespace node

} // namespace feather

#endif
