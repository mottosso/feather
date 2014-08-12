// =====================================================================================
// 
//       Filename:  root_node.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/12/2014 03:42:23 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef ROOT_NODE_HPP
#define ROOT_NODE_HPP

#include "types.hpp"
#include "status.hpp"
#include "node.hpp"
#include "scenegraph.hpp"

namespace feather
{

    namespace root
    {

        struct data : public DataObject
        {
            FNodeArray nodes;
        };

    } // namespace root

    template <> root::data* DataObject::get_data<root::data>(FNodeDescriptor node) { return static_cast<root::data*>(sg[node].data); };

    namespace scenegraph
    {

        template <> status add_node<node::Root>(std::string n)
        {
            std::cout << "ADDING ROOT NODE" << std::endl;
            FNodeDescriptor node = boost::add_vertex(sg);
            sg[node].type = node::Root;
            sg[node].name = n;
            root::data* pdata = new root::data();
            sg[node].data = pdata;
            node_selection.push_back(node);   
            return status();
        };

        template <> status do_it<node::Root>::exec(FNodeDescriptor node)
        {
            root::data* pdata=sg[node].data->get_data<root::data>(node);
            std::cout << "Root " << sg[node].name << std::endl;
            return status();
        }

    } // namespace scenegraph

} // namespace feather

#endif
