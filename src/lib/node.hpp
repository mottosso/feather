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

        template <int _Type>
            struct Node
            {
                static status do_it() { return status(FAILED,"No matching Type for Node."); };
                static status draw() { return status(FAILED,"No matching Type for Node."); };
                static status undo() { return status(FAILED,"No matching Type for Node."); };
                static status remove() { return status(FAILED,"No matching Type for Node."); };

                private:
                FVertexArray m_v;
                FVertexArray m_vn;
                FTextureCoordArray m_st;
            };

    } // namespace node

} // namespace feather

#endif
