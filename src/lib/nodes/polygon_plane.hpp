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
            FInt* subx;
            FInt* suby;
            FInt* subval;
            FMesh* mesh;
        };

    } // namespace polygon_plane

    template <> polygon_plane::data* DataObject::get_data<polygon_plane::data>(FNodeDescriptor node) { return static_cast<polygon_plane::data*>(sg[node].data); };


    namespace scenegraph
    {


        template <> status add_node<node::PolygonPlane>(std::string n)
        {
            std::cout << "ADD NODE " << n << std::endl;
            FNodeDescriptor node = boost::add_vertex(sg);
            sg[node].type = node::PolygonPlane;
            sg[node].name = n;
            polygon_plane::data* pdata = new polygon_plane::data();
            sg[node].data = pdata;

            node_selection.push_back(node);

            // run each node's do_it()
            //do_it<node::PolyPlane>(node);
            std::cout << "node added\n";

            return status();
        };

        template <> status do_it<node::PolygonPlane>::exec(FNodeDescriptor node)
        {
            // get the values for the input fields
            polygon_plane::data* pdata = sg[node].data->get_data<polygon_plane::data>(node);

            std::cout << "Polygon Plane " << sg[node].name
                << " subx=" << pdata->subx //pdata->subx.get_value()
                << std::endl;

            return status();
        };


    } // namespace scenegraph

} // namespace feather

#endif
