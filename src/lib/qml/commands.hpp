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
#include "command.hpp"

namespace feather
{

    namespace qml
    {

        namespace command
        {

            status init();
            int add_node(int type, int node, std::string name); 
            bool node_exists(int uid);
            status connect_nodes(int n1, int f1, int n2, int f2); 
            status load_plugins();
            status run_command(std::string cmd, feather::parameter::ParameterList params);
            // get the field value
            status get_field_val(int uid, int node, int field, bool& val);
            status get_field_val(int uid, int node, int field, int& val);
            status get_field_val(int uid, int node, int field, float& val);
            // set the field value
            status set_field_val(int uid, int node, int field, bool& val);
            status set_field_val(int uid, int node, int field, int& val);
            status set_field_val(int uid, int node, int field, float& val);
            status get_field_connection_status(int uid, int node, int field, bool& val);
            // SG EDITOR
            void get_node_connections(int uid, std::vector<int>& nodes);
            std::string get_node_name(int uid);
            void gl_init(int uid, FGlInfo& info);
            void gl_draw(int uid, FGlInfo& info);
            int get_min_uid();
            int get_max_uid();

        } // namespace command

    } // namespace qml

} // namespace feather

#endif
