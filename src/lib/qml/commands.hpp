/***********************************************************************
 *
 * Filename: commands.hpp
 *
 * Description: Used to give qml access to the core.
 *
 * Copyright (C) 2015 Richard Layman, rlayman2000@yahoo.com 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "types.hpp"
#include "status.hpp"
#include "command.hpp"
#include "pluginmanager.hpp"

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
            status get_node_icon(int nid, std::string& file);
            status load_plugins();
            status run_command(std::string cmd, feather::parameter::ParameterList params);

            // Fields
 
            // get field base 
            status get_field_base(int uid, int field, feather::field::FieldBase* &f);
            // get the field value
            status get_field_val(int uid, int node, int field, bool& val);
            status get_field_val(int uid, int node, int field, int& val);
            status get_field_val(int uid, int node, int field, float& val);
            // set the field value
            status set_field_val(int uid, int node, int field, bool& val);
            status set_field_val(int uid, int node, int field, int& val);
            status set_field_val(int uid, int node, int field, float& val);
            status get_field_connection_status(int uid, int node, int field, bool& val);
            status get_fid_list(int nid, field::connection::Type conn, std::vector<int>& list);

            // SG EDITOR
            void get_node_connections(int uid, std::vector<int>& nodes);
            std::string get_node_name(int uid);
            void gl_init(int uid, FGlInfo& info);
            void gl_draw(int uid, FGlInfo& info);
            int get_min_uid();
            int get_max_uid();
            void get_plugins(std::vector<PluginInfo>& list);

            // SG SELECTION
            status add_selection(int type, int uid, int nid, int fid);
            status node_selection(int type, int uid, int nid);
        } // namespace command

    } // namespace qml

} // namespace feather

#endif
