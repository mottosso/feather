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
#include "field.hpp"

namespace feather
{

    namespace polygon_plane
    {
        enum Id { SubX, SubY, Mesh };

        struct data : public DataObject 
        {
            FField subx=FField(SubX);
            FField suby=FField(SubY);
            FField mesh=FField(Mesh, field::Mesh, field::Connection::Out);
        };

    } // namespace polygon_plane

    //SET_NODE_DATA(polygon_plane::data)
    //template <> polygon_plane::data* DataObject::get_data<polygon_plane::data>(FNodeDescriptor node) { return static_cast<polygon_plane::data*>(sg[node].data); };

    namespace scenegraph
    {
        template <> status add_node<node::Object,node::PolygonPlane>(int id)
        {
            /*
            std::cout << "ADD NODE " << id << std::endl;
            FNodeDescriptor node = boost::add_vertex(sg);
            sg[node].type = node::PolygonPlane;
            sg[node].id = id;
            GET_NODE_DATA(polygon_plane::data)
            sg[node].data = pdata;
            node_selection.push_back(node);
            */
            return status();
        };


        /*
        template <> status add_node<node::PolygonPlane>(int id)
        {
            std::cout << "ADD NODE " << id << std::endl;
            FNodeDescriptor node = boost::add_vertex(sg);
            sg[node].type = node::PolygonPlane;
            sg[node].id = id;
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
            //std::cout << "subx = " << pdata->subx << std::endl;

            return status();
        };
        */

    } // namespace scenegraph

} // namespace feather

#endif
