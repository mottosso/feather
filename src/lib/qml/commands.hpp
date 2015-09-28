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

            // Node

            int add_node(int type, int node, std::string name); 
            bool nodes_added(std::vector<int>& uids);
            void nodes_updated();
            bool node_exists(int uid);
            status connect_nodes(int n1, int f1, int n2, int f2); 
            status get_node_icon(int nid, std::string& file);
            status get_node_id(int uid, int& nid);
            status get_node_connected_uids(int uid, std::vector<int>& uids);
            status load_plugins();
            status run_command(std::string cmd, feather::parameter::ParameterList params);
            status run_command_string(std::string str);

            
            // Layer
            status add_layer(FLayer layer);
            status remove_layer(int lid);
            status move_layer(int sid, int tid);
            status get_layer(int id, FLayer &layer);
            void set_layer_name(std::string name, int lid);
            void set_layer_color(int r, int g, int b, int lid);
            void set_layer_visible(bool v, int lid);
            void set_layer_locked(bool l, int lid);
            int layer_count();
            void add_node_to_layer(int lid, int uid);


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
            status get_fid_list(int uid, int nid, field::connection::Type conn, std::vector<field::FieldBase*>& list);


            // SG EDITOR
            void clear();
            void get_node_connections(int uid, std::vector<int>& nodes);
            int get_node_connection_count(int uid);
            std::string get_node_name(int uid);
            void gl_init(int uid, FGlInfo& info);
            void gl_draw(int uid, FGlInfo& info);
            int get_min_uid();
            int get_max_uid();
            void get_plugins(std::vector<PluginInfo>& list);

            // SG SELECTION
            int selected_node();
            status select_node(int uid);
            status select_node(int type, int uid);
            status select_node(int type, int uid, int nid);
            status select_node(int type, int uid, int nid, int fid);
            status get_selected_nodes(std::vector<int>& uids);
            void clear_selection();
   
        } // namespace command

    } // namespace qml

} // namespace feather

#endif
