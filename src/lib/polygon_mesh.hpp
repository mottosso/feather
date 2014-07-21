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
#include "field.hpp"
#include "node.hpp"

namespace feather
{

    namespace node
    {

        struct PolygonMeshNode
        {
            field::Field<FVertex3D> v;
            field::Field<FNormal3D> n;
            field::Field<FTextureCoord> st;
        };

        template <> status Node<PolygonMeshNode,PolygonMesh>::init(PolygonMeshNode node)
        {
            return status();
        };

    } // namespace node

} // namespace feather

#endif
