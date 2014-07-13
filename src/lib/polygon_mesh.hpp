// =====================================================================================
// 
//       Filename:  polygon_mesh.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/13/2014 05:40:25 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef POLYGON_MESH_HPP
#define POLYGON_MESH_HPP

#include "deps.hpp"
#include "types.hpp"
#include "status.hpp"

namespace feather
{

    namespace node
    {

        template <typename _Fields> struct Node<PolygonMesh, _Fields>::init(_Fields fields)
        {
            return status();
        };

    } // namespace node

} // namespace feather

#endif
