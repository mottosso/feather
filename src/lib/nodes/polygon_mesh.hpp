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

        struct PolygonMeshNode : public Object
        {
            FVertex3DArray v;
            FNormal3DArray n;
            FTextureCoordArray st;
        };

        typedef Node<PolygonMeshNode> polymesh;

        // INIT
        template <> status polymesh::init(PolygonMeshNode node)
        {
            
            return status();
        };

        // DO IT
        template <> status polymesh::do_it(PolygonMeshNode node)
        {
            return status();
        };

        // DRAW GL
        template <> status polymesh::draw_gl()
        {
            std::cout << "draw polycube\n";
            return status();
        };

    } // namespace node

} // namespace feather

#endif
