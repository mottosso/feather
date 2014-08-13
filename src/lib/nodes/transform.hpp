// =====================================================================================
// 
//       Filename:  transform.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/13/2014 04:44:19 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "types.hpp"
#include "scenegraph.hpp"
#include "node.hpp"

namespace feather
{

    namespace transform
    {

        struct data : public DataObject
        {

        };

    } // namespace transform

    SET_NODE_DATA(transform::data)

        namespace scenegraph
        {

            template <> status add_node<node::Transform>(std::string n)
            {
                //SET_NODE_DATA(transform::data)
                std::cout << "add transform node\n";
                    return status();
            } 

            template <> status do_it<node::Transform>::exec(FNodeDescriptor node)
            {
                //SET_NODE_DATA(transform::data)

                    return status();
            };


        } // namespace scenegraph

} // namespace feather

#endif
