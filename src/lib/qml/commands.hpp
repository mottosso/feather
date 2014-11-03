// =====================================================================================
// 
//       Filename:  commands.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/02/2014 09:45:17 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "types.hpp"
#include "status.hpp"

namespace feather
{

    namespace qml
    {

        namespace command
        {

            status init();
            status add_node(int type, int node, int id); 
            status draw_sg(QMatrix4x4& view);
            status load_node_plugins();

        } // namespace command

    } // namespace qml

} // namespace feather

#endif
