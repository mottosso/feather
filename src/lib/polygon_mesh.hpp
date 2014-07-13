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

namespace feather
{

    namespace node
    {

        struct PolygonMeshFields : public FieldContainer
        {
            field::Field<field::Vertex3D> v;
            field::Field<field::Normal3D> n;
            field::Field<field::TextureCoord> st;
        };

        template <> struct Node<PolygonMesh, PolygonMeshFields>::init(PolygonMeshFields fields)
        {
            return status();
        };

    } // namespace node

} // namespace feather

#endif
