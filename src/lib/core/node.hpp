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
#include "object.hpp"
#include "field.hpp"

namespace feather
{

    namespace node
    {

        enum Type {
            Null,
            Camera,
            Light,
            Texture,
            Shader,
            Object,
            N
        };


        /* This is the class mapped to the sg vertex and gets
         * called during a sg update or other sg action
         */
        /*
        struct NodeBase
        {
            int node; // unique id of the node
            //feather::PluginInfo plugin; // holds plugin data
            //PluginNodeFields* fields; // holds field data for the node
            std::vector<connection::Connection> connections; // what fields are connected
        };
        */

    } // namespace node

} // namespace feather

#endif
