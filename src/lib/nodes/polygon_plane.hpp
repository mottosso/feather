// =====================================================================================
// 
//       Filename:  polygon_plane.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/10/2014 06:16:03 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef POLYGON_PLANE_HPP
#define POLYGON_PLANE_HPP

#include "types.hpp"
#include "scenegraph.hpp"
#include "node.hpp"

namespace feather
{

    namespace polygon_plane
    {

        struct data : public DataObject
        {
            FInt subx=2;
            FInt suby=2;
            FInt subval=2;
        };

    } // namespace polygon_plane

    SET_NODE_DATA(polygon_plane::data)

    namespace scenegraph
    {


        template <> status add_node<node::PolygonPlane>(std::string n)
        {
            std::cout << "ADD NODE " << n << std::endl;
            FNodeDescriptor node = boost::add_vertex(sg);
            sg[node].type = node::PolygonPlane;
            sg[node].name = n;
            GET_NODE_DATA(polygon_plane::data)
            sg[node].data = pdata;

            node_selection.push_back(node);

            // run each node's do_it()
            //do_it<node::PolyPlane>(node);
            std::cout << "node added\n";

            return status();
        };

        DO_IT(node::PolygonPlane)
        {
            // Get the values for the input fields.
            // pdata will hold the address of the data
            GET_NODE_DATA(polygon_plane::data)
            std::cout << "subx = " << pdata->subx << std::endl;

            return status();
        };


    } // namespace scenegraph

} // namespace feather

#endif
